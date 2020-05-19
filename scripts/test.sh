#!/bin/bash
# rm /var/www/blockchain/eosio/data -fr




./1_create_accounts.sh

./2_deploy_contract.sh

#!/bin/bash
HOME=/var/www/telos-dex-contract

cd $HOME/libraries/telos-decide/tests/contracts/eosio.token/

echo "-------- eosio.token (TLOS) ---------"
cleos set contract eosio.token $PWD -p eosio.token@active
cleos push action eosio.token create '[ "telosmaindex", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token create '[ "telosmaindex", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token issue '["telosmaindex", "10000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
sleep 1
# cleos push action eosio.token transfer '["telosmaindex", "alice", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "alice", "1001.0000 TLOS", "memo 1001 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "bob", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "tom", "2000.0000 TLOS", "memo 2000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "kate", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "eosio", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active



echo "----- INITIALIZATION ----"
cleos push action telosmaindex init '[]' -p telosmaindex@active
sleep 1
echo "- table: state -"
cleos get table telosmaindex telosmaindex state
echo "- table: tokengroups -"
cleos get table telosmaindex telosmaindex tokengroups
echo "- table: tokens -"
cleos get table telosmaindex telosmaindex tokens
sleep 1

