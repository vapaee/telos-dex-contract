#!/bin/bash

echo "-- 6_deposits --"
cleos push action eosio.token transfer  '["bob",  "telosmaindex","100.0000 TLOS","deposit"]' -p bob@active
cleos push action eosio.token transfer  '["alice","telosmaindex","1000.0000 TLOS","deposit"]' -p alice@active
cleos push action eosio.token transfer  '["kate", "telosmaindex","100.0000 TLOS","deposit"]' -p kate@active
cleos push action eosio.token transfer  '["tom",  "telosmaindex","1000.0000 TLOS","deposit"]' -p tom@active

cleos push action acornaccount transfer  '["bob",  "telosmaindex","50.0000 ACORN","deposit"]' -p bob@active
cleos push action acornaccount transfer  '["alice","telosmaindex","1000.0000 ACORN","deposit"]' -p alice@active
cleos push action acornaccount transfer  '["tom",  "telosmaindex","50.0000 ACORN","deposit"]' -p tom@active
cleos push action acornaccount transfer  '["kate", "telosmaindex","50.0000 ACORN","deposit"]' -p kate@active

cleos push action futboltokens transfer  '["bob",  "telosmaindex","1000.0000 FUTBOL","deposit"]' -p bob@active
cleos push action futboltokens transfer  '["alice","telosmaindex","1000.0000 FUTBOL","deposit"]' -p alice@active
cleos push action futboltokens transfer  '["tom",  "telosmaindex","1000.0000 FUTBOL","deposit"]' -p tom@active
cleos push action futboltokens transfer  '["kate", "telosmaindex","1000.0000 FUTBOL","deposit"]' -p kate@active

cleos push action qubicletoken transfer  '["bob",  "telosmaindex","100.0000 QBE","deposit"]' -p bob@active
cleos push action qubicletoken transfer  '["alice","telosmaindex","100.0000 QBE","deposit"]' -p alice@active
cleos push action qubicletoken transfer  '["tom",  "telosmaindex","100.0000 QBE","deposit"]' -p tom@active
cleos push action qubicletoken transfer  '["kate", "telosmaindex","100.0000 QBE","deposit"]' -p kate@active

cleos push action stablecarbon transfer  '["bob",  "telosmaindex","1000.0000 TLOSD","deposit"]' -p bob@active
cleos push action stablecarbon transfer  '["alice","telosmaindex","1000.0000 TLOSD","deposit"]' -p alice@active
cleos push action stablecarbon transfer  '["tom",  "telosmaindex","1000.0000 TLOSD","deposit"]' -p tom@active
cleos push action stablecarbon transfer  '["kate", "telosmaindex","1000.0000 TLOSD","deposit"]' -p kate@active

cleos push action stablecoin.z transfer  '["bob",  "telosmaindex","1000.00 EZAR","deposit"]' -p bob@active
cleos push action stablecoin.z transfer  '["alice","telosmaindex","1000.00 EZAR","deposit"]' -p alice@active
cleos push action stablecoin.z transfer  '["tom",  "telosmaindex","1000.00 EZAR","deposit"]' -p tom@active
cleos push action stablecoin.z transfer  '["kate", "telosmaindex","1000.00 EZAR","deposit"]' -p kate@active

cleos push action ednazztokens transfer  '["bob",  "telosmaindex","100.0000 EDNA","deposit"]' -p bob@active
cleos push action ednazztokens transfer  '["alice","telosmaindex","100.0000 EDNA","deposit"]' -p alice@active
cleos push action ednazztokens transfer  '["tom",  "telosmaindex","100.0000 EDNA","deposit"]' -p tom@active
cleos push action ednazztokens transfer  '["kate", "telosmaindex","100.0000 EDNA","deposit"]' -p kate@active

cleos push action oliveaccount transfer  '["bob",  "telosmaindex","100.0000 OLIVE","deposit"]' -p bob@active
cleos push action oliveaccount transfer  '["alice","telosmaindex","100.0000 OLIVE","deposit"]' -p alice@active
cleos push action oliveaccount transfer  '["tom",  "telosmaindex","100.0000 OLIVE","deposit"]' -p tom@active
cleos push action oliveaccount transfer  '["kate", "telosmaindex","100.0000 OLIVE","deposit"]' -p kate@active

cleos push action proxibotstkn transfer  '["bob",  "telosmaindex","100.0000 ROBO","deposit"]' -p bob@active
cleos push action proxibotstkn transfer  '["alice","telosmaindex","100.0000 ROBO","deposit"]' -p alice@active
cleos push action proxibotstkn transfer  '["tom",  "telosmaindex","100.0000 ROBO","deposit"]' -p tom@active
cleos push action proxibotstkn transfer  '["kate", "telosmaindex","100.0000 ROBO","deposit"]' -p kate@active

cleos push action viitasphere1 transfer  '["bob",  "telosmaindex","100.0000 VIITA","deposit"]' -p bob@active
cleos push action viitasphere1 transfer  '["alice","telosmaindex","100.0000 VIITA","deposit"]' -p alice@active
cleos push action viitasphere1 transfer  '["tom",  "telosmaindex","100.0000 VIITA","deposit"]' -p tom@active
cleos push action viitasphere1 transfer  '["kate", "telosmaindex","100.0000 VIITA","deposit"]' -p kate@active

cleos push action teachology14 transfer  '["bob",  "telosmaindex","100.0000 TEACH","deposit"]' -p bob@active
cleos push action teachology14 transfer  '["alice","telosmaindex","100.0000 TEACH","deposit"]' -p alice@active
cleos push action teachology14 transfer  '["tom",  "telosmaindex","100.0000 TEACH","deposit"]' -p tom@active
cleos push action teachology14 transfer  '["kate", "telosmaindex","100.0000 TEACH","deposit"]' -p kate@active

cleos push action telosdacdrop transfer '["bob",  "telosmaindex","50000.0000 TLOSDAC","deposit"]' -p bob@active
cleos push action telosdacdrop transfer '["alice","telosmaindex","50000.0000 TLOSDAC","deposit"]' -p alice@active
cleos push action telosdacdrop transfer '["tom",  "telosmaindex","50000.0000 TLOSDAC","deposit"]' -p tom@active
cleos push action telosdacdrop transfer '["kate", "telosmaindex","50000.0000 TLOSDAC","deposit"]' -p kate@active

cleos push action vapaeetokens transfer '["bob",  "telosmaindex","10000.0000 CNT","deposit"]' -p bob@active
cleos push action vapaeetokens transfer '["alice","telosmaindex","10000.0000 CNT","deposit"]' -p alice@active
cleos push action vapaeetokens transfer '["kate", "telosmaindex","10000.0000 CNT","deposit"]' -p kate@active

cleos push action vapaeetokens transfer  '["bob",  "telosmaindex","1000.0000 BOX","deposit"]' -p bob@active
cleos push action vapaeetokens transfer  '["alice","telosmaindex","1000.0000 BOX","deposit"]' -p alice@active


cleos push action cryptomulita transfer '["bob",  "telosmaindex","1000.0000 MULITA","deposit"]' -p bob@active
cleos push action cryptomulita transfer '["alice","telosmaindex","1000.0000 MULITA","deposit"]' -p alice@active
cleos push action cryptomulita transfer '["tom",  "telosmaindex","1000.0000 MULITA","deposit"]' -p tom@active
cleos push action cryptomulita transfer '["kate", "telosmaindex","1000.0000 MULITA","deposit"]' -p kate@active

cleos push action cryptomulita transfer '["bob",  "telosmaindex","1000.0000 FAKE","deposit"]' -p bob@active
cleos push action cryptomulita transfer '["alice","telosmaindex","1000.0000 FAKE","deposit"]' -p alice@active
cleos push action cryptomulita transfer '["tom",  "telosmaindex","1000.0000 FAKE","deposit"]' -p tom@active
cleos push action cryptomulita transfer '["kate", "telosmaindex","1000.0000 FAKE","deposit"]' -p kate@active

echo "-- 6_deposits finiched --"