#pragma once
#include <dex/base.hpp>

using namespace eosio;
using namespace std;

namespace eosio {

CONTRACT telosmaindex : public eosio::contract {
    
    private:

#include <dex/tables.all.hpp>

    public:
        ACTION test () {

        };

};

}; // eosio namespace