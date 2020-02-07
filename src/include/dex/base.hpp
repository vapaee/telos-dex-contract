#pragma once
#include <eosiolib/contracts/eosio/eosio.hpp>
#include <eosiolib/core/eosio/symbol.hpp>
#include <eosiolib/core/eosio/asset.hpp>
#include <eosiolib/core/eosio/print.hpp>
#include <eosiolib/contracts/eosio/transaction.hpp>
#include <eosiolib/core/eosio/check.hpp>

using namespace eosio;




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