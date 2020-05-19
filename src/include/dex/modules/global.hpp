#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/error.hpp>

namespace eosio {
    namespace dex {

        using namespace error;        

        namespace global {

            const symbol system_symbol = symbol(symbol_code("TLOS"), 4);
            const symbol fee_symbol = symbol(symbol_code("FEE"), 8);


            inline global_state_singleton get_singleton() {
                return global_state_singleton(get_self(), get_self().value);
            };

            state get() {
                check(get_singleton().exists(), create_error_name1(ERROR_GC_1, name("state")).c_str());
                return get_singleton().get();
            }

            void set( const state& conf) {
                state entry_stored = get();
                entry_stored.maker_fee = conf.maker_fee;
                entry_stored.taker_fee = conf.taker_fee;
                entry_stored.hprune = conf.hprune;
                entry_stored.bprune = conf.bprune;
                entry_stored.eprune = conf.eprune;
                entry_stored.regcost = conf.regcost;
                entry_stored.next_market = conf.next_market;
                AUX_DEBUG_CODE(entry_stored.time_offset = conf.time_offset;)
                get_singleton().set(entry_stored, get_self());
            }


            time_point_sec get_now_time_point_sec() {
                PRINT("eosio::dex::global::get_now_time_point_sec()\n");

                uint32_t offset = 0;
                PRINT(" -> offset: ", std::to_string((unsigned long)offset), "\n");
                AUX_DEBUG_CODE(
                    offset = get().time_offset;
                    PRINT(" -> offset: ", std::to_string((unsigned long)offset), " (updated)\n");
                )
                time_point_sec _now = time_point_sec(current_time_point().sec_since_epoch() - offset);
                
                PRINT(" -> _now: ", std::to_string((unsigned long)_now.utc_seconds), " (updated)\n");
                PRINT("eosio::dex::global::get_now_time_point_sec() ...\n");
                return _now;
            }            

            void init() {
                PRINT("eosio::dex::global::init()\n");
                //authenticate
                require_auth(get_self());

                //open state singleton
                global_state_singleton states(get_self(), get_self().value);

                //validate
                check(!states.exists(), ERROR_AIC_1);

                state new_state;
                new_state.taker_fee = asset(2500000, fee_symbol);
                new_state.maker_fee = asset(1500000, fee_symbol);
                new_state.hprune = 365; // 365 days old history entry should be considered expired and must be deleted
                new_state.bprune = 100; // no more than 100 entries allowed in the ballots table.
                new_state.eprune = 60; // 60 days old event should be considered expired and must be deleted
                new_state.regcost = asset(1000000, system_symbol);
                new_state.next_market = 0;
                AUX_DEBUG_CODE(new_state.time_offset = 0;)

                states.set(new_state, get_self());
                PRINT("eosio::dex::global::init() ...\n");
            }
            

            AUX_DEBUG_CODE(
                void action_set_time_offset(uint32_t offset) {
                    PRINT("eosio::dex::global::action_set_time_offset()\n");
                    PRINT(" offset: ", offset, "\n");
                    auto state = get();
                    state.time_offset = offset;
                    set(state);
                    PRINT("eosio::dex::global::action_set_time_offset() ...\n");
                }
            )
            

            
        };     
    };
};
