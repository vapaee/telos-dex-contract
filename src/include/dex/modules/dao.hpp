#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>
#include <dex/modules/deposit.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace dao {

            const name decide = name("telos.decide");

            // telos.decide table structs ------------------
            struct config_struct {
                string app_name;
                string app_version;
                asset total_deposits;
                map<name, asset> fees;     //ballot, treasury, archival
                map<name, uint32_t> times; //balcooldown, minballength, forfeittime

                uint64_t primary_key() const { return 0; }
            };

            typedef eosio::multi_index< "tdconfig"_n, config_struct > config_table;

            struct ballot {
                name ballot_name;
                name category; //proposal, referendum, election, poll, leaderboard
                name publisher;
                name status; //setup, voting, closed, cancelled, archived

                string title; //markdown
                string description; //markdown
                string content; //IPFS link to content or markdown

                symbol treasury_symbol; //treasury used for counting votes
                name voting_method; //1acct1vote, 1tokennvote, 1token1vote, 1tsquare1v, quadratic
                uint8_t min_options; //minimum options per voter
                uint8_t max_options; //maximum options per voter
                map<name, asset> options; //option name -> total weighted votes

                uint32_t total_voters; //number of voters who voted on ballot
                uint32_t total_delegates; //number of delegates who voted on ballot
                asset total_raw_weight; //total raw weight cast on ballot
                uint32_t cleaned_count; //number of expired vote receipts cleaned
                map<name, bool> settings; //setting name -> on/off
                
                time_point_sec begin_time; //time that voting begins
                time_point_sec end_time; //time that voting closes

                uint64_t primary_key() const { return ballot_name.value; }
                uint64_t by_category() const { return category.value; }
                uint64_t by_status() const { return status.value; }
                uint64_t by_symbol() const { return treasury_symbol.code().raw(); }
                uint64_t by_end_time() const { return static_cast<uint64_t>(end_time.utc_seconds); }
                
                EOSLIB_SERIALIZE(ballot, 
                    (ballot_name)(category)(publisher)(status)
                    (title)(description)(content)
                    (treasury_symbol)(voting_method)(min_options)(max_options)(options)
                    (total_voters)(total_delegates)(total_raw_weight)(cleaned_count)(settings)
                    (begin_time)(end_time))
            };
            typedef multi_index<name("ballots"), ballot,
                indexed_by<name("bycategory"), const_mem_fun<ballot, uint64_t, &ballot::by_category>>,
                indexed_by<name("bystatus"), const_mem_fun<ballot, uint64_t, &ballot::by_status>>,
                indexed_by<name("bysymbol"), const_mem_fun<ballot, uint64_t, &ballot::by_symbol>>,
                indexed_by<name("byendtime"), const_mem_fun<ballot, uint64_t, &ballot::by_end_time>>
            > decide_ballots_table;

            config_struct aux_get_telos_decide_config() {
                config_table configs(eosio::dex::dao::decide, eosio::dex::dao::decide.value);
                auto ptr = configs.begin();
                check(ptr != configs.end(), create_error_name1(ERROR_AGTDC_1, eosio::dex::dao::decide).c_str()); 
                return *ptr;
            }

            asset aux_get_telos_decide_ballot_fee() {
                config_struct configs = aux_get_telos_decide_config();
                return configs.fees[name("ballot")];
            }

            name aux_get_available_ballot_name() {
                decide_ballots_table ballots(eosio::dex::dao::decide, eosio::dex::dao::decide.value);
                return name(ballots.available_primary_key());
            }

            // ---------------------------------------------
            uint8_t char_to_value( char c ) {
                if( c == '.')
                    return 0;
                else if( c >= '1' && c <= '5' )
                    return (c - '1') + 1;
                else if( c >= 'a' && c <= 'z' )
                    return (c - 'a') + 6;
                else
                    eosio::check( false, create_error_string1(ERROR_CTV_1, std::to_string(c)).c_str());

                return 0;
            }

            name aux_check_name_from_string(string str) {
                uint64_t value = 0;
                if( str.size() > 13 ) {
                    eosio::check( false, create_error_string1(ERROR_ACNFS_1, str).c_str());
                }
                if( str.empty() ) {
                    eosio::check( false, create_error_string1(ERROR_ACNFS_2, str).c_str());
                }

                auto n = std::min( (uint32_t)str.size(), (uint32_t)12u );
                for( decltype(n) i = 0; i < n; ++i ) {
                    value <<= 5;
                    value |= char_to_value( str[i] );
                }
                value <<= ( 4 + 5*(12 - n) );
                if( str.size() == 13 ) {
                    uint64_t v = char_to_value( str[12] );
                    if( v > 0x0Full ) {
                        eosio::check(false, create_error_string1(ERROR_ACNFS_3, str).c_str());
                    }
                    value |= v;
                }

                return name(value);
            }

            symbol_code aux_check_symbol_code_from_string(string str) {
                uint64_t value = 0;
                if( str.size() > 7 ) {
                    eosio::check( false, create_error_string1(ERROR_ACSCFS_1, str).c_str());
                }
                for( auto itr = str.rbegin(); itr != str.rend(); ++itr ) {
                    if( *itr < 'A' || *itr > 'Z') {
                        eosio::check( false, create_error_string1(ERROR_ACSCFS_2, str).c_str());
                    }
                    value <<= 8;
                    value |= *itr;
                }
                symbol_code code(str.c_str());
                return code;
            }

            double aux_check_double_from_string(string str) {
                double value = std::stod(str.c_str());
                check(value >= 0, create_error_double1(ERROR_ACDFS_1, value).c_str());
                check(value <= 1, create_error_double1(ERROR_ACDFS_2, value).c_str());
                return value;
            }

            uint32_t aux_check_integer_from_string(string str) {
                uint32_t value = std::atoi(str.c_str());
                uint32_t nowsec = current_time_point().sec_since_epoch();
                check(value <= nowsec, create_error_id1(ERROR_ACIFS_1, value).c_str());
                return value;
            }

            bool aux_is_token_whitelisted(const symbol_code &sym_code) {
                whitelist list(get_self(), get_self().value);
                auto index = list.get_index<name("symbol")>();
                auto itr = index.lower_bound(sym_code.raw());
                if (itr != index.end()) {
                    return true;
                }
                return false;
            }

            bool aux_is_token_blacklisted(const symbol_code &sym_code, name contract) {
                blacklist list(get_self(), get_self().value);
                auto index = list.get_index<name("symbol")>();
                auto itr = index.lower_bound(sym_code.raw());
                for (auto itr = index.lower_bound(sym_code.raw()); itr != index.end(); itr++) {
                    if (itr->symbol == sym_code) {
                        if (itr->contract == contract) {
                            return true;
                        }
                    } else {
                        break;
                    }
                }
                return false;
            }

            bool aux_is_token_blacklisted(const symbol_code &sym_code) {
                tokens token_table(get_self(), get_self().value);
                auto ptr = token_table.find(sym_code.raw());
                check(ptr != token_table.end(), create_error_symcode1(ERROR_AITB_1, sym_code).c_str());
                return aux_is_token_blacklisted(sym_code, ptr->contract);
            }

            void aux_process_ballot_to_ban_token(symbol_code & symcode, name contract, name ballot_name) {
                PRINT("eosio::dex::dao::aux_process_ballot_to_ban_token()\n");
                PRINT(" symcode: ", symcode.to_string(), "\n");
                PRINT(" contract: ", contract.to_string(), "\n");
                
                whitelist white_table(get_self(), get_self().value);
                auto wptr = white_table.find(symcode.raw());
                check(wptr == white_table.end(), create_error_symcode1(ERROR_APBTBT_1, symcode).c_str());

                blacklist black_table(get_self(), get_self().value);
                auto bptr = black_table.find(symcode.raw());
                check(bptr != black_table.end(), create_error_symcode1(ERROR_APBTBT_2, symcode).c_str());

                black_table.emplace(get_self(), [&](auto &a){
                    a.id = black_table.available_primary_key();
                    a.symbol = symcode;
                    a.contract = contract;
                    a.ballot = ballot_name;
                });
                
                PRINT("eosio::dex::dao::aux_process_ballot_to_ban_token()\n");
            }

            void action_start_ballot_on (name property, vector<string> params, name feepayer) {
                
                PRINT("vapaee::token::dao::action_start_ballot_on()\n");
                PRINT(" property: ", property.to_string(), "\n");
                for (int i=0; i<params.size(); i++) {
                    PRINT(" params[",i,"]: ", params[i].c_str(), "\n");
                }
                PRINT(" feepayer: ", feepayer.to_string(), "\n");

                require_auth(feepayer);

                // validating property
                if (
                    property != name("bantoken")    && 
                    property != name("savetoken")   && 
                    property != name("makerfee")    && 
                    property != name("takerfee")    && 
                    property != name("setcurrency") && 
                    property != name("historyprune")
                ) {
                    check(false, create_error_name1(ERROR_ASBO_1, property).c_str());
                }

                // validating params
                if (property == name("bantoken")  || 
                    property == name("savetoken") || 
                    property == name("setcurrency")
                ) {
                    string param1 = params[0];
                    string param2 = params[1];
                    symbol_code sym_code = aux_check_symbol_code_from_string(param1);
                    name contract = aux_check_name_from_string(param2);
                }

                if (property == name("makerfee")    || 
                    property == name("takerfee")
                ) {
                    string param1 = params[0];
                    double value = aux_check_double_from_string(param1);
                }

                if (property == name("historyprune")
                ) {
                    string param1 = params[0];
                    uint32_t value = aux_check_integer_from_string(param1);
                }

                // find out what is the ballot fee
                asset ballot_fee = aux_get_telos_decide_ballot_fee();
                check(ballot_fee.symbol.code() == eosio::dex::SYS_TKN_CODE, create_error_asset2(ERROR_ASBO_2, ballot_fee, ballot_fee).c_str());

                // convert to internal 8 decimal representation
                asset extended = aux_extend_asset(ballot_fee);
                
                // charge feepayer for the fees to pay telos.decide ballot service
                eosio::dex::deposit::aux_substract_deposits(feepayer, extended, feepayer);

                // deposit ballot fee in telos decide contract
                action(
                    permission_level{get_self(),name("active")},
                    eosio::dex::SYS_TKN_CONTRACT,
                    name("transfer"),
                    std::make_tuple(get_self(), eosio::dex::dao::decide, ballot_fee, string("deposit"))
                ).send();

                // + at this point it should be a treasure created for VOTE token in telos decide contract
                // + at this point it this contract name should be registered as voter in that treasury

                // create ballot on Telos Decide contract
                name ballot_name = aux_get_available_ballot_name();
                name category = name("poll");
                symbol treasury_symbol = symbol(symbol_code("VOTE"), 4);
                name voting_method = name("1token1vote");
                vector<name> initial_options = {name("yes"), name("no"), name("abstain")};
                action(
                    permission_level{get_self(),name("active")},
                    eosio::dex::dao::decide,
                    name("newballot"),
                    std::make_tuple(
                        ballot_name,
                        category,
                        get_self(),
                        treasury_symbol,
                        voting_method,
                        initial_options
                    )
                ).send();

                // open ballot for votting in Telos Decide contract
                uint32_t _15_days = 15 * 24 * 60 * 60;
                time_point_sec end_time = time_point_sec(current_time_point().sec_since_epoch() + _15_days);

                action(
                    permission_level{get_self(),name("active")},
                    eosio::dex::dao::decide,
                    name("openvoting"),
                    std::make_tuple(
                        ballot_name,
                        end_time
                    )
                ).send();

                ballots ball_table(get_self(), get_self().value);
                auto ptr = ball_table.find(ballot_name.value);
                check(ptr == ball_table.end(), create_error_name1(ERROR_ASBO_3, ballot_name).c_str()); 

                ball_table.emplace(get_self(), [&]( auto &a){
                    a.ballot_name = ballot_name;
                    a.property = property;
                    a.params = params;
                    a.feepayer = feepayer;
                    a.started = time_point_sec(current_time_point().sec_since_epoch());
                    a.finished = time_point_sec::maximum();
                });

                if ( property == name("bantoken") ) {
                    string param1 = params[0];
                    string param2 = params[1];
                    symbol_code sym_code = aux_check_symbol_code_from_string(param1);
                    name contract = aux_check_name_from_string(param2);                    
                    aux_process_ballot_to_ban_token(sym_code, contract, ballot_name);
                }

                PRINT("vapaee::token::dao::action_start_ballot_on() ...\n");
                
            }

            void handler_ballot_result_for_savetoken(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_savetoken()\n");

                string param1 = ballot.params[0];
                string param2 = ballot.params[1];
                symbol_code sym_code = aux_check_symbol_code_from_string(param1);
                name contract = aux_check_name_from_string(param2);          

                whitelist list(get_self(), get_self().value);
                auto index = list.get_index<name("symbol")>();
                auto itr = index.lower_bound(sym_code.raw());

                if (approved) {
                    if (itr != index.end()) {
                        list.emplace(get_self(), [&](auto &a){
                            a.id = list.available_primary_key();
                            a.symbol = sym_code;
                            a.contract = contract;
                            a.ballot = ballot.ballot_name;                            
                        });
                    }
                } else {
                    if (itr != index.end()) {
                        list.erase(*itr);
                    }
                }
                PRINT("vapaee::token::dao::handler_ballot_result_for_savetoken() ...\n");
            }

            void handler_ballot_result_for_bantoken(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_bantoken()\n");

                //     - afirmativo:
                //       - sacarlo de la lista de tokens
                //       - averiaguar en cuantos markets participa y ponerlos en delmarkets
                
                string param1 = ballot.params[0];
                symbol_code sym_code = aux_check_symbol_code_from_string(param1);

                if (approved) {
                    // approved, so the token must be removed from the token list.
                    tokens list(get_self(), get_self().value);
                    auto ptr = list.find(sym_code.raw());
                    check(ptr != list.end(), create_error_symcode1(ERROR_HBRFB_1, sym_code).c_str());

                    if (ptr != list.end()) {
                        list.erase(*ptr);
                    }

                    // delete all markets were this tokens participates
                    aaaaaaaaaaaaaa

                } else {
                    // not approved, so the token must be removed from the blacklist.
                    blacklist blist(get_self(), get_self().value);
                    auto index = blist.get_index<name("symbol")>();
                    auto itr = index.lower_bound(sym_code.raw());

                    if (itr != index.end()) {
                        blist.erase(*itr);
                    }
                }                


                PRINT("vapaee::token::dao::handler_ballot_result_for_bantoken() ...\n");
            }

            void handler_ballot_result_for_makerfee(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_makerfee()\n");

                PRINT("vapaee::token::dao::handler_ballot_result_for_makerfee() ...\n");
            }

            void handler_ballot_result_for_takerfee(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_takerfee()\n");

                PRINT("vapaee::token::dao::handler_ballot_result_for_takerfee() ...\n");
            }

            void handler_ballot_result_for_setcurrency(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_setcurrency()\n");

                PRINT("vapaee::token::dao::handler_ballot_result_for_setcurrency() ...\n");
            }

            void handler_ballot_result_for_historyprune(const ballots_table & ballot, bool approved, uint32_t total_voters) {
                PRINT("vapaee::token::dao::handler_ballot_result_for_historyprune()\n");

                PRINT("vapaee::token::dao::handler_ballot_result_for_historyprune() ...\n");
            }

            void handler_ballot_result(name ballot_name, map<name, asset> final_results, uint32_t total_voters) {
                
                PRINT("eosio::dex::dao::handler_ballot_result()\n");
                PRINT(" ballot_name: ", ballot_name.to_string(), "\n");
                for (int i=0; i<final_results.size(); i++) {
                for (auto it = final_results.begin(); it != final_results.end(); ++it)
                    PRINT(" final_results[",it->first.to_string(),"]: ", it->second.to_string(), "\n");
                }                
                PRINT(" total_voters: ", std::to_string((unsigned long)total_voters), "\n");

                ballots ball_table(get_self(), get_self().value);
                const ballots_table ballot = ball_table.get(ballot_name.value, create_error_name1(ERROR_HBR_1, ballot_name).c_str());
     
                bool approved = final_results[name("yes")].amount > final_results[name("no")].amount;

                switch(ballot.property.value) {
                    case name("savetoken").value:
                        handler_ballot_result_for_savetoken(ballot, approved, total_voters);
                        break;
                    case name("bantoken").value:
                        handler_ballot_result_for_bantoken(ballot, approved, total_voters);
                        break;
                    case name("makerfee").value:
                        handler_ballot_result_for_makerfee(ballot, approved, total_voters);
                        break;
                    case name("takerfee").value:
                        handler_ballot_result_for_takerfee(ballot, approved, total_voters);
                        break;
                    case name("setcurrency").value:
                        handler_ballot_result_for_setcurrency(ballot, approved, total_voters);
                        break;
                    case name("historyprune").value:
                        handler_ballot_result_for_historyprune(ballot, approved, total_voters);
                        break;
                    default:
                        check(false, create_error_name1(ERROR_HBR_2, ballot.property).c_str()); 
                        break;
                }



                PRINT("eosio::dex::dao::handler_ballot_result() ...\n");
                
            }
            
        };     
    };
};
