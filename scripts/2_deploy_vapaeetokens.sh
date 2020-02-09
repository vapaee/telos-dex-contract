#!/bin/bash

HOME=/var/www/telos-dex-contract
force=false
NET=

# checking 'force' param
if [ "$1" == "force" ]; then
   force=true
fi

if [ "$2" == "force" ]; then
   force=true
fi

if [ "$1" == "prod" ]; then
   NET='--url https://telos.eos.barcelona'
fi

if [ "$1" == "test" ]; then
   NET='--url https://testnet.telos.caleos.io'
fi

DEX_CONTRACT_DIR=$HOME/src/contracts/telosmaindex

echo "-------- vapaeetokens ---------"
cd $DEX_CONTRACT_DIR
if [[ vapaeetokens.core.hpp -nt vapaeetokens.wasm || 
      vapaeetokens.stake.hpp -nt vapaeetokens.wasm ||
      vapaeetokens.exchange.hpp -nt vapaeetokens.wasm ||
      vapaeetokens.airdrop.hpp -nt vapaeetokens.wasm ||
      vapaeetokens.dispatcher.hpp -nt vapaeetokens.wasm || 
      vapaeetokens.cpp -nt vapaeetokens.wasm ||
      vapaeetokens.hpp -nt vapaeetokens.wasm || 
      $force == true ]]; then
    eosio-cpp -o vapaeetokens.wasm vapaeetokens.cpp --abigen -I ../includes
fi
echo "cleos $NET set contract vapaeetokens $PWD -p vapaeetokens@active"
cleos $NET set contract vapaeetokens $PWD -p vapaeetokens@active


EVENTHANDLER_DIR=$HOME/src/contracts/eventhandler
if [ "$NET" == "" ]; then
    echo "-------- eventhandler ---------"
    cd $EVENTHANDLER_DIR
    pwd
    if [[ eventhandler.hpp -nt eventhandler.wasm || 
        $force == true ]]; then
        eosio-cpp -o eventhandler.wasm eventhandler.cpp --abigen -I ../includes
    fi
    echo "cleos $NET set contract eventhandler $PWD -p eventhandler@active"
    cleos $NET set contract eventhandler $PWD -p eventhandler@active
fi