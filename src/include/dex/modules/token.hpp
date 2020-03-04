#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>

using namespace std;

namespace eosio {
    namespace dex {
        using namespace utils;
        
        namespace token {
            
            void action_add_token(name contract, const symbol_code & sym_code, uint8_t precision, name admin) {
                PRINT("vapaee::token::exchange::action_add_token()\n");
                PRINT(" contract: ", contract.to_string(), "\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" precision: ", std::to_string((unsigned) precision), "\n");
                PRINT(" admin: ", admin.to_string(), "\n");
                
                stats statstable( contract, sym_code.raw() );
                auto token_itr = statstable.find( sym_code.raw() );
                check( token_itr != statstable.end(), "token with symbol not exists" );
                
                check(has_auth(get_self()) || has_auth(contract) || has_auth(token_itr->issuer), "only token contract or issuer can add this token to DEX" );

                tokens tokenstable(get_self(), get_self().value);
                auto itr = tokenstable.find(sym_code.raw());
                check(itr == tokenstable.end(), "Token already registered");
                tokenstable.emplace( admin, [&]( auto& a ){
                    a.contract  = contract;
                    a.symbol    = sym_code;
                    a.precision = precision;
                    a.admin     = admin;
                    a.title     = "";
                    a.website   = "";
                    a.brief     = "";
                    a.banner    = "";
                    a.icon      = "";
                    a.iconlg    = "";
                    a.tradeable = false;
                    a.ballot    = name();
                    a.date      = time_point_sec(current_time_point().sec_since_epoch());
                    a.data      = 0;
                });
                PRINT(" -> tokenstable.emplace() OK\n");
                
                PRINT("vapaee::token::exchange::action_add_token() ...\n");
            }

            void action_update_token_info(const symbol_code & sym_code, string title, string website, string brief, string banner, string icon, string iconlg, bool tradeable) {
                PRINT("vapaee::token::exchange::action_update_token_info()\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" title: ", title.c_str(), "\n");
                PRINT(" website: ", website.c_str(), "\n");
                PRINT(" brief: ", brief.c_str(), "\n");
                PRINT(" banner: ", banner.c_str(), "\n");
                PRINT(" icon: ", icon.c_str(), "\n");
                PRINT(" iconlg: ", iconlg.c_str(), "\n");
                PRINT(" tradeable: ", std::to_string(tradeable), "\n");

                tokens tokenstable(get_self(), get_self().value);
                auto itr = tokenstable.find(sym_code.raw());
                check(itr != tokenstable.end(), "Token not registered. You must register it first calling addtoken action");
                name admin = itr->admin;
                check(has_auth(get_self()) || has_auth(admin), "only admin or token's admin can modify the token main info");

                tokenstable.modify( *itr, same_payer, [&]( auto& a ){
                    a.title     = title;
                    a.website   = website;
                    a.brief     = brief;
                    a.banner    = banner;
                    a.icon      = icon;
                    a.iconlg    = iconlg;
                    a.tradeable = tradeable;
                    a.date      = time_point_sec(current_time_point().sec_since_epoch());
                });

                PRINT("vapaee::token::exchange::action_update_token_info() ...\n");
            }
            
            void action_set_token_admin (const symbol_code & sym_code, name newadmin) {
                PRINT("vapaee::token::exchange::action_set_token_admin()\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" newadmin: ", newadmin.to_string(), "\n");

                tokens tokenstable(get_self(), get_self().value);
                auto itr = tokenstable.find(sym_code.raw());
                check(itr != tokenstable.end(), "Token not registered. You must register it first calling addtoken action");

                check( is_account( newadmin ), "newadmin account does not exist");
                check(has_auth(get_self()) || has_auth(itr->admin), "only DAO or token's admin can change token admin");

                tokenstable.modify( *itr, same_payer, [&]( auto& a ){
                    a.admin = newadmin;
                });

                PRINT("vapaee::token::exchange::action_set_token_admin() ...\n");
            }
            
            void action_set_token_as_currency (const symbol_code & sym_code, bool is_currency) {
                PRINT("vapaee::token::exchange::action_set_token_as_currency()\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" is_currency: ", std::to_string(is_currency), "\n");

                tokens tokenstable(get_self(), get_self().value);
                auto itr = tokenstable.find(sym_code.raw());
                check(itr != tokenstable.end(), "Token not registered. You must register it first calling addtoken action");
                
                check(has_auth(get_self()), "only admin can modify the token.currency status");

                tokenstable.modify( *itr, same_payer, [&]( auto& a ){
                    a.currency = is_currency;
                });

                PRINT("vapaee::token::exchange::action_set_token_as_currency() ...\n");
            }

            void action_set_token_data (const symbol_code & sym_code, uint64_t id, name action, name category, string text, string link) {
                PRINT("vapaee::token::exchange::action_set_token_data()\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" id: ", std::to_string((unsigned long) id), "\n");
                PRINT(" action: ", action.to_string(), "\n");
                PRINT(" category: ", category.to_string(), "\n");
                PRINT(" text: ", text.c_str(), "\n");
                PRINT(" link: ", link.c_str(), "\n"); 

                tokens tokenstable(get_self(), get_self().value);
                auto tkitr = tokenstable.find(sym_code.raw());
                check(tkitr != tokenstable.end(), "Token not registered. You must register it first calling addtoken action");
                name admin = tkitr->admin;
                check(has_auth(get_self()) || has_auth(admin), "only admin or token's admin can modify the token data");
                name ram_payer = admin;
                if (has_auth(get_self())) {
                    ram_payer = get_self();
                }

                require_auth( ram_payer );

                tokendata tokendatatable(get_self(), sym_code.raw());
                auto itr = tokendatatable.find(id);
                if (action == name("add")) {
                    tokendatatable.emplace( ram_payer, [&]( auto& a ){
                        a.id        = tokendatatable.available_primary_key();
                        a.category  = category;
                        a.text      = text;
                        a.link      = link;
                        a.date      = time_point_sec(current_time_point().sec_since_epoch());
                    });
                    tokenstable.modify(*tkitr, same_payer, [&]( auto& a){
                        a.data++;
                    });
                } else {
                    check(itr != tokendatatable.end(), "No action can be performed on entry with this id because it does not exist");
                    if (action == name("remove")) {
                        tokendatatable.erase(*itr);
                        tokenstable.modify(*tkitr, same_payer, [&]( auto& a){
                            a.data--;
                            check(a.data >= 0, "Data inconsistency");
                        });
                    } else {
                        tokendatatable.modify(*itr, same_payer, [&](auto& a){
                            a.category  = category;
                            a.text      = text;
                            a.link      = link;
                            a.date      = time_point_sec(current_time_point().sec_since_epoch());
                        });
                    }
                }
                
                PRINT("vapaee::token::exchange::action_set_token_data() ...\n");            
            }

            void action_edit_token_event(const symbol_code & sym_code, name event, name action, name receptor) {
                PRINT("vapaee::token::exchange::action_edit_token_event()\n");
                PRINT(" sym_code: ", sym_code.to_string(), "\n");
                PRINT(" event: ", event.to_string(), "\n");
                PRINT(" action: ", action.to_string(), "\n");
                PRINT(" receptor: ", receptor.to_string(), "\n");


                bool event_ok = false;
                if (!event_ok && event == name("withdraw"))     event_ok = true;
                if (!event_ok && event == name("deposit"))      event_ok = true;
                if (!event_ok && event == name("swapdeposit"))  event_ok = true;
                if (!event_ok && event == name("order"))        event_ok = true;
                if (!event_ok && event == name("cancel"))       event_ok = true;
                if (!event_ok && event == name("deal"))         event_ok = true;

                if (!event_ok) {
                    string error = string("'") + event.to_string() + "' is not a valid event ('withdraw', 'deposit', 'swapdeposit', 'order', 'cancel', 'deal')";
                    check(event_ok, error.c_str());
                }
                
                tokens tokenstable(get_self(), get_self().value);
                auto tkitr = tokenstable.find(sym_code.raw());
                check(tkitr != tokenstable.end(), "Token not registered. You must register it first calling addtoken action");
                name admin = tkitr->admin;
                check(has_auth(get_self()) || has_auth(admin), "only admin or token's admin can modify the token data");
                name ram_payer = admin;
                if (has_auth(get_self())) {
                    ram_payer = get_self();
                }

                require_auth( ram_payer );

                tokenevents tokeneventstable(get_self(), sym_code.raw());
                auto itr = tokeneventstable.find(event.value);
                if (action == name("add")) {
                    check(itr == tokeneventstable.end(), "The event is already registered. User action 'modify' instead of 'add'");
                    tokeneventstable.emplace( ram_payer, [&]( auto& a ){
                        a.event     = event;
                        a.receptor  = receptor;
                    });
                } else {
                    check(itr != tokeneventstable.end(), "No action can be performed on entry with this id because it does not exist");
                    if (action == name("remove")) {
                        tokeneventstable.erase(*itr);
                    } else {
                        tokeneventstable.modify(*itr, same_payer, [&](auto& a){
                            a.receptor  = receptor;
                        });
                    }
                }

                PRINT("vapaee::token::exchange::action_edit_token_event()...\n");
            }

            
        };     
    };
};
