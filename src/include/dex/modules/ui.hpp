#pragma once
#include <dex/base.hpp>
#include <dex/errors.hpp>
#include <dex/tables.hpp>
#include <dex/modules/utils.hpp>

namespace eosio {
    namespace dex {

        using namespace utils;

        namespace ui {
            
            void aux_assert_ui_is_valid(uint64_t ui) {
                PRINT("eosio::dex::ui::aux_assert_ui_is_valid()\n");
                PRINT(" ui: ", std::to_string((long unsigned) ui), "\n");

                interfaces uitable(get_self(), get_self().value);
                auto ptr = uitable.find(ui);
                check(ptr != uitable.end(), create_error_id1(ERROR_ACUE_1, ui).c_str());

                PRINT("eosio::dex::ui::aux_assert_ui_is_valid() ...\n");
            }

            void action_add_ui(name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail) {
                PRINT("eosio::dex::ui::action_add_ui()\n");
                PRINT(" admin: ", admin.to_string(), "\n");
                PRINT(" receiver: ", receiver.to_string(), "\n");
                PRINT(" params: ", params.c_str(), "\n");
                PRINT(" title: ", title.c_str(), "\n");
                PRINT(" website: ", website.c_str(), "\n");
                PRINT(" brief: ", brief.c_str(), "\n");
                PRINT(" banner: ", banner.c_str(), "\n");
                PRINT(" thumbnail: ", thumbnail.c_str(), "\n");

                // receiver and admin must exist
                check( is_account( receiver ), create_error_name1(ERROR_AAU_1, receiver).c_str());
                check( is_account( admin ), create_error_name1(ERROR_AAU_2, admin).c_str());

                // signature and ram payer
                name rampayer = admin;
                if (has_auth(get_self())) {
                    rampayer = get_self();
                } else {
                    check(has_auth(admin), create_error_name1(ERROR_AAU_3, admin).c_str());
                }

                interfaces uitable(eosio::dex::get_self(), get_self().value);
                
                uint64_t ui = uitable.available_primary_key();
                uitable.emplace(rampayer, [&]( auto& a ){
                    a.id        = ui;
                    a.admin     = admin;
                    a.receiver  = receiver;
                    a.params    = params;
                    a.title     = title;
                    a.website   = website;
                    a.brief     = brief;
                    a.banner    = banner;
                    a.thumbnail = thumbnail;
                    a.state     = "";
                    a.date      = time_point_sec(current_time_point().sec_since_epoch());
                });

                PRINT(" -> emplace: ", receiver.to_string(), " with id ", std::to_string((unsigned) ui), "\n");

                PRINT("eosio::dex::ui::action_add_ui() ...\n");
            }

            void action_update_ui(uint64_t ui, name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail) {
                PRINT("eosio::dex::ui::action_add_ui()\n");
                PRINT(" ui: ", std::to_string((unsigned) ui), "\n");
                PRINT(" admin: ", admin.to_string(), "\n");
                PRINT(" receiver: ", receiver.to_string(), "\n");
                PRINT(" params: ", params.c_str(), "\n");
                PRINT(" title: ", title.c_str(), "\n");
                PRINT(" website: ", website.c_str(), "\n");
                PRINT(" brief: ", brief.c_str(), "\n");
                PRINT(" banner: ", banner.c_str(), "\n");
                PRINT(" thumbnail: ", thumbnail.c_str(), "\n");

                // receiver and admin must exist
                check( is_account( receiver ), create_error_name1(ERROR_AUU_1, receiver).c_str());
                check( is_account( admin ), create_error_name1(ERROR_AUU_2, admin).c_str());

                // signature and ram payer
                name rampayer = admin;
                if (has_auth(get_self())) {
                    rampayer = same_payer;
                } else {
                    check(has_auth(admin), create_error_name1(ERROR_AUU_3, admin).c_str());
                }

                // check tuple existance
                aux_assert_ui_is_valid(ui);
                
                // update table
                interfaces uitable(get_self(), get_self().value);
                auto ptr = uitable.find(ui);
                uitable.modify( *ptr, rampayer, [&](auto & a){
                    a.admin     = admin;
                    a.receiver  = receiver;
                    a.params    = params;
                    a.title     = title;
                    a.website   = website;
                    a.brief     = brief;
                    a.banner    = banner;
                    a.thumbnail = thumbnail;
                    a.date      = time_point_sec(current_time_point().sec_since_epoch());
                });

                PRINT(" -> modify: ", receiver.to_string(), " with id ", std::to_string((unsigned) ui), "\n");

                PRINT("eosio::dex::ui::action_update_ui() ...\n");
            }
            
        };     
    };
};
