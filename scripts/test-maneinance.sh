#!/bin/bash
# rm /var/www/blockchain/eosio/data -fr




./1_create_accounts.sh

./2_deploy_contract.sh

./3_load_tokens.sh

./4_load_telos_decide.sh

cleos push action telosmaindex timeoffset '[186500]' -p telosmaindex

./5_register_interfaces.sh

./6_deposits.sh

./7_orders.sh




# 86400
echo "-- bob sells CNT --"
cleos push action telosmaindex timeoffset '[186360]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 CNT", "0.10000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186350]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 CNT", "0.11000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186340]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 CNT", "0.12000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186330]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 CNT", "0.13000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186320]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 CNT", "0.14000000 TLOS",0]' -p bob


echo "-- bob sells FAKE --"
cleos push action telosmaindex timeoffset '[186460]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.10000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186450]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.11000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186440]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.12000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186430]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.13000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[186420]' -p telosmaindex
cleos push action telosmaindex order '["bob", "sell", "5.00000000 FAKE", "0.14000000 TLOS",0]' -p bob
cleos push action telosmaindex timeoffset '[0]' -p telosmaindex

echo "create ballots over history prune ----------------------"
cleos push action telosmaindex balloton '["historyprune", ["1"], "historyprune - sets days of expiration", "alice"]' -p alice
cleos push action telosmaindex balloton '["ballotsprune", ["0"], "ballotsprune - sets max count for ballots", "alice"]' -p alice
cleos push action telosmaindex balloton '["eventsprune", ["1"], "eventsprune - sets days of expiration for events", "alice"]' -p alice

echo "create ballots over tokens -----------------------------"
cleos push action telosmaindex balloton '["bantoken", ["FAKE","cryptomulita"], "bantoken FAKE cryptomulita", "alice"]' -p alice
cleos push action telosmaindex balloton '["savetoken", ["CNT","vapaeetokens"], "savetoken CNT vapaeetokens", "alice"]' -p alice
cleos push action telosmaindex balloton '["setcurrency", ["MULITA","cryptomulita"], "setcurrency MULITA cryptomulita", "alice"]' -p alice

echo "vottng ------------------------------------------------"
cleos push action telos.decide castvote '["bob", "", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "", ["yes"]]' -p alice
cleos push action telos.decide castvote '["tom", "", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "", ["yes"]]' -p kate
cleos push action telos.decide castvote '["bob", "............1", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............1", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............1", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............1", ["yes"]]' -p kate
cleos push action telos.decide castvote '["bob", "............2", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............2", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............2", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............2", ["yes"]]' -p kate
cleos push action telos.decide castvote '["bob", "............3", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............3", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............3", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............3", ["yes"]]' -p kate
cleos push action telos.decide castvote '["bob", "............4", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............4", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............4", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............4", ["yes"]]' -p kate
cleos push action telos.decide castvote '["bob", "............5", ["yes"]]' -p bob
cleos push action telos.decide castvote '["alice", "............5", ["no"]]' -p alice
cleos push action telos.decide castvote '["tom", "............5", ["yes"]]' -p tom
cleos push action telos.decide castvote '["kate", "............5", ["yes"]]' -p kate

echo "closing voting on telos.decide to generate broadcast --"
sleep 6
cleos push action telos.decide closevoting '["", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............1", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............2", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............3", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............4", true]' -p telosmaindex@active
cleos push action telos.decide closevoting '["............5", true]' -p telosmaindex@active

cleos get table telosmaindex telosmaindex state
sleep 1





cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1
cleos push action telosmaindex maintenance '[]' -p alice
cleos get table telosmaindex telosmaindex historyall
sleep 1


cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
cleos push action telosmaindex maintenance '[]' -p alice && sleep 0.5
