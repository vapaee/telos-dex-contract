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
sleep 1

# sudo apt-get install cmake -y

if [ ! -d $TELOSDECIDE_DIR ]; then
    cd $HOME/libraries/
    echo "Cloning telos-decide recursively"
    git clone --recursive https://github.com/telosnetwork/telos-decide.git
else
    echo "$TELOSDECIDE_DIR OK!"
fi


# if [ ! -d $EOS_DIR ]; then
#     cd $HOME/libraries/
#     echo "Cloning eos. This can take some minutes..."
#     git clone https://github.com/EOSIO/eos.git
# else
#     echo "$EOS_DIR OK!"
# fi
# 


# cd $TELOSDECIDE_DIR
# if [ ! -d $TELOSDECIDE_DIR/cmake ]; then
#     mkdir -p $TELOSDECIDE_DIR/cmake
#     cd cmake
#     wget https://raw.githubusercontent.com/EOSIO/eos/master/CMakeModules/eosio-config.cmake.in
#     mv eosio-config.cmake.in eosio-config.cmake
# else
#     echo "$TELOSDECIDE_DIR/cmake/eosio-config.cmake OK!"
# fi
 
cd $TELOSDECIDE_DIR 
rm $TELOSDECIDE_DIR/build -fr &>>/dev/null
rm $TELOSDECIDE_DIR/CMakeFiles -fr &>>/dev/null
rm $TELOSDECIDE_DIR/CMakeCache.txt &>>/dev/null

#message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
#message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# this anulates test building
echo "cmake_minimum_required( VERSION 3.5 )" > $TELOSDECIDE_DIR/tests/CMakeLists.txt

echo "-------- cmake ---------"
cmake -DCMAKE_MODULE_PATH=$EOSIO_CDT_CMAKE_PATH .
#cmake .
echo "-------- make ---------"
make

#cmake -DCMAKE_MODULE_PATH=./cmake<additional-path> .
#make

# if [ ! -d $HOME/src/contracts/telos.contracts ]; then
#     cd $HOME/src/contracts/
#     echo "Cloning telos.contracts"
#     git clone https://github.com/telosnetwork/telos.contracts.git
# else
#     echo "$HOME/src/contracts/telos.contracts OK!"
# fi



#echo "-------- BUILD ---------"
#cd $TELOSDECIDE_DIR
#./build.sh -c decide
#cd $TELOS_CONTRACTS_DIR/..
#./build.sh -e /usr/opt/eosio/1.8.12 -c /usr/opt/eosio.cdt




# cp -r $DECIDE_CONTRACT_DIR $TELOS_CONTRACTS_DIR/
# 
# echo -e "\nadd_subdirectory(decide)\n" >> $TELOS_CONTRACTS_DIR/CMakeLists.txt
# echo "----- contracts ------"
# ls -asl $TELOS_CONTRACTS_DIR/
# sleep 1.5
# echo "----- CMake List ------"
# cat $TELOS_CONTRACTS_DIR/CMakeLists.txt
# sleep 1.5





#echo "-------- telos.decide (Voting system) ---------"
#cd $DECIDE_CONTRACT_DIR
# ./build.sh
#eosio-cpp --abigen -o telos.decide.wasm src/ballot.cpp src/committee.cpp src/decide.cpp src/treasury.cpp src/voter.cpp src/worker.cpp -I include -I $HOME/src/contracts/telos.contracts/contracts/eosio.system/include
# if [[ src/decide.cpp -nt telos.decide.wasm ]]; then
#     eosio-cpp -o telos.decide.wasm src/ballot.cpp src/committee.cpp src/decide.cpp src/treasury.cpp src/voter.cpp src/worker.cpp --abigen -I include -I $HOME/src/contracts/telos.contracts/contracts/eosio.system/include    
# fi
#cleos set contract telos.decide $PWD -p telos.decide@active

#echo "-------- eosio.token (standar token) ---------"
#cd $HOME/src/contracts/telos.contracts/contracts/eosio.token
#if [[ src/eosio.token.cpp -nt eosio.token.wasm ]]; then
#    eosio-cpp -o eosio.token.wasm src/eosio.token.cpp --abigen -I include
#fi
#cleos set contract eosio.token $PWD -p eosio.token@active