#pragma once

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


// DAO Module ------------------------

// action_start_ballot_on
#define ERROR_ASBO_1 "ERR-ASBO-01: unknown property: "
#define ERROR_ASBO_2 "ERR-ASBO-02: telos.decide fee symbol_code and system symbol_code does not match?: "


// aux_check_symbol_code_from_string
#define ERROR_ACSCFS_1 "ERR-ACSCFS-01: This token is not registered: "

// aux_check_double_from_string
#define ERROR_ACDFS_1 "ERR-ACDFS-01: Fee can not be negative: "
#define ERROR_ACDFS_2 "ERR-ACDFS-02: Fee can not higher than 1: "

// aux_check_integer_from_string
#define ERROR_ACIFS_1 "ERR-ACIFS-02: Cant prune future records: "

// aux_get_telos_decide_config
#define ERROR_AGTDC_1 "ERR-AGTDC-02: Cant prune future records: "