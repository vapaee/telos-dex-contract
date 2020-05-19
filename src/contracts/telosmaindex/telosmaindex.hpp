#pragma once
#include <dex/base.hpp>
#include <dex/modules/ui.hpp>
#include <dex/modules/token.hpp>
#include <dex/modules/exchange.hpp>
#include <dex/modules/deposit.hpp>
#include <dex/modules/dao.hpp>
#include <dex/modules/maintenance.hpp>
#include <vapaee/dispatcher.spp>

using namespace eosio;
using namespace std;

namespace eosio {
    using namespace dex;

CONTRACT telosmaindex : public eosio::contract {
    
    private:

#include <dex/tables.all.hpp>

    public:
        using contract::contract;

    public:

        // Interface Module ---------------------------------------------------------------------
        
        ACTION addui (name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.addui() ------------------\n");
            eosio::dex::ui::action_add_ui(admin, receiver, params, title, website, brief, banner, thumbnail);
        };
        
        ACTION updateui (uint64_t ui, name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.updateui() ------------------\n");
            eosio::dex::ui::action_update_ui(ui, admin, receiver, params, title, website, brief, banner, thumbnail);
        };

        // Token Module ---------------------------------------------------------------------
        
        ACTION addtoken (name contract, const symbol_code & symbol, uint8_t precision, name admin, string title, string website, string brief, string banner, string icon, string iconlg, string pcontact, string gcontact, bool tradeable) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.addtoken() ------------------\n");
            vector<uint64_t> groups = {0};
            eosio::dex::token::action_add_token(contract, symbol, precision, admin);
            eosio::dex::token::action_update_token_info(symbol, title, website, brief, banner, icon, iconlg, pcontact, gcontact, groups, tradeable);
        };
         
        ACTION updatetoken (const symbol_code & sym_code, string title, string website, string brief, string banner, string icon, string iconlg, string pcontact, string gcontact, vector<uint64_t> groups, bool tradeable) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.updatetoken() ------------------\n");
            eosio::dex::token::action_update_token_info(sym_code, title, website, brief, banner, icon, iconlg, pcontact, gcontact, groups, tradeable);
        };

        ACTION tokenadmin (const symbol_code & sym_code, name admin) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.tokenadmin() ------------------\n");
            eosio::dex::token::action_set_token_admin(sym_code, admin);
        };

        ACTION setcurrency (const symbol_code & sym_code, bool is_currency) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.setcurrency() ------------------\n");
            eosio::dex::token::action_set_token_as_currency(sym_code, is_currency);
        };

        ACTION settokendata (const symbol_code & symbol, uint64_t id, name action, name category, string text, string link) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.updatetoken() ------------------\n");
            eosio::dex::token::action_set_token_data(symbol, id, action, category, text, link);
        };

        ACTION edittkevent (const symbol_code & symbol, name event, name action, name contract) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.edittkevent() ------------------\n");
            eosio::dex::token::action_edit_token_event(symbol, event, action, contract);
        };

        ACTION addtnkgroup (name admin, string title, string website, string brief, string banner, string thumbnail, vector<symbol_code> currencies) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.addtnkgroup() ------------------\n");
            eosio::dex::token::action_add_token_group(admin, title, website, brief, banner, thumbnail, currencies);
        };
        
        ACTION uptnkgroup (uint64_t group_id, name admin, string title, string website, string brief, string banner, string thumbnail, vector<symbol_code> currencies) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.uptnkgroup() ------------------\n");
            eosio::dex::token::action_update_token_group(group_id, admin, title, website, brief, banner, thumbnail, currencies);
        };        

        // Exchange Module ---------------------------------------------------------------------

        ACTION cancel(name owner, name type, const symbol_code & commodity, const symbol_code & currency, const std::vector<uint64_t> & orders) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.cancel() ------------------\n");
            eosio::dex::exchange::action_cancel(owner, type, commodity, currency, orders);
        };

        ACTION order(name owner, name type, const asset & total, const asset & price, uint64_t ui) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.order() ------------------\n");
            eosio::dex::exchange::action_order(owner, type, total, price, ui);
        };

        // Deposit Module ---------------------------------------------------------------------

        ACTION withdraw(name owner, const asset & quantity, uint64_t ui) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.withdraw() ------------------\n");
            eosio::dex::deposit::action_withdraw(owner, quantity, ui);
        };

        ACTION swapdeposit(name from, name to, const asset & quantity, bool trigger, string memo) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.swapdeposit() ------------------\n");
            eosio::dex::deposit::action_swapdeposit(from, to, quantity, trigger, memo);
        };
    
        // habdler for tokenaccount::transfer
        HANDLER htransfer(name from, name to, asset quantity, string  memo ) {
            // MAINTENANCE();
            PRINT("\nHANDLER telosmaindex.htransfer() ------------------\n");
            
            // skip handling outcoming transfers from this contract to outside
            if (from == get_self()) {
                PRINT(from.to_string(), " to ", to.to_string(), ": ", quantity.to_string(), " eosio::telosmaindex::handler_transfer() skip...\n");
                return;
            }
            
            string order_str;
            int i,j,s;
            
            for (i=0,j=0,s=0; i<memo.size(); i++,j++) {
                if (memo[i] == '|') {
                    break;
                } else {
                    order_str += memo[i];
                }
            }
            
            if (order_str == string("deposit")) {
                MAINTENANCE();
                eosio::dex::deposit::handler_transfer(from, to, quantity, memo);                
            }
        }
        

        ACTION deps2earn(const uint64_t ui, const asset & quantity) {
            PRINT("\nACTION telosmaindex.deps2earn() ------------------\n");
            eosio::dex::deposit::action_convert_deposits_to_earnings(ui, quantity);
        };

        // Maintenance Module ---------------------------------------------------------------------
        ACTION maintenance () {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.maintenance() ------------------\n");
            eosio::dex::maintenance::action_do_maintenance();
        };

        // Global Module ---------------------------------------------------------------------
        ACTION init () {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.init() ------------------\n");
            eosio::dex::token::init();
            eosio::dex::global::init();
        };

        
        // DAO Module ---------------------------------------------------------------------

        ACTION balloton (name operation, vector<string> params, string arguments, name feepayer) {
            MAINTENANCE();
            PRINT("\nACTION telosmaindex.balloton() ------------------\n");
            eosio::dex::dao::action_start_ballot_on(operation, params, arguments, feepayer);
        };

        // habdler for telos.decide::breadcast
        HANDLER hbroadcast(name ballot_name, map<name, asset> final_results, uint32_t total_voters) {
            MAINTENANCE();
            PRINT("\nHANDLER telosmaindex.hbroadcast() ------------------\n");
            eosio::dex::dao::handler_ballot_result(ballot_name, final_results, total_voters);
        };
                
        AUX_DEBUG_CODE (

            ACTION testdao (name ballot_name, map<name, asset> final_results, uint32_t total_voters) {
                MAINTENANCE();
                PRINT("\nACTION telosmaindex.testdao() ------------------\n");
                hbroadcast(ballot_name, final_results, total_voters);
            };

            ACTION hotfix (int max, name scope, asset q) {
                PRINT("\nACTION telosmaindex.hotfix() ------------------\n");
                eosio::dex::exchange::action_hotfix(max, scope, q);
            };

            ACTION timeoffset (uint32_t offset) {
                PRINT("\nACTION telosmaindex.timeoffset() ------------------\n");
                eosio::dex::global::action_set_time_offset(offset);
            };

        )


        //      [[eosio::on_notify("telos.decide::broadcast")]]
        

};

}; // eosio namespace