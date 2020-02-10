#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/packages/utils.hpp>
#include <dex/packages/record.hpp>
#include <dex/packages/market.hpp>
#include <dex/packages/ui.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;
        // using namespace ui;
        using namespace record;
        // using namespace market;

        namespace deposit {

            void aux_substract_deposits(name owner, const asset & amount, name ram_payer) {
                PRINT("eosio::dex::deposit::aux_substract_deposits()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" amount: ", amount.to_string(), "\n");

                deposits depositstable(get_self(), owner.value);
                auto itr = depositstable.find(amount.symbol.code().raw());
                check(itr != depositstable.end(),
                            create_error_asset1(ERROR_ASD_1, amount).c_str());

                check(itr->amount.symbol == amount.symbol,
                    create_error_asset2(ERROR_ASD_2, itr->amount, amount).c_str());
                if (itr->amount == amount) {
                    PRINT("  itr->amount == amount: ",  amount.to_string(), "\n");
                    depositstable.erase(itr);
                } else {
                    PRINT("  itr->amount > amount: ", itr->amount.to_string(), " > ", amount.to_string(),  "\n");
                    check(itr->amount > amount,
                            create_error_asset2(ERROR_ASD_3, amount, itr->amount).c_str());
                    
                    depositstable.modify(*itr, same_payer, [&](auto& a){
                        a.amount -= amount;
                    });
                }
                PRINT("eosio::dex::deposit::aux_substract_deposits() ...\n");
            }

            void aux_add_deposits(name owner, const asset & amount, name ram_payer) {
                PRINT("eosio::dex::deposit::aux_add_deposits()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" amount: ", amount.to_string(), "\n");
                PRINT(" ram_payer: ", ram_payer.to_string(), "\n");

                if (has_auth(owner)) {
                    PRINT(" -> owner has auth : ", owner.to_string(), "\n");
                }
                if (has_auth(get_self())) {
                    PRINT(" -> owner has auth : ", owner.to_string(), "\n");
                }

                tokens tokenstable(get_self(), get_self().value);
                auto tk_itr = tokenstable.find(amount.symbol.code().raw());
                check(tk_itr != tokenstable.end(), "The token is not registered");
                check(tk_itr->tradeable, "The token is not setted as tradeable. Contact the token's responsible admin.");

                depusers depuserstable(get_self(), get_self().value);
                auto user_itr = depuserstable.find(owner.value);
                if (user_itr == depuserstable.end()) {
                    PRINT(" -> depuserstable.emplace() : \n");
                    // check(has_auth(ram_payer), "ERROR: attempt to allocate RAM without authorization for depusers table");
                    depuserstable.emplace( ram_payer, [&]( auto& a ){
                        a.account = owner;
                    });
                } else {
                    if (ram_payer != get_self()) {
                        // change from using contract RAM to user's RAM 
                        PRINT(" -> depuserstable.modify() : \n");
                        depuserstable.modify(*user_itr, same_payer, [&]( auto& a ){
                            a.account = owner;
                        });
                    }
                }

                deposits depositstable(get_self(), owner.value);
                auto itr = depositstable.find(amount.symbol.code().raw());
                if (itr == depositstable.end()) {
                    
                    // check(has_auth(ram_payer), "ERROR: attempt to allocate RAM without authorization for deposits table");
                    depositstable.emplace( ram_payer, [&]( auto& a ){
                        a.amount = amount;
                    });
                } else {
                    depositstable.modify(*itr, same_payer , [&](auto& a){
                        check(a.amount.symbol == amount.symbol,
                            create_error_asset2(ERROR_AAD_1, a.amount, amount).c_str()); 
                        a.amount += amount;
                    });
                }

                PRINT("eosio::dex::deposit::aux_add_deposits() ...\n");
            }
            
            void aux_put_deposits_on_user_ram(name owner, const asset & amount) {
                PRINT("eosio::dex::deposit::aux_put_deposits_on_user_ram()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" amount: ", amount.to_string(), "\n");

                if (!has_auth(owner)) {
                    PRINT(" user has no auth -> quitting\n");
                    PRINT("eosio::dex::deposit::aux_put_deposits_on_user_ram()...\n");
                    return;
                }

                depusers depuserstable(get_self(), get_self().value);
                auto user_itr = depuserstable.find(owner.value);
                if (user_itr != depuserstable.end()) {
                    // change from using contract RAM to user's RAM 
                    PRINT(" -> depuserstable.modify() : \n");
                    depuserstable.modify(*user_itr, owner, [&]( auto& a ){
                        a.account = a.account; // dummie operation
                    });
                }

                deposits depositstable(get_self(), owner.value);
                auto itr = depositstable.find(amount.symbol.code().raw());
                if (itr != depositstable.end()) {
                    depositstable.modify(*itr, owner , [&](auto& a){
                        a.amount = a.amount; // dummie operation
                    });
                }

                PRINT("eosio::dex::deposit::aux_put_deposits_on_user_ram() ...\n");
            }

            void aux_earn_micro_change(name owner, symbol orig, symbol extended, name ram_payer, uint64_t ui) {
                PRINT("eosio::dex::deposit::aux_earn_micro_change()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" orig: ", orig.code().to_string(), "\n");
                PRINT(" extended: ", extended.code().to_string(), "\n");
                PRINT(" ram_payer: ", ram_payer.to_string(), "\n");

                deposits depositstable(get_self(), owner.value);
                auto itr = depositstable.find(extended.code().raw());
                
                if (itr == depositstable.end()) return;
                // check(itr != depositstable.end(),
                //             create_error_symbol1(ERROR_AEMC_1, extended).c_str());
                
                check(orig.code().raw() == extended.code().raw(),
                            create_error_symbol2(ERROR_AEMC_2, orig, extended).c_str());

                asset lowest_real_value = asset(1, orig);
                asset lowest_extended_value = aux_extend_asset(lowest_real_value);
                PRINT("   lowest_real_value: ", lowest_real_value.to_string(), "\n");
                PRINT("   lowest_extended_value: ", lowest_extended_value.to_string(), "\n");
                PRINT("   itr->amount: ", itr->amount.to_string(), "\n");
                if (itr->amount < lowest_extended_value) {
                    // transfer to contract fees on CNT
                    action(
                        permission_level{get_self(),name("active")},
                        get_self(),
                        name("swapdeposit"),
                        std::make_tuple(owner, get_self(), itr->amount, true, string(" withdraw micro-change fees: ") + itr->amount.to_string())
                    ).send();

                    PRINT("     -- withdraw micro-change fees: ",  itr->amount.to_string(), " from ", owner.to_string(),"\n");
                    // convert deposits to earnings
                    action(
                        permission_level{get_self(),name("active")},
                        get_self(),
                        name("deps2earn"),
                        std::make_tuple(ui, itr->amount)
                    ).send();
                    PRINT("     -- converting micro-chang fees ", itr->amount.to_string(), " to earnings\n");
                }

                PRINT("eosio::dex::deposit::aux_earn_micro_change() ...\n");
            }

            void aux_transfer_earnings_to_ui(const uint64_t ui, const asset & quantity) {
                PRINT("eosio::dex::deposit::aux_transfer_earnings_to_ui()\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");

                // get interface receiver account and params
                interfaces uitable(get_self(), get_self().value);
                auto ptr = uitable.find(ui);
                check(ptr != uitable.end(), create_error_id1(ERROR_ATETU_1, ui).c_str());
                name receiver = ptr->receiver;
                string memo = ptr->params;

                // get token contract account
                tokens tokenstable(get_self(), get_self().value);
                auto tk_ptr = tokenstable.find(quantity.symbol.code().raw());

                action(
                    permission_level{get_self(),name("active")},
                    tk_ptr->contract,
                    name("transfer"),
                    std::make_tuple(get_self(), receiver, quantity, memo)
                ).send();
                PRINT("   transfer ", quantity.to_string(), " to ", receiver.to_string(),"\n");

                // Hay que sacar de la tabla de ui cual es el account y mandarle la quantity

                PRINT("eosio::dex::deposit::aux_transfer_earnings_to_ui() ...\n");
            }            

            void aux_convert_deposits_to_earnings(const uint64_t ui, asset quantity) {
                PRINT("eosio::dex::deposit::aux_convert_deposits_to_earnings()\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");

                aux_substract_deposits(get_self(), quantity, get_self());
                aux_transfer_earnings_to_ui(ui, quantity);

                PRINT("eosio::dex::deposit::aux_convert_deposits_to_earnings() ...\n");
            }            

            void action_withdraw(name owner, const asset & quantity, uint64_t ui) {
                PRINT("eosio::dex::deposit::action_withdraw()\n");
                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");

                // substract or remove deposit entry
                require_auth(owner);
                asset extended = aux_extend_asset(quantity);
                aux_substract_deposits(owner, extended, owner);

                aux_earn_micro_change(owner, quantity.symbol, extended.symbol, owner, ui);

                // send tokens
                tokens tokenstable(get_self(), get_self().value);
                auto ptk_itr = tokenstable.find(quantity.symbol.code().raw());
                check(ptk_itr != tokenstable.end(), (string("Token ") + quantity.symbol.code().to_string() + " not registered").c_str());

                action(
                    permission_level{get_self(),name("active")},
                    ptk_itr->contract,
                    name("transfer"),
                    std::make_tuple(get_self(), owner, quantity, string("withdraw deposits: ") + quantity.to_string())
                ).send();
                PRINT("   transfer ", quantity.to_string(), " to ", owner.to_string(),"\n");

                aux_register_event(owner, name("withdraw"), quantity.to_string());

                asset _asset;
                aux_trigger_event(quantity.symbol.code(), name("withdraw"), owner, get_self(), quantity, _asset, _asset);

                PRINT("eosio::dex::deposit::action_withdraw() ...\n");
            }

            void action_swapdeposit(name from, name to, const asset & quantity, bool trigger_event, string memo) {
                PRINT("eosio::dex::deposit::action_swapdeposit()\n");
                PRINT(" from: ", from.to_string(), "\n");
                PRINT(" to: ", to.to_string(), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");
                PRINT(" trigger_event: ", std::to_string(trigger_event), "\n");
                PRINT(" memo: ", memo.c_str(), "\n");
                
                check( from != to, "cannot swap deposits to self" );

                // if is not an internal inline action then the user "from" must have beed signed this transaction
                if ( !has_auth( get_self() )) {
                    require_auth( from );
                }
                
                check( is_account( to ), "to account does not exist");
                auto sym = quantity.symbol.code();
                tokens tokenstable(get_self(), get_self().value);
                const auto& st = tokenstable.get( sym.raw() );

                require_recipient( from );
                require_recipient( to );

                check( quantity.is_valid(), "invalid quantity" );
                check( quantity.amount > 0, "must transfer positive quantity" );
                check( quantity.symbol.precision() == internal_precision, "symbol precision mismatch" );
                check( memo.size() <= 256, "memo has more than 256 bytes" );
                
                name ram_payer;
                if ( has_auth( to ) ) {
                    ram_payer = to;
                } else if (has_auth( from )) {
                    ram_payer = from;
                } else {
                    ram_payer = get_self();
                }
                PRINT("   -> ram_payer: ", ram_payer.to_string(), "\n");
                aux_substract_deposits(from, quantity, ram_payer);
                aux_add_deposits(to, quantity, ram_payer);

                if (from != get_self() && to != get_self()) {
                    trigger_event = true;
                    PRINT(" -> trigger_event: ", std::to_string(trigger_event), "\n");
                }

                if (trigger_event) {
                    asset _asset;
                    aux_trigger_event(quantity.symbol.code(), name("swapdeposit"), from, to, quantity, _asset, _asset);
                }
                
                PRINT("eosio::dex::deposit::action_swapdeposit() ...\n"); 
            }
            
            void action_convert_deposits_to_earnings(const uint64_t ui, const asset & quantity) {
                PRINT("eosio::dex::deposit::action_convert_deposits_to_earnings()\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");
                require_auth(get_self());

                aux_convert_deposits_to_earnings(ui, quantity);
                PRINT("eosio::dex::deposit::action_convert_deposits_to_earnings() ...\n");
            }

            void handler_transfer(name from, name to, asset quantity, string memo) {
                // skipp handling outcoming transfers from this contract to outside
                asset _quantity;
                if (to != get_self()) {
                    print(from.to_string(), " to ", to.to_string(), ": ", quantity.to_string(), " eosio::dex::deposit::handler_transfer() skip...\n");
                    return;
                }
                
                PRINT("eosio::dex::deposit::handler_transfer()\n");
                PRINT(" from: ", from.to_string(), "\n");
                PRINT(" to: ", to.to_string(), "\n");
                PRINT(" quantity: ", quantity.to_string(), "\n");
                PRINT(" memo: ", memo.c_str(), "\n");                
                
                vector<string> strings = {""};
                name ram_payer = get_self();
                PRINT(" strings.size(): ", std::to_string(strings.size()), "\n");
                int i,j,s;

                for (i=0,j=0,s=0; i<memo.size(); i++,j++) {
                    if (memo[i] == '|') {
                        s++;
                        j=0;
                        strings.push_back(string(""));
                        continue;
                    } else {
                        strings[s] += memo[i];
                    }
                }
                
                if (strings[0] == string("deposit")) {
                    asset _asset;
                    name receiver;
                    if (strings.size() == 1) {
                        receiver = from;
                    } else if (strings.size() == 2) {
                        receiver = name(strings[1]);
                    }
                    PRINT(" receiver: ", receiver.to_string(), "\n");
                    check(is_account(receiver), "receiver is not a valid account");
                    PRINT(" ram_payer: ", ram_payer.to_string(), "\n");
                    _quantity = aux_extend_asset(quantity);
                    PRINT(" _quantity extended: ", _quantity.to_string(), "\n");
                    aux_add_deposits(receiver, _quantity, get_self());
                    aux_register_event(from, name("deposit"), receiver.to_string() + "|" + _quantity.to_string());
                    aux_trigger_event(_quantity.symbol.code(), name("deposit"), from, receiver, _quantity, _asset, _asset);
                }

                PRINT("eosio::dex::deposit::handler_transfer() ...\n");
            }                 
        };     
    };
};
