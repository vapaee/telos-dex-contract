#pragma once


// aux_generate_order
 
#define ERROR_AGO_1 "ERR-AGO-01: amount token is blacklisted: "
#define ERROR_AGO_2 "ERR-AGO-02: price token is blacklisted: "


// aux_generate_sell_order
#define ERROR_AGSO_1 "ERR-AGSO-01: symbol mismatch: "
#define ERROR_AGSO_2 "ERR-AGSO-02: symbol mismatch: "
#define ERROR_AGSO_3 "ERR-AGSO-03: symbol mismatch: "
#define ERROR_AGSO_4 "ERR-AGSO-04: symbol mismatch: "
#define ERROR_AGSO_5 "ERR-AGSO-05: symbol mismatch: "
#define ERROR_AGSO_6 "ERR-AGSO-06: symbol mismatch: "
#define ERROR_AGSO_7 "ERR-AGSO-07: symbol mismatch: "
#define ERROR_AGSO_8 "ERR-AGSO-08: symbol mismatch: "


// aux_substract_deposits
#define ERROR_ASD_1 "ERR-ASD-01: user has no deposits for this symbol to subtract from: "
#define ERROR_ASD_2 "ERR-ASD-02: symbol mismatch: "
#define ERROR_ASD_3 "ERR-ASD-03: user has not enought deposits to subtract from: "

// aux_earn_micro_change
#define ERROR_AEMC_1 "ERR-AEMC-01: user has no deposits for this symbol: "
#define ERROR_AEMC_2 "ERR-AEMC-02: internal and external symbols don't match in code: "

// aux_get_market_id
#define ERROR_AGMI_1 "ERR-AGMI-01: This market is not allowed because none of them are currencies and they are not in the same token group: "

// aux_is_it_allowed_to_cerate_this_market
#define ERROR_AIIATCTM_1 "ERR-AIIATCTM-01: This token is not registered: "
#define ERROR_AIIATCTM_2 "ERR-AIIATCTM-02: This token is not registered: "
#define ERROR_AIIATCTM_3 "ERR-AIIATCTM-03: Can't create market. Both tokens are the same: "

// aux_get_table_from_market
#define ERROR_AGTFM_1 "ERR-AGTFM-01: not market found: "

// aux_add_deposits
#define ERROR_AAD_1 "ERR-AAD-01: symbol mismatch: "

// action_add_ui
#define ERROR_AAU_1 "ERR-AAU-01: receiver account does not exist: "
#define ERROR_AAU_2 "ERR-AAU-02: admin account does not exist: "
#define ERROR_AAU_3 "ERR-AAU-03: admin signature needed: "

// action_update_ui
#define ERROR_AUU_1 "ERR-AUU-01: receiver account does not exist: "
#define ERROR_AUU_2 "ERR-AUU-02: admin account does not exist: "
#define ERROR_AUU_3 "ERR-AUU-03: admin signature needed: "

// aux_check_ui_exists
#define ERROR_ACUE_1 "ERR-ACUE-01: interface not found with this id: "

// action_update_ui
#define ERROR_ATETU_1 "ERR-ATETU-01: interface not found with this id: "

// aux_get_real_asset
#define ERROR_AGEA_1 "ERR-AGEA-01: precision mismatch: "


// Token Module ----------------------

// action_update_token_info
#define ERROR_AUTI_1 "ERR-AUTI-01: only admin or token's admin can modify the token main info: " 
#define ERROR_AUTI_2 "ERR-AUTI-02: the token is currently blacklisted: " 

// action_add_token
#define ERROR_AAT_1 "ERR-AAT-01: Token with symbol not exists: " 
#define ERROR_AAT_2 "ERR-AAT-02: Token already registered: " 


// action_set_token_admin
#define ERROR_ASTA_1 "ERR-ASTA-01: Token not registered. You must register it first calling addtoken action: " 
#define ERROR_ASTA_2 "ERR-ASTA-02: account does not exist: " 
#define ERROR_ASTA_3 "ERR-ASTA-03: only DAO or token's admin can change token admin" 

// DAO Module ------------------------

// action_start_ballot_on
#define ERROR_ASBO_1 "ERR-ASBO-01: unknown property: "
#define ERROR_ASBO_2 "ERR-ASBO-02: telos.decide fee symbol_code and system symbol_code does not match?: "
#define ERROR_ASBO_3 "ERR-ASBO-03: ballot_name already exists: "


// aux_check_symbol_code_from_string
#define ERROR_ACSCFS_1 "ERR-ACSCFS-01: string is too long to be a valid symbol_code: "
#define ERROR_ACSCFS_2 "ERR-ACSCFS-02: thirteenth character in name cannot be a letter that comes after j: "

// aux_check_name_from_string
#define ERROR_ACNFS_1 "ERR-ACNFS-01: contract name is too long to be a valid name: "
#define ERROR_ACNFS_2 "ERR-ACNFS-02: contract name can not be empty: "
#define ERROR_ACNFS_3 "ERR-ACNFS-03: thirteenth character of contract name cannot be a letter that comes after j: "

// char_to_value
#define ERROR_CTV_1 "ERR-CTV-1: character is not in allowed character set for names: "

// aux_check_double_from_string
#define ERROR_ACDFS_1 "ERR-ACDFS-01: Fee can not be negative: "
#define ERROR_ACDFS_2 "ERR-ACDFS-02: Fee can not higher than 1: "

// aux_check_integer_from_string
#define ERROR_ACIFS_1 "ERR-ACIFS-02: Cant prune future records: "

// aux_get_telos_decide_config
#define ERROR_AGTDC_1 "ERR-AGTDC-02: Cant prune future records: "

// aux_is_token_blacklisted
#define ERROR_AITB_1 "ERR-AITB-01: Token is not registered: " 

// aux_process_ballot_to_ban_token
#define ERROR_APBTBT_1 "ERR-APBTBT-01: This token can't be banned because it belongs to the DEX token white list: " 
#define ERROR_APBTBT_2 "ERR-APBTBT-02: This token is already blacklisted: " 

// handler_ballot_result
#define ERROR_HBR_1 "ERR-HBR-01: could't find a ballot identified: "
#define ERROR_HBR_2 "ERR-HBR-02: property not valid: "

// handler_ballot_result_for_bantoken
#define ERROR_HBRFB_1 "ERR-HBRFB-01: Symbol is not part of the token list: "
