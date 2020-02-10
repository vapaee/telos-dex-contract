#include "telosmaindex.hpp"

#define DEX_ACTIONS (addui)(updateui)(addtoken)(updatetoken)(tokenadmin)(setcurrency)(settokendata)(edittkevent)(order)(withdraw)(swapdeposit)(cancel)(deps2earn)
#define EXCHANGE_HANDLERS (htransfer)
#define DEBUG_ACTIONS (hotfix)


EOSIO_DISPATCH_VAPAEE (
    eosio::telosmaindex,
    DEX_ACTIONS AUX_DEBUG_ACTIONS(DEBUG_ACTIONS),
    EXCHANGE_HANDLERS
)
