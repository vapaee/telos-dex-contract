#pragma once

#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/symbol.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>
#include <eosio/print.hpp>

#include <ctype.h>
#include <stdlib.h>

namespace eosio {
    namespace dex {
        name contract               = name("telosmaindex");
        symbol_code SYS_TKN_CODE    = symbol_code("TLOS");
        name SYS_TKN_CONTRACT       = name("eosio.token");
        uint8_t internal_precision  = 8;
    }
}




// hepper macros 

/*
#define MAINTENANCE(...) check(has_auth(_self), ">>>>>> This contract is in MAINTENANCE. Please, try later again. <<<<<<");
/*/
#define MAINTENANCE(...)
//*/

//*
#define PRINT(...) print(__VA_ARGS__)
#define AUX_DEBUG_ACTIONS(...) __VA_ARGS__
/*/
#define PRINT(...)
#define AUX_DEBUG_ACTIONS(...)
//*/