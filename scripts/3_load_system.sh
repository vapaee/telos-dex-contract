#!/bin/bash
HOME=/var/www/telos-dex-contract
EOSIO_CDT_HOME=/usr/opt/eosio.cdt/1.6.3
# -----------------------------------
EOS_DIR=$HOME/libraries/eos
TELOSDECIDE_DIR=$HOME/libraries/telos-decide
DECIDE_CONTRACT_DIR=$TELOSDECIDE_DIR/contracts/decide
TELOS_CONTRACTS_DIR=$TELOSDECIDE_DIR/libraries/telos.contracts/contracts
EOS_CMAKEMODULES_DIR=$HOME/libraries/eos/CMakeModules
EOSIO_CDT_CMAKE_PATH=$EOSIO_CDT_HOME/lib/cmake/eosio.cdt

echo "-------- 3_load_tokens ---------"


# sudo apt-get install cmake -y

if [ ! -d $TELOSDECIDE_DIR ]; then
    cd $HOME/libraries/
    echo "Cloning telos-decide recursively"
    git clone --recursive https://github.com/telosnetwork/telos-decide.git
else
    echo "$TELOSDECIDE_DIR OK!"
fi
 
cd $TELOSDECIDE_DIR 
rm $TELOSDECIDE_DIR/build -fr &>>/dev/null
rm $TELOSDECIDE_DIR/CMakeFiles -fr &>>/dev/null
rm $TELOSDECIDE_DIR/CMakeCache.txt &>>/dev/null

# this anulates test building
echo "cmake_minimum_required( VERSION 3.5 )" > $TELOSDECIDE_DIR/tests/CMakeLists.txt

echo "-------- cmake ---------"
cmake -DCMAKE_MODULE_PATH=$EOSIO_CDT_CMAKE_PATH .
echo "-------- make ---------"
make


$HOME/libraries/telos-decide/contracts/decide/decide.abi
$HOME/libraries/telos-decide/contracts/watcher/watcher.abi
$HOME/libraries/telos-decide/libraries/telos.contracts/tests/test_contracts/eosio.msig.old/eosio.msig.abi
$HOME/libraries/telos-decide/libraries/telos.contracts/tests/test_contracts/eosio.system.old/eosio.system.abi
$HOME/libraries/telos-decide/tests/contracts/eosio.system/eosio.system.abi
$HOME/libraries/telos-decide/tests/contracts/eosio.token/eosio.token.abi

###  cleos set contract decide /var/www/telos-dex-contract/libraries/telos-decide/contracts/decide/ -p decide@active
###  cleos set contract eosio.trail /var/www/telos-dex-contract/libraries/telos-decide/contracts/decide/ -p eosio.trail@active

echo "-------- 3_load_tokens finished ---------"
