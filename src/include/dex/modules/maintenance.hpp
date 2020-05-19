#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>
#include <dex/modules/exchange.hpp>
#include <dex/modules/record.hpp>
#include <dex/modules/global.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace maintenance {

            
            // maintenance ------------------------------------------------------------------
            void aux_cancel_sell_order(name owner, uint64_t id, uint64_t market) {
                PRINT("eosio::dex::maintenance::aux_cancel_sell_order()\n");
                uint64_t can_market = market;
                if (market % 2 != 0) {
                    can_market--;
                }

                PRINT(" owner: ", owner.to_string(), "\n");
                PRINT(" can_market: ", std::to_string((unsigned long) can_market), "\n");
                PRINT(" market: ", std::to_string((unsigned long) market), "\n");

                sellorders selltable(get_self(), market);
                asset return_amount;
                name table = aux_get_table_from_market(market);
                
                uint64_t order_id = id;
                auto itr = selltable.find(order_id);
                check(itr != selltable.end(), "buy order not found");
                check(itr->owner == owner, "attemp to delete someone elses buy order");
                return_amount = itr->selling;
                uint64_t ui = itr->ui;
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

                // skip ordersummary
                PRINT("  --> swapdeposit: swap ", return_amount.to_string(), " to ", owner.to_string(), "\n");
                action(
                    permission_level{get_self(),name("active")},
                    get_self(),
                    name("swapdeposit"),
                    std::make_tuple(get_self(), owner, return_amount, false, string("order canceled, payment returned, because of maintenance"))
                ).send();
                asset _asset;
                eosio::dex::record::aux_trigger_event(return_amount.symbol.code(), name("cancel"), owner, get_self(), return_amount, _asset, _asset);

                asset return_amount_real = aux_get_real_asset(return_amount);
                PRINT("  --> withdraw: transfer ", return_amount_real.to_string(), " to ", owner.to_string(), "\n");
                action(
                    permission_level{get_self(),name("active")},
                    get_self(),
                    name("withdraw"),
                    std::make_tuple(owner, return_amount_real, ui)
                ).send();
                eosio::dex::record::aux_trigger_event(return_amount_real.symbol.code(), name("withdraw"), owner, get_self(), return_amount_real, _asset, _asset);

                PRINT("eosio::dex::maintenance::aux_cancel_sell_order() ...\n");
            }

            string aux_maintenance_from_delmarkets() {
                PRINT("eosio::dex::maintenance::aux_maintenance_from_delmarkets()\n");
                // -- TODO:
                // - tomar la primer entrada de deltable y extraer a.id del market as market_id
                // - abrir la tabla history(market_id) y agarrar el primero .begin()
                // - si hay un primero, borrarlo y ta.
                // - si no hay un primero, significa que la history está lipia. history_clean = true
                // - abrir la tabla sellorders(market_id) y agarrar el primero .begin()
                // - si hay un primero, se ejecuta la inline action de cancelar order con ese scope y ese id
                // - si no hay un primero, significa que la sellorders está lipia. sellorders_clean = true
                // - if (history_clean && sellorders_clean) entonces borro la entrada del delmarkets y ese market ya no existe más
                // - si hay cambios -> eosio::dex::record::aux_register_event() EN CADA CASO

                string report;
                delmarkets deltable(get_self(), get_self().value);
                auto delptr = deltable.begin();
                bool history_clean = false;
                bool sellorders_clean = false;
                if (delptr != deltable.end()) {
                    uint64_t market_id = delptr->id;

                    // delete de oldest history entry
                    history htable(get_self(), market_id);
                    auto hptr = htable.begin();
                    if (hptr != htable.end()) {
                        report += string("|delmarket-history-prune:")+ std::to_string((unsigned long)hptr->id)  + "," + std::to_string((unsigned long)market_id);
                        // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), );
                        PRINT("  => history.erase(): ",std::to_string((unsigned long)hptr->id), "\n");
                        htable.erase(*hptr);

                        historyall hall_table(get_self(), get_self().value);
                        auto hall_index = hall_table.get_index<name("marketkey")>();
                        historyall_table auxiliar;
                        auxiliar.key = hptr->id;
                        auxiliar.market = market_id;
                        PRINT(" -> auxiliar.key: ",std::to_string((unsigned long long)auxiliar.key), "\n");
                        PRINT(" -> auxiliar.market: ",std::to_string((unsigned long long)auxiliar.market), "\n");
                        PRINT(" -> auxiliar.by_marketkey_key(): ",std::to_string((unsigned long long)auxiliar.by_marketkey_key()), "\n");
                        auto hall_ptr = hall_index.find(auxiliar.by_marketkey_key());
                        check(hall_ptr != hall_index.end(), "ERROR, el indice no encara");
                        check(hall_ptr->key == hptr->id, create_error_id2("ERROR, keys are not equal:", hall_ptr->key, hptr->id).c_str());
                        check(hall_ptr->market == market_id, create_error_id2("ERROR, markets are not equal:", hall_ptr->market, market_id).c_str());

                        PRINT("  => historyall.erase(): ",std::to_string((unsigned long)hall_ptr->id), "\n");
                        hall_table.erase(*hall_ptr);
                    } else {
                        PRINT(" -> history_clean \n");
                        history_clean = true;
                    }

                    // delete de first sellorders order
                    sellorders stable(get_self(), market_id);
                    auto sptr = stable.begin();
                    if (sptr != stable.end()) {
                        report += string("|delmarket-cancel-order:")+ std::to_string((unsigned long)sptr->id)  + "," + std::to_string((unsigned long)market_id);
                        // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("delmarket-cancel-order|")+ std::to_string((unsigned long)sptr->id)  + "|" + std::to_string((unsigned long)market_id));
                        PRINT("  => cancel_sell_order(): ",sptr->owner.to_string(), " id: ", std::to_string((unsigned long)sptr->id), " market: ", std::to_string((unsigned long)market_id), "\n"); 
                        aux_cancel_sell_order(sptr->owner, sptr->id, market_id);
                    } else {
                        PRINT(" -> sellorders_clean \n");
                        sellorders_clean = true;
                    }

                    if (history_clean && sellorders_clean) {
                        PRINT("  => delmarkets.erase(): ",std::to_string((unsigned long)delptr->id), " DELETE delmarket!!!!\n");
                        report += string("|delmarket-erase-market:") + std::to_string((unsigned long)market_id);
                        // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("delmarket-erase-market|") + std::to_string((unsigned long)market_id));
                        deltable.erase(*delptr);
                    }

                }
                PRINT("eosio::dex::maintenance::aux_maintenance_from_delmarkets() ...\n");                
                return report;
            }

            string aux_maintenance_from_history() {
                PRINT("eosio::dex::maintenance::aux_maintenance_from_history()\n");
                // -- TODO: 
                // - tomar hprune del config
                // - calcular la fecha mas_vieja que se permite un history_entry
                // - abrir la tabla historyall hall_table(get_self(), get_self().value) y tomar la primera entrada
                // - si tiene fecha (a.date) menor (más antigua) que mas_vieja, entonces:
                //    - abrir la tabla history h_table(get_self(), market_id); tomar la entrada con el id y borrarla
                //    - se borra esa entrada del historyall
                //    - eosio::dex::record::aux_register_event()
                string report;
                int hprune_days = eosio::dex::global::get().hprune;
                time_point_sec _now = eosio::dex::global::get_now_time_point_sec();
                time_point_sec _expire = time_point_sec(_now.utc_seconds - hprune_days * 24 * 60 * 60);

                PRINT(" -> _now:    ",std::to_string((unsigned long)_now.utc_seconds)," \n");
                PRINT(" -> _expire: ",std::to_string((unsigned long)_expire.utc_seconds)," \n");

                historyall hall_table(get_self(), get_self().value);
                auto hall_ptr = hall_table.begin();
                if (hall_ptr != hall_table.end()) {
                    if (hall_ptr->date < _expire) {
                        history h_table(get_self(), hall_ptr->market);
                        auto h_ptr = h_table.find(hall_ptr->key);
                        check(h_ptr != h_table.end(), create_error_id2(ERROR_AMFH_1, hall_ptr->key, hall_ptr->market));

                        report += string("|history-prune:") + std::to_string((unsigned long)hall_ptr->key) + "," + std::to_string((unsigned long)hall_ptr->market);
                        // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("history-prune|") + std::to_string((unsigned long)hall_ptr->key) + "|" + std::to_string((unsigned long)hall_ptr->market));

                        PRINT(" => history.erase(): ",std::to_string((unsigned long)h_ptr->id)," \n");
                        PRINT(" => historyall.erase(): ",std::to_string((unsigned long)hall_ptr->id)," \n");
                        h_table.erase(*h_ptr);
                        hall_table.erase(*hall_ptr);
                    }
                }                 
                PRINT("eosio::dex::maintenance::aux_maintenance_from_history() ...\n");
                return report;
            }

            string aux_maintenance_from_events() {
                PRINT("eosio::dex::maintenance::aux_maintenance_from_events()\n");
                // -- TODO: 
                // - tomar eprune del config
                // - calcular la fecha mas_vieja que se permite un history_entry
                // - abrir la tabla events etable(get_self(), get_self().value) y tomar la primera entrada
                // - si tiene fecha (a.date) menor (más antigua) que mas_vieja, entonces:
                //    - se borra esa entrada
                //    - eosio::dex::record::aux_register_event()
                string report;
                int eprune_days = eosio::dex::global::get().eprune;
                time_point_sec _now = eosio::dex::global::get_now_time_point_sec();
                time_point_sec _expire = time_point_sec(_now.utc_seconds - eprune_days * 24 * 60 * 60);

                PRINT(" -> _now:       ",std::to_string((unsigned long)_now.utc_seconds)," \n");
                PRINT(" -> _expire:    ",std::to_string((unsigned long)_expire.utc_seconds)," \n");

                events etable(get_self(), get_self().value);
                int max = 20;
                int count = 0;
                for (auto eptr = etable.begin(); eptr != etable.end() && count < max; eptr = etable.begin()) {
                    eptr++; //we skip the very first event witch holds the max id for events
                    if (eptr == etable.end()) {
                        break;
                    } else {
                        if (eptr->date < _expire) {
                            count++;
                            PRINT(" => events.erase(): ",std::to_string((unsigned long)eptr->id)," '", eptr->params, "' \n");
                            etable.erase(*eptr);
                        } else {
                            PRINT(" -> not expired: ",std::to_string((unsigned long)eptr->date.utc_seconds)," '", eptr->params, "' \n");
                            break;
                        }
                    }                    
                }
                if (count>0) {
                    report += string("|events-prune:") + std::to_string(count);
                    // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("events-prune|") + std::to_string(count));
                }

                PRINT("eosio::dex::maintenance::aux_maintenance_from_events() ...\n");
                return report;
            }

            string aux_maintenance_from_ballots() {
                PRINT("eosio::dex::maintenance::aux_maintenance_from_ballots()\n");
                // -- TODO: 
                // - tomar bprune del config
                // - abrir la tabla ballots balltable(get_self(), get_self().value), tomar la primera entrada
                // - obtener el proximo id: balltable.available_primary_key()
                // - calcular la cantidad de ballots actuales: dif = proximo - entrada.id;
                // - si la dif está pasada del bprune, entonces deletear la primera entrada
                // - si hay cambios -> eosio::dex::record::aux_register_event()
                string report;
                int bprune = eosio::dex::global::get().bprune;
                PRINT(" -> bprune: ",bprune," \n");

                ballots balltable(get_self(), get_self().value);
                auto ptr = balltable.begin();

                time_point_sec _now = eosio::dex::global::get_now_time_point_sec();

                if (ptr != balltable.end()) {
                    PRINT(" -> ptr->num: ",std::to_string((unsigned long)ptr->id)," \n");
                    uint64_t next_id = balltable.available_primary_key();
                    PRINT(" -> next_id: ",std::to_string((unsigned long)next_id)," \n");
                    uint64_t dif = next_id - ptr->id;
                    PRINT(" -> dif: ",std::to_string((unsigned long)dif)," \n");
                    if (dif > bprune) {
                        // discard ballot if not finished
                        PRINT(" -> _now:          ",std::to_string((unsigned long)_now.utc_seconds)," \n");
                        PRINT(" -> itr->finished: ",std::to_string((unsigned long)ptr->finished.utc_seconds)," \n");
                        if (ptr->finished < _now) {
                            report += string("|ballots-prune:") + ptr->ballot_name.to_string();
                            // eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("ballots-prune|") + ptr->ballot_name.to_string());
                            PRINT("  => ballots.erase(): ",std::to_string((unsigned long)ptr->id), "\n");
                            balltable.erase(*ptr);
                        } else {
                            PRINT(" -> we skip ballot because is not finished: ",std::to_string((unsigned long)ptr->id)," \n");         
                        }                       
                    }
                }

                PRINT("eosio::dex::maintenance::aux_maintenance_from_ballots() ...\n");
                return report;
            }

            void action_do_maintenance() {
                PRINT("eosio::dex::maintenance::action_do_maintenance() ------------------------------\n");
                string report;
                PRINT("       --------------------------------\n");
                PRINT("       -- MAINTENANCE: delmarkets    --\n");
                report += aux_maintenance_from_delmarkets();
                
                PRINT("       --------------------------------\n");
                PRINT("       -- MAINTENANCE: history       --\n");
                report += aux_maintenance_from_history();

                PRINT("       --------------------------------\n");
                PRINT("       -- MAINTENANCE: events        --\n");
                report += aux_maintenance_from_events();

                PRINT("       --------------------------------\n");
                PRINT("       -- MAINTENANCE: ballots       --\n");
                report += aux_maintenance_from_ballots();

                if (report.size() > 0) {
                    eosio::dex::record::aux_register_event(get_self(), name("maintenance"), string("detail") + report);
                }

                PRINT("eosio::dex::maintenance::action_do_maintenance() ------------------------------ (end)\n");
            }
        };     
    };
};
