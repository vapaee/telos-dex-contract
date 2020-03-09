#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>
#include <dex/modules/record.hpp>
#include <dex/modules/market.hpp>
#include <dex/modules/ui.hpp>
#include <dex/modules/deposit.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;
        using namespace ui;
        using namespace record;
        using namespace market;
        using namespace deposit;

        namespace exchange {
         

            void aux_cancel_sell_order(name owner, uint64_t can_market, uint64_t market, const std::vector<uint64_t> & orders) {
                // viterbotelos, acorn.telosd, acorn.telosd, [1]
                PRINT("eosio::dex::exchange::aux_cancel_sell_order()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" can_market: ", std::to_string((unsigned long) can_market), "\n");
                PRINT(" market: ", std::to_string((unsigned long) market), "\n");
                PRINT(" orders.size(): ", orders.size(), "\n");

                sellorders selltable(get_self(), market);
                asset return_amount;
                name table = aux_get_table_from_market(market);
                
                ordersummary o_summary(get_self(), get_self().value);
                auto orders_ptr = o_summary.find(can_market);
                bool reverse_scope = can_market != market;

                // Register event
                aux_register_event(owner, name("cancel.order"), table.to_string() + "|" + std::to_string(orders.size()));

                for (int i=0; i<orders.size(); i++) {
                    uint64_t order_id = orders[i];
                    auto itr = selltable.find(order_id);
                    check(itr != selltable.end(), "buy order not found");
                    check(itr->owner == owner, "attemp to delete someone elses buy order");
                    return_amount = itr->selling;
                    PRINT("  return_amount: ", return_amount.to_string(), "\n");
                    selltable.erase(*itr);

                    // ake out the order from the user personal order registry
                    userorders buyerorders(get_self(), owner.value);
                    auto buyer_itr = buyerorders.find(market);
                    
                    check(buyer_itr != buyerorders.end(), "ERROR: cómo que no existe? No fue registrado antes?");
                    // take the order out of the buyer personal order registry
                    buyerorders.modify(*buyer_itr, same_payer, [&](auto & a){
                        std::vector<uint64_t> newlist;
                        std::copy_if (a.ids.begin(), a.ids.end(), std::back_inserter(newlist), [&](uint64_t i){return i!=order_id;} );
                        a.ids = newlist;
                    });
                    // if there's no orders left, erase the entire table entry
                    buyer_itr = buyerorders.find(market);
                    if (buyer_itr != buyerorders.end() && buyer_itr->ids.size() == 0) {
                        buyerorders.erase(*buyer_itr);
                    }

                    // take out the registry for this canceled order
                    check(orders_ptr != o_summary.end(), "ordertable does not exist for that scope");
                    if (!reverse_scope) {
                        // we are canceling a sell-order so we decrement the supply
                        o_summary.modify(*orders_ptr, same_payer, [&](auto & a){
                            a.supply.orders--;
                            check(a.supply.total.symbol == return_amount.symbol,
                                create_error_asset2(ERROR_AGSO_6, a.supply.total, return_amount).c_str());
                            a.supply.total -= return_amount;
                        });
                    } else {
                        // we are consuming a sell-order so we decrement the demand
                        o_summary.modify(*orders_ptr, same_payer, [&](auto & a){
                            a.demand.orders--;
                            check(a.demand.total.symbol == return_amount.symbol,
                                create_error_asset2(ERROR_AGSO_6, a.demand.total, return_amount).c_str());
                            a.demand.total -= return_amount;
                        });
                    }

                    action(
                        permission_level{get_self(),name("active")},
                        get_self(),
                        name("swapdeposit"),
                        std::make_tuple(get_self(), owner, return_amount, false, string("order canceled, payment returned"))
                    ).send();

                    asset _asset;
                    aux_trigger_event(return_amount.symbol.code(), name("cancel"), owner, get_self(), return_amount, _asset, _asset);
                }

                userorders buyerorders(get_self(), owner.value);
                auto buyer_itr = buyerorders.find(market);
                if (buyer_itr != buyerorders.end() && buyer_itr->ids.size() == 0) {
                    buyerorders.erase(*buyer_itr);
                }
            }

            void action_cancel(name owner, name type, const symbol_code & token_a, const symbol_code & token_p, const std::vector<uint64_t> & orders) {
                // viterbotelos, sell, ACORN, TELOSD, [1]
                PRINT("eosio::dex::exchange::action_cancel()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" type: ", type.to_string(), "\n");
                PRINT(" token_a: ",  token_a.to_string(), "\n");
                PRINT(" token_p: ",  token_p.to_string(), "\n");
                PRINT(" orders.size(): ", std::to_string((int) orders.size()), "\n");

                require_auth(owner);

                // create scope for the orders table
                uint64_t buy_market = aux_get_market_id(token_a, token_p);
                uint64_t sell_market = aux_get_market_id(token_p, token_a);
                uint64_t can_market = aux_get_canonical_market(token_a, token_p);

                if (type == name("sell")) {
                    aux_cancel_sell_order(owner, can_market, buy_market, orders);
                }

                if (type == name("buy")) {
                    aux_cancel_sell_order(owner, can_market, sell_market, orders);
                }

                PRINT("eosio::dex::exchange::action_cancel() ...\n");
            }

            // ----------------------------------------------------------
            void aux_clone_user_deposits(name owner, vector<asset> & depos) {
                PRINT("eosio::dex::exchange::aux_clone_user_deposits()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                
                deposits depositstable(get_self(), owner.value);
                for (auto itr = depositstable.begin(); itr != depositstable.end(); itr++) {
                    PRINT(" - deposit: ", itr->amount.to_string(), "\n");
                    depos.push_back(itr->amount);            
                }

                PRINT(" deposits.size(): ", depos.size(), "\n");
                PRINT("eosio::dex::exchange::aux_clone_user_deposits() ...\n");
            } 
                        
            void aux_generate_sell_order(bool inverted, name owner, uint64_t market_buy, uint64_t market_sell, asset total, asset payment, asset price, asset inverse, name ram_payer, uint64_t sell_ui) {
                PRINT("eosio::dex::exchange::aux_generate_sell_order()\n");
                PRINT(" inverted: ", std::to_string(inverted), "\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" market_buy: ", std::to_string((long unsigned) market_buy), "\n");
                PRINT(" market_sell: ", std::to_string((long unsigned) market_sell), "\n");
                PRINT(" total: ", total.to_string(), "\n");        // total: 1.00000000 TLOS
                PRINT(" payment: ", payment.to_string(), "\n");    // payment: 2.50000000 CNT
                PRINT(" price: ", price.to_string(), "\n");        // price: 2.50000000 CNT
                PRINT(" inverse: ", inverse.to_string(), "\n");    // inverse: 0.40000000 TLOS
                PRINT(" ram_payer: ", ram_payer.to_string(), "\n");
                PRINT(" sell_ui: ", std::to_string((long unsigned) sell_ui), "\n");
                
                double maker_fee_percentage = 0.000;
                double taker_fee_percentage = 0.0025;
                
                sellorders buytable(get_self(),  market_buy);
                sellorders selltable(get_self(), market_sell);

                ordersummary o_summary(get_self(), get_self().value);
                symbol_code  A = total.symbol.code();
                symbol_code  B = payment.symbol.code();
                
                uint64_t can_market = aux_get_canonical_market(A, B);
                uint64_t inv_market = aux_get_inverted_market(A, B);
                uint64_t market = aux_get_market_id(A, B);
                auto orders_ptr = o_summary.find(can_market);
                bool reverse_scope = market != can_market;

                // sellorders selltable(get_self(), scope.value);
                auto buy_index = buytable.get_index<name("price")>();
                // auto sell_index = selltable.get_index<"price"_n>();
                auto sell_index = selltable.get_index<name("price")>();
                asset remaining = total;
                asset remaining_payment = payment;
                asset current_price;
                asset current_inverse;
                asset current_total;
                asset current_payment = payment;
                name maker, taker;
                uint64_t maker_ui, taker_ui;
                // asset inverse = vapaee::utils::inverse(price, total.symbol);
                sell_order_table order;
                
                vector<asset> deposits;
                aux_put_deposits_on_user_ram(owner, payment);
                aux_clone_user_deposits(owner, deposits);

                tokens tokenstable(get_self(), get_self().value);
                auto atk_itr = tokenstable.find(total.symbol.code().raw());
                auto ptk_itr = tokenstable.find(price.symbol.code().raw());
                check(atk_itr != tokenstable.end(), (string("Token ") + total.symbol.code().to_string() + " not registered").c_str());
                check(ptk_itr != tokenstable.end(), (string("Token ") + price.symbol.code().to_string() + " not registered").c_str());
                // check(atk_itr->precision == total.symbol.precision(), aux_error_1(total, atk_itr->precision).c_str());
                // check(ptk_itr->precision == price.symbol.precision(), aux_error_1(price, ptk_itr->precision).c_str());
                check(price.symbol != total.symbol, (string("price token symbol ") + price.symbol.code().to_string() + " MUST be different from total").c_str());
    
                uint64_t total_unit = pow(10.0, total.symbol.precision());
                uint64_t price_unit = pow(10.0, price.symbol.precision());

                // iterate over a list or buy order from the maximun price down
                for (auto b_ptr = buy_index.begin(); b_ptr != buy_index.end(); b_ptr = buy_index.begin()) {
                    check(b_ptr->price.symbol == inverse.symbol,
                        create_error_asset2(ERROR_AGSO_1, b_ptr->price, inverse).c_str());
                    PRINT(" compare: (price<=inverse) ??  - (", b_ptr->price.to_string(), " <= ", inverse.to_string(), ") ??? \n");
                    if (b_ptr->price.amount <= inverse.amount) {
                        // transaction !!!
                        current_price = b_ptr->price;   // TLOS
                        PRINT("TRANSACTION!! price: ", current_price.to_string(),"\n");
                        maker = b_ptr->owner;
                        maker_ui = b_ptr->ui;
                        taker = owner;
                        taker_ui = sell_ui;
                        PRINT("              maker: ", maker.to_string() ,"\n");
                        PRINT("      current_price: ", current_price.to_string() ,"\n");
                        PRINT("       b_ptr->total: ", b_ptr->total.to_string(), " > remaining: ", remaining.to_string()," ?\n");
    
                        check(b_ptr->total.symbol == remaining.symbol,
                            create_error_asset2(ERROR_AGSO_2, b_ptr->total, remaining).c_str());

                        if (b_ptr->total > remaining) { // CNT
                            // maker wants more that the user is selling -> reduces maker order amount
                            current_total = remaining;  // CNT
                            current_payment.amount = utils::multiply(remaining, b_ptr->inverse);

                            // // this code is useful to hot-debugging
                            // check(owner.value != name("viterbotelos").value,
                            //     create_error_asset4("DEBUG IN PROGRESS. PLEASE WAIT",
                            //     current_payment, b_ptr->inverse, remaining, b_ptr->total).c_str());       

                            buytable.modify(*b_ptr, aux_get_modify_payer(ram_payer), [&](auto& a){
                                // double percent = (double)remaining.amount / (double)a.total.amount;
                                check(a.total.symbol == remaining.symbol,
                                    create_error_asset2(ERROR_AGSO_3, a.total, remaining).c_str());
                                check(a.selling.symbol == current_payment.symbol,
                                    create_error_asset2(ERROR_AGSO_4, a.selling, current_payment).c_str());
                                a.total   -= remaining;          // CNT
                                a.selling -= current_payment;    // TLOS
                            });
                            PRINT("    payment (1): ", current_payment.to_string(),"\n");

                            // decrese the total in registry for this incompleted order
                            check(orders_ptr != o_summary.end(), "table MUST exist but it does not");
                            o_summary.modify(*orders_ptr, ram_payer, [&](auto & a){
                                PRINT("        a.total:  ", a.demand.total.to_string(),"\n");
                                PRINT("        payment:  ", current_payment.to_string(),"\n");
                                
                                if (!reverse_scope) {
                                    // we are consuming part of a buy-order so we decrement the demand
                                    check(a.demand.total.symbol == current_payment.symbol,
                                        create_error_asset2(ERROR_AGSO_5, a.demand.total, current_payment).c_str());             
                                    a.demand.total -= current_payment;
                                } else {
                                    // we are consuming part of a sell-order so we decrement the supply
                                    check(a.supply.total.symbol == current_payment.symbol,
                                        create_error_asset2(ERROR_AGSO_5, a.supply.total, current_payment).c_str());
                                    a.supply.total -= current_payment;
                                }
                            });

                        } else {
                            // maker gets all amount wanted -> destroy order                        
                            uint64_t buy_id = b_ptr->id;
                            current_total = b_ptr->total;
                            current_payment = b_ptr->selling;
                            buytable.erase(*b_ptr);
                            PRINT("    payment (2): ", current_payment.to_string(),"\n");

                            // register order in user personal order registry
                            userorders makerorders(get_self(), maker.value);     
                            auto maker_itr = makerorders.find(market_buy);
                            check(maker_itr != makerorders.end(), "ERROR: cómo que no existe? No fue registrado antes? maker? market_buy?");
                            check(orders_ptr != o_summary.end(), "table MUST exist but it does not");

                            // take the order out of the maker personal order registry
                            makerorders.modify(*maker_itr, ram_payer, [&](auto & a){
                                std::vector<uint64_t> newlist;
                                std::copy_if (a.ids.begin(), a.ids.end(), std::back_inserter(newlist), [&](uint64_t i){return i!=buy_id;} );
                                a.ids = newlist;
                            });
                            // if there's no orders left, erase the entire table entry
                            maker_itr = makerorders.find(market_buy);
                            if (maker_itr != makerorders.end() && maker_itr->ids.size() == 0) {
                                makerorders.erase(*maker_itr);
                            }

                            if (!reverse_scope) {
                                // we are consuming a buy-order so we decrement the demand
                                o_summary.modify(*orders_ptr, ram_payer, [&](auto & a){
                                    a.demand.orders--;
                                    check(a.demand.total.symbol == current_payment.symbol,
                                        create_error_asset2(ERROR_AGSO_6, a.demand.total, current_payment).c_str());
                                    a.demand.total -= current_payment;
                                });
                            } else {
                                // we are consuming a sell-order so we decrement the supply
                                o_summary.modify(*orders_ptr, ram_payer, [&](auto & a){
                                    a.supply.orders--;
                                    check(a.supply.total.symbol == current_payment.symbol,
                                        create_error_asset2(ERROR_AGSO_6, a.supply.total, current_payment).c_str());
                                    a.supply.total -= current_payment;
                                });
                            }

                        }

                        check(remaining.symbol == current_total.symbol,
                            create_error_asset2(ERROR_AGSO_7, remaining, current_total).c_str());
                        check(remaining_payment.symbol == current_payment.symbol,
                            create_error_asset2(ERROR_AGSO_8, remaining_payment, current_payment).c_str());

                        remaining -= current_total;
                        remaining_payment -= current_payment;
                        asset taker_fee, maker_fee, taker_gains, maker_gains;

                        // calculate fees
                        maker_fee = current_total;
                        maker_fee.amount = current_total.amount * maker_fee_percentage;
                        maker_gains = current_total - maker_fee;
                        // taker gets total minus maker_fee

                        taker_fee = current_payment;
                        taker_fee.amount = current_payment.amount * taker_fee_percentage;
                        taker_gains = current_payment - taker_fee;

                        // transfer CNT to maker 
                        action(
                            permission_level{get_self(),name("active")},
                            get_self(),
                            name("swapdeposit"),
                            std::make_tuple(taker, maker, maker_gains, true, string("exchange made for ") + current_payment.to_string())
                        ).send();
                        PRINT("     -- transfer ", maker_gains.to_string(), " to ", maker.to_string(),"\n");
                            
                        // transfer to contract fees on CNT
                        // at this moment maker_fee is still in the owner's deposits. So it must be swaped to the contract before earning it
                        if (maker_fee.amount > 0) {
                            action(
                                permission_level{get_self(),name("active")},
                                get_self(),
                                name("swapdeposit"),
                                std::make_tuple(taker, get_self(), maker_fee, true, string("exchange made for ") + current_total.to_string())
                            ).send();
                            PRINT("     -- charge fees ", maker_fee.to_string(), " to ", maker.to_string(),"\n");
                        }
                            
                        // transfer TLOS to taker (TLOS the belongs to maker but the contracxts holds them)
                        action(
                            permission_level{get_self(),name("active")},
                            get_self(),
                            name("swapdeposit"),
                            std::make_tuple(get_self(), taker, taker_gains, true, string("exchange made for ") + current_total.to_string())
                        ).send();
                        PRINT("     -- transfer ", taker_gains.to_string(), " to ", taker.to_string(),"\n");

                        // convert deposits to earnings
                        // Now the contract's deposits includes the maker_fee, so it can be transformed to ernings
                        if (taker_fee.amount > 0) {
                            action(
                                permission_level{get_self(),name("active")},
                                get_self(),
                                name("deps2earn"),
                                std::make_tuple(taker_ui, taker_fee)
                            ).send();
                            PRINT("     -- converting fee ", maker_fee.to_string(), " to earnings\n");
                        }

                        // The taker_fee were already included in the contract's deposits, so no swap was needed.
                        // It can be earned directly
                        if (maker_fee.amount > 0) {
                            action(
                                permission_level{get_self(),name("active")},
                                get_self(),
                                name("deps2earn"),
                                std::make_tuple(maker_ui, maker_fee)
                            ).send();
                            PRINT("     -- converting fee ", taker_fee.to_string(), " to earnings\n");
                        }
                        // saving the transaction in history
                        current_inverse = utils::inverse(current_price, current_payment.symbol);
                        // PRINT("   - current_payment: ", current_payment.to_string(), "\n");  // 1.00000000 EDNA
                        // PRINT("   - inverse:         ", inverse.to_string(), "\n");
                        // PRINT("   - current_price:   ", current_price.to_string(), "\n");    // 0.00047800 TLOS
                        // PRINT("   - current_inverse: ", current_inverse.to_string(), "\n");
                        aux_register_transaction_in_history(inverted, maker, taker, current_inverse, current_price, current_payment, current_total, maker_fee, taker_fee);
                        
                    } else {
                        break;
                    }

                    PRINT("  remaining:", remaining.to_string(),"\n");
                    if (remaining.amount <= 0) break;
                }

                if (remaining.amount > 0 && remaining_payment.amount > 0) {
                    PRINT("-- final remaining: ", remaining.to_string(), " --\n");
                    // insert sell order
                    
                    payment.amount = remaining_payment.amount;

                    // transfer payment deposits to contract
                    action(
                        permission_level{get_self(),name("active")},
                        get_self(),
                        name("swapdeposit"),
                        std::make_tuple(owner, get_self(), remaining, false, string("future payment for order"))
                    ).send();

                    aux_trigger_event(remaining.symbol.code(), name("order"), owner, get_self(), remaining, payment, price);

                    PRINT("   remaining: ", remaining.to_string(), "\n");
                    PRINT("   payment: ", payment.to_string(), "\n");
                    PRINT("   price: ", price.to_string(), "\n");
                    PRINT("   inverse: ", inverse.to_string(), "\n");

                    // create order entry
                    // inverse = vapaee::utils::inverse(price, remaining.symbol);
                    uint64_t id = selltable.available_primary_key();
                    PRINT("   selltable.emplace() id:", std::to_string((unsigned long) id),"\n"); 
                    selltable.emplace( ram_payer, [&]( auto& a ) {
                        a.id = id;
                        a.owner = owner;
                        a.price = price;
                        a.inverse = inverse;
                        a.total = payment;
                        a.selling = remaining;
                        a.ui = sell_ui;
                    });

                    // register new order in the orders table
                    if (orders_ptr == o_summary.end()) {
                        o_summary.emplace( ram_payer, [&]( auto& a ) {
                            if (!reverse_scope) {
                                PRINT("   o_summary.emplace() can_market:", std::to_string((unsigned long)can_market),"\n"); 
                                a.market = can_market;
                                a.sell = remaining.symbol.code();
                                a.pay = payment.symbol.code();            
                                a.supply.orders = 1;
                                a.supply.total = remaining;
                                a.demand.orders = 0;
                                a.demand.total = asset(0, payment.symbol);
                            } else {
                                PRINT("   o_summary.emplace() can_market:", std::to_string((unsigned long)can_market)," INVERSED\n"); 
                                a.market = can_market;
                                a.sell = payment.symbol.code();
                                a.pay = remaining.symbol.code();
                                a.supply.orders = 0;
                                a.supply.total = asset(0, payment.symbol);
                                a.demand.orders = 1;
                                a.demand.total = remaining;
                            }                       
                        });
                    } else {
                        o_summary.modify(*orders_ptr, ram_payer, [&](auto & a){
                            if (!reverse_scope) {
                                a.supply.orders++;
                                a.supply.total += remaining;
                            } else {
                                a.demand.orders++;
                                a.demand.total += remaining;
                            }
                        });
                    }

                    // register order in user personal order registry
                    userorders userorders_table(get_self(), owner.value);
                    auto user_itr = userorders_table.find(market_sell);
                    if (user_itr == userorders_table.end()) {
                        PRINT("   userorders_table.emplace id:", std::to_string((unsigned long)market_sell),"\n"); 
                        userorders_table.emplace( ram_payer, [&]( auto& a ) {
                            a.table = aux_get_table_from_market(market_sell).to_string();
                            a.market = market_sell;
                            a.ids.push_back(id);
                        });
                    } else {
                        userorders_table.modify(*user_itr, ram_payer, [&](auto & a){
                            a.ids.push_back(id);
                        });
                    }

                    PRINT("  sellorders.emplace(): ", std::to_string((unsigned long long) id), "\n");
                }
                
                PRINT("eosio::dex::exchange::aux_generate_sell_order() ...\n");
            }

            void aux_generate_order(name owner, name type, asset total, asset price, name ram_payer, uint64_t ui) {
                PRINT("eosio::dex::exchange::aux_generate_order()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" type: ", type.to_string(), "\n");
                PRINT(" total: ", total.to_string(), "\n");
                PRINT(" price: ", price.to_string(), "\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");
                
                require_auth(owner);

                // Check if blacklisted
                check(eosio::dex::dao::aux_is_token_blacklisted(total.symbol.code()), 
                    create_error_symcode1(ERROR_AGO_1, total.symbol.code()).c_str());
                check(eosio::dex::dao::aux_is_token_blacklisted(price.symbol.code()), 
                    create_error_symcode1(ERROR_AGO_2, price.symbol.code()).c_str());

                // create scope for the orders table
                uint64_t market_buy = aux_get_market_id(total.symbol.code(), price.symbol.code());
                uint64_t market_sell = aux_get_market_id(price.symbol.code(), total.symbol.code());

                PRINT(" market_buy: ", std::to_string((long unsigned) market_buy), "\n");
                PRINT(" market_sell: ", std::to_string((long unsigned) market_sell), "\n");
                
                asset inverse = eosio::dex::utils::inverse(price, total.symbol);
                asset payment = eosio::dex::utils::payment(total, price);
                
                PRINT(" -> inverse: ", inverse.to_string(), "\n");
                PRINT(" -> payment: ", payment.to_string(), "\n");

                aux_register_event(owner, name(type.to_string() + ".order"), total.to_string() + "|" + price.to_string() );

                // Check user interface is valid and registered
                eosio::dex::ui::aux_assert_ui_is_valid(ui);


                if (type == name("sell")) {
                    aux_generate_sell_order(false, owner, market_sell, market_buy, total, payment, price, inverse, ram_payer, ui);
                } else if (type == name("buy")) {
                    aux_generate_sell_order(true, owner, market_buy, market_sell, payment, total, inverse, price, ram_payer, ui);
                } else {
                    check(false, (string("type must be 'sell' or 'buy' in lower case, got: ") + type.to_string()).c_str());
                }
                
                PRINT("eosio::dex::exchange::aux_generate_order() ...\n");
            }


            void action_order(name owner, name type, const asset & total, const asset & price, uint64_t ui) {
                PRINT("eosio::dex::exchange::action_order()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" type: ", type.to_string(), "\n");      
                PRINT(" total: ", total.to_string(), "\n");      
                PRINT(" price: ", price.to_string(), "\n");      
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");
                require_auth(owner);

                aux_generate_order(owner, type, total, price, owner, ui);

                PRINT("eosio::dex::exchange::action_order() ...\n");      
            }

            void action_hotfix(int num, name account, asset quantity) {
                
            }
            
        };     
    };
};
