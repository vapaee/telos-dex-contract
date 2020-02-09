#include "telosmaindex.hpp"

// helpper macros -----------------
#define HANDLER void 
#define EOSIO_DISPATCH_VAPAEE( TYPE, MEMBERS, HANDLERS ) \
extern "C" { \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
      if( code == receiver ) { \
         switch( action ) { \
            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
      } \
      name handler = eosio::name(string("h") + eosio::name(action).to_string()); \
      switch( handler.value ) { \
         EOSIO_DISPATCH_HELPER( TYPE, HANDLERS ) \
      } \
   } \
} \

// ---------------------------------

#define DEX_ACTIONS (test)


// #define EXCHANGE_HANDLERS (htransfer)
#define EXCHANGE_HANDLERS

// #define DEBUG_ACTIONS (hotfix)
#define DEBUG_ACTIONS

EOSIO_DISPATCH_VAPAEE (
    eosio::telosmaindex,
    DEX_ACTIONS AUX_DEBUG_ACTIONS(DEBUG_ACTIONS),
    EXCHANGE_HANDLERS
)