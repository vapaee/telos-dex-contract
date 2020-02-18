#pragma once
#include <eosiolib/contracts/eosio/eosio.hpp>
#include <eosiolib/core/eosio/symbol.hpp>
#include <eosiolib/core/eosio/asset.hpp>
#include <eosiolib/core/eosio/print.hpp>
#include <eosiolib/contracts/eosio/transaction.hpp>
#include <eosiolib/core/eosio/check.hpp>

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