#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace market {

            bool aux_is_it_allowed_to_cerate_this_market(const symbol_code & A, const symbol_code & B) {
                PRINT("vapaee::token::exchange::aux_is_it_allowed_to_cerate_this_market()\n");
                PRINT(" A: ", A.to_string(), "\n");
                PRINT(" B: ", B.to_string(), "\n");

                tokens tokenstable(get_self(), get_self().value);
                auto atk_itr = tokenstable.find(A.raw());
                auto btk_itr = tokenstable.find(B.raw());
                
                check(atk_itr != tokenstable.end(), create_error_symcode1(ERROR_AIIATCTM_1, A).c_str());
                check(btk_itr != tokenstable.end(), create_error_symcode1(ERROR_AIIATCTM_2, B).c_str());
                check(atk_itr != btk_itr,           create_error_symcode1(ERROR_AIIATCTM_3, A).c_str());

                bool allowed = false;
                if (atk_itr->currency) {
                    allowed = true;
                }
                if (btk_itr->currency) {
                    allowed = true;
                }
                if (atk_itr->group > 0 && atk_itr->group == btk_itr->group) {
                    allowed = true;
                }

                PRINT("vapaee::token::exchange::aux_is_it_allowed_to_cerate_this_market()...\n");
                return allowed;
            }

            uint64_t aux_get_market_id(const symbol_code& A, const symbol_code& B) {
                PRINT("vapaee::token::exchange::aux_get_market_id()\n");
                PRINT(" A: ", A.to_string(), "\n");
                PRINT(" B: ", B.to_string(), "\n");
                uint64_t market = 0;
                markets mktable(get_self(), get_self().value);
                auto index = mktable.get_index<name("name")>();
                

                name scope_canonical = aux_get_canonical_scope_for_symbols(A, B);
                name scope_b = aux_get_scope_for_tokens(A, B);
                
                for (auto itr = index.lower_bound(scope_b.value); itr != index.end(); itr++) {
                    if (itr->name == scope_b) {
                        if (itr->commodity == A && itr->currency == B) {
                            return itr->id;
                        }
                    } else {
                        break;
                    }
                }

                // Is it allowed to create this market?
                if (!aux_is_it_allowed_to_cerate_this_market(A,B)) {
                    check(false, create_error_symcode2(ERROR_AGMI_1, A,B).c_str());
                }
            
                symbol_code commodity = A;
                symbol_code currency = B;
                uint64_t id = mktable.available_primary_key();
                market = id;
                if (scope_canonical != scope_b) {
                    commodity = B;
                    currency = A;
                    market++;
                }
                PRINT("  mktable.emplace() id\n", std::to_string((unsigned) id), scope_canonical.to_string(), "\n");
                mktable.emplace(get_self(), [&](auto & a){
                    a.id = id;
                    a.name = scope_canonical;
                    a.commodity = commodity;
                    a.currency = currency;
                });
                name scope_inv = aux_get_scope_for_tokens(currency, commodity);
                PRINT("  mktable.emplace() id+1\n", std::to_string((unsigned) id+1), scope_canonical.to_string(), "\n");
                mktable.emplace(get_self(), [&](auto & a){
                    a.id = id+1;
                    a.name = scope_inv;
                    a.commodity = currency;
                    a.currency = commodity;
                });

                PRINT("vapaee::token::exchange::aux_get_market_id()...\n");
                return market;
            }            

            uint64_t aux_get_canonical_market(const symbol_code & A, const symbol_code & B) {
                name scope_a = aux_get_canonical_scope_for_symbols(A, B);
                name scope_b = aux_get_scope_for_tokens(A, B);
                if (scope_a == scope_b) return aux_get_market_id(A, B);
                if (scope_a != scope_b) return aux_get_market_id(B, A);
                return 0;
            }

            uint64_t aux_get_inverted_market(const symbol_code & A, const symbol_code & B) {
                name scope_a = aux_get_canonical_scope_for_symbols(A, B);
                name scope_b = aux_get_scope_for_tokens(A, B);
                if (scope_a != scope_b) return aux_get_market_id(A, B);
                if (scope_a == scope_b) return aux_get_market_id(B, A);
                return 0;
            }

            name aux_get_table_from_market(uint64_t market_id) {
                PRINT("vapaee::token::exchange::aux_get_table_from_market()\n");
                PRINT(" market_id: ", std::to_string((unsigned long) market_id), "\n");
                markets mktable(get_self(), get_self().value);
                auto market = mktable.get(market_id,  create_error_id1(ERROR_AGTFM_1, market_id).c_str());
                PRINT("vapaee::token::exchange::aux_get_table_from_market()...\n");
                return market.name;
            }

        };
    };
};
