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

echo "-------- 4_load_telos_decide ---------"


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


echo "-------- set contract telos.decide ---------"

cleos set contract telos.decide $HOME/libraries/telos-decide/contracts/decide/ -p telos.decide@active

# /var/www/telos-dex-contract/libraries/telos-decide/contracts/decide/decide.abi
# /var/www/telos-dex-contract/libraries/telos-decide/contracts/watcher/watcher.abi
# /var/www/telos-dex-contract/libraries/telos-decide/libraries/telos.contracts/tests/test_contracts/eosio.msig.old/eosio.msig.abi
# /var/www/telos-dex-contract/libraries/telos-decide/libraries/telos.contracts/tests/test_contracts/eosio.system.old/eosio.system.abi
# /var/www/telos-dex-contract/libraries/telos-decide/tests/contracts/eosio.system/eosio.system.abi
# /var/www/telos-dex-contract/libraries/telos-decide/tests/contracts/eosio.token/eosio.token.abi


echo "-------- set telos.decide config ---------"

cleos push action telos.decide init '["v2.0.2"]' -p telos.decide
cleos push action telos.decide init '["v2.0.2+"]' -p telos.decide
cleos get table telos.decide telos.decide config
sleep 1

echo "-------- set telos.decide newtreasury VOTE ---------"

cleos push action eosio.token transfer '["eosio", "telos.decide", "1000.0000 TLOS", "deposit"]' -p eosio@active
cleos push action telos.decide newtreasury '["eosio","10000000000.0000 VOTE","public"]' -p eosio
cleos get table telos.decide telos.decide treasuries

echo "pause..."
sleep 1

echo "-------- registering voters ---------"

cleos push action telos.decide regvoter '["telosmaindex","4,VOTE","telosmaindex"]' -p telosmaindex
cleos push action telos.decide regvoter '["alice", "4,VOTE", "alice"]' -p alice
cleos push action telos.decide regvoter '["bob", "4,VOTE", "bob"]' -p bob
cleos push action telos.decide regvoter '["kate", "4,VOTE", "kate"]' -p kate
cleos push action telos.decide regvoter '["tom", "4,VOTE", "tom"]' -p tom
cleos get table telos.decide telosmaindex voters
sleep 1

cleos push action telos.decide mint '["bob", "1000.0000 VOTE", ""]' -p eosio
cleos push action telos.decide mint '["alice", "1001.0000 VOTE", ""]' -p eosio
cleos push action telos.decide mint '["tom", "2000.0000 VOTE", ""]' -p eosio
cleos push action telos.decide mint '["kate", "1000.0000 VOTE", ""]' -p eosio

# cleos get currency balance eosio.token bob TLOS
# cleos get currency balance eosio.token alice TLOS
# cleos get currency balance eosio.token tom TLOS
# cleos get currency balance eosio.token kate TLOS

echo "pause..."
sleep 1



echo "-------- 4_load_telos_decide finished ---------"
