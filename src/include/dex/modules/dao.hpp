#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace dao {
            
            void action_start_ballot_on (name property, vector<string> params, name feepayer) {
                PRINT("vapaee::token::dao::action_start_ballot_on()\n");
                PRINT(" property: ", property.to_string(), "\n");
                for (int i=0; i<params.size(); i++) {
                    PRINT(" params[",i,"]: ", params[i].c_str(), "\n");
                }
                PRINT(" feepayer: ", feepayer.to_string(), "\n");

                // TODO: 
                // - validar el property
                // - validar los params
                // - averiguar en telos.decide:config cuanto es el fee por ballot
                // - descontar de los depósitos de feepayer el fee de un ballot
                // - mandar los fondos (TLOS) a telos.decide a nombre de este contrato
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

            void action_start_vote_on (name property, uint64_t ballotid, uint8_t vote) {
                PRINT("eosio::dex::dao::action_start_vote_on()\n");
                PRINT(" property: ", property.to_string(), "\n");
                PRINT(" ballotid: ", std::to_string((unsigned long)ballotid), "\n");
                PRINT(" vote: ", std::to_string(vote), "\n");

                PRINT("eosio::dex::dao::action_start_vote_on() ...\n");
            }
            
        };     
    };
};
