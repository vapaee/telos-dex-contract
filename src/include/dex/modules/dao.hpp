#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace dao {

            const name decide = name("telos.decide");

            // telos.decide table structs ------------------
            struct config {
                string app_name;
                string app_version;
                asset total_deposits;
                map<name, asset> fees;     //ballot, treasury, archival
                map<name, uint32_t> times; //balcooldown, minballength, forfeittime

                uint64_t primary_key() const { return 0; }
            };

            typedef eosio::multi_index< "depusers"_n, config > config_table;

            config aux_get_telos_decide_config() {
                config_table configs(eosio::dex::dao::decide, eosio::dex::dao::decide.value);
                auto ptr = configs.begin();
                check(ptr != configs.end(), create_error_name1(ERROR_AGTDC_1, eosio::dex::dao::decide).c_str()); 
                return *ptr;
            }

            asset aux_get_telos_decide_ballot_fee() {
                config configs = aux_get_telos_decide_config();
                return configs.fees[name("ballot")];
            }

            // ---------------------------------------------

            symbol_code aux_check_symbol_code_from_string(string str) {
                symbol_code sym_code(str.c_str());
                tokens tokens_table(get_self(), get_self().value);
                auto ptr = tokens_table.find(sym_code.raw());
                check(ptr != tokens_table.end(), create_error_symcode1(ERROR_ACSCFS_1, sym_code).c_str());
                return sym_code;
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
                    property != name("delisttoken") && 
                    property != name("makerfee")    && 
                    property != name("takerfee")    && 
                    property != name("setcurrency") && 
                    property != name("historyprune")
                ) {
                    check(false, create_error_name1(ERROR_ASBO_1, property).c_str());
                }


                // validating params
                if (property == name("bantoken")    || 
                    property == name("delisttoken") || 
                    property == name("setcurrency")
                ) {
                    string param1 = params[0];
                    symbol_code sym_code = aux_check_symbol_code_from_string(param1);
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

                // at this point it should be a treasure created for VOTE token in telos decide contract

                // at this point it this contract name should be registered as votter in tat treasury

                // create ballot
                name ballot_name = property;
                name category = 
                action(
                    permission_level{get_self(),name("active")},
                    eosio::dex::SYS_TKN_CONTRACT,
                    name("newballot"),
                    std::make_tuple(get_self(), eosio::dex::dao::decide, ballot_fee, string("deposit"))
                ).send();


name ballot_name, name category, name publisher,  
    symbol treasury_symbol, name voting_method, vector<name> initial_options

                // TODO: 
                // + validar el property
                // + validar los params
                // + averiguar en telos.decide:config cuanto es el fee por ballot
                // + descontar de los depósitos de feepayer el fee de un ballot
                // + mandar los fondos (TLOS) a telos.decide a nombre de este contrato
                // - crear un ballot y de algún modo recuperar una referencia a ese ballot (un ballotid?)
                // - openvote para ese ballot?
                // - guardar localmente que se ha iniciado un ballot -> guardar la invocación y el ballotid
                

                PRINT("vapaee::token::dao::action_start_ballot_on() ...\n");
            }

            void handler_ballor_result(name ballot_name, map<name, asset> final_results, uint32_t total_voters) {
                PRINT("eosio::dex::dao::handler_ballor_result()\n");
                PRINT(" property: ", ballot_name.to_string(), "\n");
                for (int i=0; i<final_results.size(); i++) {
                for (auto it = final_results.begin(); it != final_results.end(); ++it)
                    PRINT(" final_results[",it->first.to_string(),"]: ", it->second.to_string(), "\n");
                }                
                PRINT(" total_voters: ", std::to_string((unsigned long)total_voters), "\n");

                // TODO: 
                // - ir a las tabla de cambios en curso y ver si existe una para ballot_name
                // - si el resultado es positivo, ejecutar los cambios según el caso (hay que hacer N sub funciones y un switch-case con las props)
                // https://github.com/telosnetwork/telos-decide/tree/master/contracts/decide

                PRINT("eosio::dex::dao::handler_ballor_result() ...\n");
            }
            
        };     
    };
};
