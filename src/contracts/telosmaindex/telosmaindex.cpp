#include "telosmaindex.hpp"

#define DEX_ACTIONS (order)(cancel)
#define TOKEN_ACTIONS (addtoken)(updatetoken)(tokenadmin)(setcurrency)(settokendata)(edittkevent)(addtnkgroup)(uptnkgroup)
#define UI_ACTIONS (addui)(updateui)
#define DAO_ACTIONS (balloton)
#define DEPOSITS_ACTIONS (withdraw)(swapdeposit)(deps2earn)
#define GLOBAL_ACTIONS (init)(maintenance)
#define HANDLERS (htransfer)(hbroadcast)
#define DEBUG_ACTIONS (hotfix)(testdao)(timeoffset)


EOSIO_DISPATCH_VAPAEE (
    eosio::telosmaindex,
    DEX_ACTIONS TOKEN_ACTIONS UI_ACTIONS DAO_ACTIONS DEPOSITS_ACTIONS GLOBAL_ACTIONS AUX_DEBUG_CODE(DEBUG_ACTIONS),
    HANDLERS
)
