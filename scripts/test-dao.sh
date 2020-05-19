#!/bin/bash
# rm /var/www/blockchain/eosio/data -fr




./1_create_accounts.sh

./2_deploy_contract.sh

./3_load_tokens.sh

./4_load_telos_decide.sh

./5_register_interfaces.sh

./6_deposits.sh

./7_orders.sh


echo "-- bob sells FAKE --"
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.10000000 TLOS",0]' -p bob
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.11000000 TLOS",0]' -p bob
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.12000000 TLOS",0]' -p bob
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.13000000 TLOS",0]' -p bob
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.14000000 TLOS",0]' -p bob

echo "create ballots over tokens -----------------------------"
cleos push action telosmaindex balloton '["bantoken", ["ROBO","proxibotstkn"], "bantoken ROBO proxibotstkn", "alice"]' -p alice
cleos push action telosmaindex balloton '["bantoken", ["FAKE","cryptomulita"], "bantoken FAKE cryptomulita", "alice"]' -p alice
cleos push action telosmaindex balloton '["savetoken", ["CNT","vapaeetokens"], "savetoken CNT vapaeetokens", "alice"]' -p alice
cleos push action telosmaindex balloton '["setcurrency", ["MULITA","cryptomulita"], "setcurrency MULITA cryptomulita", "alice"]' -p alice

echo "create ballots over fees -------------------------------"
cleos push action telosmaindex balloton '["makerfee", ["0.01010101 FEE"], "makerfee - sets a fee for the market creators", "alice"]' -p alice
cleos push action telosmaindex balloton '["takerfee", ["0.02020202 FEE"], "takerfee - sets a fee for the market orders takers (should be higher)", "alice"]' -p alice

echo "create ballots over history prune ----------------------"
cleos push action telosmaindex balloton '["historyprune", ["111"], "historyprune - sets days of expiration for history", "alice"]' -p alice
cleos push action telosmaindex balloton '["ballotsprune", ["22"], "ballotsprune - sets max count for ballots", "alice"]' -p alice
cleos push action telosmaindex balloton '["eventsprune", ["7"], "eventsprune - sets days of expiration for events", "alice"]' -p alice

echo "create ballots over token registration cost ------------"
cleos push action telosmaindex balloton '["regcost", ["333.0000 TLOS"], "regcost - sets the cost for registerin a new token in the DEX list", "alice"]' -p alice


cleos get table telosmaindex telosmaindex ballots
sleep 2

echo "all FAIL (repeated) ----------------------------"
cleos push action telosmaindex balloton '["bantoken", ["ROBO","proxibotstkn"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["bantoken", ["FAKE","cryptomulita"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["savetoken", ["CNT","vapaeetokens"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["setcurrency", ["MULITA","cryptomulita"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["makerfee", ["0.01010101 FEE"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["takerfee", ["0.02020202 FEE"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["historyprune", ["111"], "aaaaaa", "alice"]' -p alice
cleos push action telosmaindex balloton '["regcost", ["333.0000 TLOS"], "aaaaaa", "alice"]' -p alice
sleep 1

echo "vottng ------------------------------------------------"
echo " - bantoken ROBO - "
cleos push action telos.decide castvote '["bob", "", ["no"]]' -p bob
cleos push action telos.decide castvote '["alice", "", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "", ["no"]]' -p tom
cleos push action telos.decide castvote '["kate", "", ["no"]]' -p kate

echo " - bantoken FAKE - "
cleos push action telos.decide castvote '["bob", "............1", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............1", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............1", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............1", ["yes"]]' -p kate

echo " - savetoken CNT - "
cleos push action telos.decide castvote '["bob", "............2", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............2", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............2", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............2", ["yes"]]' -p kate

echo " - setcurrency MULITA - "
cleos push action telos.decide castvote '["bob", "............3", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............3", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............3", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............3", ["yes"]]' -p kate

echo " - makerfee - "
cleos push action telos.decide castvote '["bob", "............4", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............4", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............4", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............4", ["yes"]]' -p kate

echo " - takerfee - "
cleos push action telos.decide castvote '["bob", "............5", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............5", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............5", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............5", ["yes"]]' -p kate

echo " - historyprune - "
cleos push action telos.decide castvote '["bob", "............a", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............a", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............a", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............a", ["yes"]]' -p kate

echo " - ballotsprune - "
cleos push action telos.decide castvote '["bob", "............b", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............b", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............b", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............b", ["yes"]]' -p kate

echo " - eventsprune - "
cleos push action telos.decide castvote '["bob", "............c", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............c", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............c", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............c", ["yes"]]' -p kate

echo " - regcost - "
cleos push action telos.decide castvote '["bob", "............d", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............d", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............d", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............d", ["yes"]]' -p kate


echo "waiting 5 sec for voting timeout..."
sleep 6

cleos get table telosmaindex telosmaindex state

echo "closing voting on telos.decide to generate broadcast"
cleos push action telos.decide closevoting '["", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............1", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............2", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............3", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............4", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............5", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............a", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............b", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............c", true]' -p telosmaindex@active


#echo "FAIL (saved token CNT)----------------------------"
#sleep 3
#cleos push action telosmaindex balloton '["bantoken", ["CNT","vapaeetokens"], "alice"]' -p alice


cleos get table telosmaindex telosmaindex state
echo "--------- FIN ----------"
exit 0

-- TODO --



https://local.bloks.io/account/telos.decide?nodeUrl=localhost%3A8888&coreSymbol=TLOS&systemDomain=eosio&loadContract=true&tab=Tables&account=telos.decide&scope=telos.decide&limit=100&table=ballots
https://local.bloks.io/account/telosmaindex?nodeUrl=localhost%3A8888&coreSymbol=TLOS&systemDomain=eosio&loadContract=true&tab=Tables&account=telosmaindex&scope=telosmaindex&limit=100

