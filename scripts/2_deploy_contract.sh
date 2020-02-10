#!/bin/bash

HOME=/var/www/telos-dex-contract
#-------------------------------
INCLUDE_PATH=$HOME/src/include
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

echo "-------- telosmaindex ---------"
cd $DEX_CONTRACT_DIR
if [[ telosmaindex.cpp -nt telosmaindex.wasm ||
      telosmaindex.hpp -nt telosmaindex.wasm || 
      $force == true ]]; then
    eosio-cpp -o telosmaindex.wasm telosmaindex.cpp --abigen -I "$INCLUDE_PATH"
fi
echo "cleos $NET set contract telosmaindex $PWD -p telosmaindex@active"
cleos $NET set contract telosmaindex $PWD -p telosmaindex@active


EVENTHANDLER_DIR=$HOME/src/contracts/eventhandler
if [ "$NET" == "" ]; then
    echo "-------- eventhandler ---------"
    cd $EVENTHANDLER_DIR
    pwd
    if [[ eventhandler.hpp -nt eventhandler.wasm || 
        $force == true ]]; then
        eosio-cpp -o eventhandler.wasm eventhandler.cpp --abigen -I "$INCLUDE_PATH"
    fi
    echo "cleos $NET set contract eventhandler $PWD -p eventhandler@active"
    cleos $NET set contract eventhandler $PWD -p eventhandler@active
fi