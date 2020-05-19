#!/bin/bash
HOME=/var/www/telos-dex-contract

echo "-------- 3_load_tokens ---------"

# cd $HOME/src/contracts/telos.contracts/contracts/eosio.token
cd $HOME/libraries/telos-decide/tests/contracts/eosio.token/

echo "-------- eosio.token (TLOS) ---------"
cleos set contract eosio.token $PWD -p eosio.token@active
cleos push action eosio.token create '[ "token.issuer", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token create '[ "token.issuer", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token issue '["token.issuer", "1000000.0000 TLOS", "memo 1000000 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "alice", "1000.0000 TLOS", "memo 1000 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "alice", "1001.0000 TLOS", "memo 1001 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "bob", "10000.0000 TLOS", "memo 10000 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "tom", "2000.0000 TLOS", "memo 2000 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "kate", "1000.0000 TLOS", "memo 1000 TLOS"]' -p token.issuer@active
cleos push action eosio.token transfer '["token.issuer", "eosio", "1000.0000 TLOS", "memo 1000 TLOS"]' -p token.issuer@active

echo "-------- acornaccount (ACORN) ---------"
cleos set contract acornaccount $PWD -p acornaccount@active
cleos push action acornaccount create '[ "token.issuer", "461168601842738.0000 ACORN"]' -p acornaccount@active
cleos push action acornaccount issue '["token.issuer", "10000.0000 ACORN", "memo ACORN"]' -p token.issuer@active
cleos push action acornaccount transfer '["token.issuer", "alice", "1000.0000 ACORN", "memo ACORN"]' -p token.issuer@active
cleos push action acornaccount transfer '["token.issuer", "bob", "1000.0000 ACORN", "memo ACORN"]' -p token.issuer@active
cleos push action acornaccount transfer '["token.issuer", "tom", "1000.0000 ACORN", "memo ACORN"]' -p token.issuer@active
cleos push action acornaccount transfer '["token.issuer", "kate", "1000.0000 ACORN", "memo ACORN"]' -p token.issuer@active

echo "-------- oliveaccount (OLIVE) ---------"
cleos set contract oliveaccount $PWD -p oliveaccount@active
cleos push action oliveaccount create '[ "token.issuer", "461168601842738.0000 OLIVE"]' -p oliveaccount@active
cleos push action oliveaccount issue '["token.issuer", "1000.0000 OLIVE", "memo OLIVE"]' -p token.issuer@active
cleos push action oliveaccount transfer '["token.issuer", "alice", "100.0000 OLIVE", "memo OLIVE"]' -p token.issuer@active
cleos push action oliveaccount transfer '["token.issuer", "bob", "100.0000 OLIVE", "memo OLIVE"]' -p token.issuer@active
cleos push action oliveaccount transfer '["token.issuer", "tom", "100.0000 OLIVE", "memo OLIVE"]' -p token.issuer@active
cleos push action oliveaccount transfer '["token.issuer", "kate", "100.0000 OLIVE", "memo OLIVE"]' -p token.issuer@active

echo "-------- revelation21 (HEART) ---------"
cleos set contract revelation21 $PWD -p revelation21@active
cleos push action revelation21 create '[ "token.issuer", "2100000000.0000 HEART"]' -p revelation21@active
cleos push action revelation21 issue '["token.issuer", "1000.0000 HEART", "memo HEART"]' -p token.issuer@active
cleos push action revelation21 transfer '["token.issuer", "alice", "100.0000 HEART", "memo HEART"]' -p token.issuer@active
cleos push action revelation21 transfer '["token.issuer", "bob", "100.0000 HEART", "memo HEART"]' -p token.issuer@active
cleos push action revelation21 transfer '["token.issuer", "tom", "100.0000 HEART", "memo HEART"]' -p token.issuer@active
cleos push action revelation21 transfer '["token.issuer", "kate", "100.0000 HEART", "memo HEART"]' -p token.issuer@active

echo "-------- futboltokens (FUTBOL) ---------"
cleos set contract futboltokens $PWD -p futboltokens@active
cleos push action futboltokens create '[ "token.issuer", "2100000000.0000 FUTBOL"]' -p futboltokens@active
cleos push action futboltokens issue '["token.issuer", "10000.0000 FUTBOL", "memo FUTBOL"]' -p token.issuer@active
cleos push action futboltokens transfer '["token.issuer", "alice", "1000.0000 FUTBOL", "memo FUTBOL"]' -p token.issuer@active
cleos push action futboltokens transfer '["token.issuer", "bob", "1000.0000 FUTBOL", "memo FUTBOL"]' -p token.issuer@active
cleos push action futboltokens transfer '["token.issuer", "tom", "1000.0000 FUTBOL", "memo FUTBOL"]' -p token.issuer@active
cleos push action futboltokens transfer '["token.issuer", "kate", "1000.0000 FUTBOL", "memo FUTBOL"]' -p token.issuer@active

echo "-------- teloslegends (LEGEND) ---------"
cleos set contract teloslegends $PWD -p teloslegends@active
cleos push action teloslegends create '[ "token.issuer", "12 LEGEND"]' -p teloslegends@active
cleos push action teloslegends issue '["token.issuer", "10 LEGEND", "memo LEGEND"]' -p token.issuer@active
cleos push action teloslegends transfer '["token.issuer", "alice", "1 LEGEND", "memo LEGEND"]' -p token.issuer@active
cleos push action teloslegends transfer '["token.issuer", "bob", "1 LEGEND", "memo LEGEND"]' -p token.issuer@active
cleos push action teloslegends transfer '["token.issuer", "tom", "1 LEGEND", "memo LEGEND"]' -p token.issuer@active
cleos push action teloslegends transfer '["token.issuer", "kate", "1 LEGEND", "memo LEGEND"]' -p token.issuer@active

echo "-------- viitasphere1 (VIITA) ---------"
cleos set contract viitasphere1 $PWD -p viitasphere1@active
cleos push action viitasphere1 create '[ "token.issuer", "10000000000.0000 VIITA"]' -p viitasphere1@active
cleos push action viitasphere1 issue '["token.issuer", "1000.0000 VIITA", "memo VIITA"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "alice", "100.0000 VIITA", "memo VIITA"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "bob", "100.0000 VIITA", "memo VIITA"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "tom", "100.0000 VIITA", "memo VIITA"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "kate", "100.0000 VIITA", "memo VIITA"]' -p token.issuer@active

echo "-------- viitasphere1 (VIICT) ---------"
cleos push action viitasphere1 create '[ "token.issuer", "500000 VIICT"]' -p viitasphere1@active
cleos push action viitasphere1 issue '["token.issuer", "1000 VIICT", "memo VIICT"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "alice", "100 VIICT", "memo VIICT"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "bob", "100 VIICT", "memo VIICT"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "tom", "100 VIICT", "memo VIICT"]' -p token.issuer@active
cleos push action viitasphere1 transfer '["token.issuer", "kate", "100 VIICT", "memo VIICT"]' -p token.issuer@active

echo "-------- qubicletoken (QBE) ---------"
cleos set contract qubicletoken $PWD -p qubicletoken@active
cleos push action qubicletoken create '[ "token.issuer", "100000000.0000 QBE"]' -p qubicletoken@active
cleos push action qubicletoken issue '["token.issuer", "1000.0000 QBE", "memo QBE"]' -p token.issuer@active
cleos push action qubicletoken transfer '["token.issuer", "alice", "100.0000 QBE", "memo QBE"]' -p token.issuer@active
cleos push action qubicletoken transfer '["token.issuer", "bob", "100.0000 QBE", "memo QBE"]' -p token.issuer@active
cleos push action qubicletoken transfer '["token.issuer", "tom", "100.0000 QBE", "memo QBE"]' -p token.issuer@active
cleos push action qubicletoken transfer '["token.issuer", "kate", "100.0000 QBE", "memo QBE"]' -p token.issuer@active

echo "-------- ednazztokens (EDNA) ---------"
cleos set contract ednazztokens $PWD -p ednazztokens@active
cleos push action ednazztokens create '[ "token.issuer", "1300000000.0000 EDNA"]' -p ednazztokens@active
cleos push action ednazztokens issue '["token.issuer", "1000.0000 EDNA", "memo EDNA"]' -p token.issuer@active
cleos push action ednazztokens transfer '["token.issuer", "alice", "100.0000 EDNA", "memo EDNA"]' -p token.issuer@active
cleos push action ednazztokens transfer '["token.issuer", "bob", "100.0000 EDNA", "memo EDNA"]' -p token.issuer@active
cleos push action ednazztokens transfer '["token.issuer", "tom", "100.0000 EDNA", "memo EDNA"]' -p token.issuer@active
cleos push action ednazztokens transfer '["token.issuer", "kate", "100.0000 EDNA", "memo EDNA"]' -p token.issuer@active

echo "-------- teachology14 (TEACH) ---------"
cleos set contract teachology14 $PWD -p teachology14@active
cleos push action teachology14 create '[ "token.issuer", "10000000000.0000 TEACH"]' -p teachology14@active
cleos push action teachology14 issue '["token.issuer", "1000.0000 TEACH", "memo TEACH"]' -p token.issuer@active
cleos push action teachology14 transfer '["token.issuer", "alice", "100.0000 TEACH", "memo TEACH"]' -p token.issuer@active
cleos push action teachology14 transfer '["token.issuer", "bob", "100.0000 TEACH", "memo TEACH"]' -p token.issuer@active
cleos push action teachology14 transfer '["token.issuer", "tom", "100.0000 TEACH", "memo TEACH"]' -p token.issuer@active
cleos push action teachology14 transfer '["token.issuer", "kate", "100.0000 TEACH", "memo TEACH"]' -p token.issuer@active

echo "-------- proxibotstkn (ROBO) ---------"
cleos set contract proxibotstkn $PWD -p proxibotstkn@active
cleos push action proxibotstkn create '[ "token.issuer", "1000000000.0000 ROBO"]' -p proxibotstkn@active
cleos push action proxibotstkn issue '["token.issuer", "1000.0000 ROBO", "memo ROBO"]' -p token.issuer@active
cleos push action proxibotstkn transfer '["token.issuer", "alice", "100.0000 ROBO", "memo ROBO"]' -p token.issuer@active
cleos push action proxibotstkn transfer '["token.issuer", "bob", "100.0000 ROBO", "memo ROBO"]' -p token.issuer@active
cleos push action proxibotstkn transfer '["token.issuer", "tom", "100.0000 ROBO", "memo ROBO"]' -p token.issuer@active
cleos push action proxibotstkn transfer '["token.issuer", "kate", "100.0000 ROBO", "memo ROBO"]' -p token.issuer@active

echo "-------- stablecarbon (TLOSD) ---------"
cleos set contract stablecarbon $PWD -p stablecarbon@active
cleos push action stablecarbon create '[ "token.issuer", "1000000000.0000 TLOSD"]' -p stablecarbon@active
cleos push action stablecarbon issue '["token.issuer", "10000.0000 TLOSD", "memo TLOSD"]' -p token.issuer@active
cleos push action stablecarbon transfer '["token.issuer", "alice", "1000.0000 TLOSD", "memo TLOSD"]' -p token.issuer@active
cleos push action stablecarbon transfer '["token.issuer", "bob", "1000.0000 TLOSD", "memo TLOSD"]' -p token.issuer@active
cleos push action stablecarbon transfer '["token.issuer", "tom", "1000.0000 TLOSD", "memo TLOSD"]' -p token.issuer@active
cleos push action stablecarbon transfer '["token.issuer", "kate", "1000.0000 TLOSD", "memo TLOSD"]' -p token.issuer@active

echo "-------- telosdacdrop (TLOSDAC) ---------"
cleos set contract telosdacdrop $PWD -p telosdacdrop@active
cleos push action telosdacdrop create '[ "token.issuer", "1000000000.0000 TLOSDAC"]' -p telosdacdrop@active
cleos push action telosdacdrop issue '["token.issuer", "500000.0000 TLOSDAC", "memo TLOSDAC"]' -p token.issuer@active
cleos push action telosdacdrop transfer '["token.issuer", "alice", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p token.issuer@active
cleos push action telosdacdrop transfer '["token.issuer", "bob", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p token.issuer@active
cleos push action telosdacdrop transfer '["token.issuer", "tom", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p token.issuer@active
cleos push action telosdacdrop transfer '["token.issuer", "kate", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p token.issuer@active

echo "-------- stablecoin.z (EZAR) ---------"
cleos set contract stablecoin.z $PWD -p stablecoin.z@active
cleos push action stablecoin.z create '[ "token.issuer", "1000000000.00 EZAR"]' -p stablecoin.z@active
cleos push action stablecoin.z issue '["token.issuer", "10000.00 EZAR", "memo EZAR"]' -p token.issuer@active
cleos push action stablecoin.z transfer '["token.issuer", "alice", "1000.00 EZAR", "memo EZAR"]' -p token.issuer@active
cleos push action stablecoin.z transfer '["token.issuer", "bob", "1000.00 EZAR", "memo EZAR"]' -p token.issuer@active
cleos push action stablecoin.z transfer '["token.issuer", "tom", "1000.00 EZAR", "memo EZAR"]' -p token.issuer@active
cleos push action stablecoin.z transfer '["token.issuer", "kate", "1000.00 EZAR", "memo EZAR"]' -p token.issuer@active

echo "-------- yanggangcoin (YANG) ---------"
cleos set contract yanggangcoin $PWD -p yanggangcoin@active
cleos push action yanggangcoin create '[ "token.issuer", "1000000000.0000 YANG"]' -p yanggangcoin@active
cleos push action yanggangcoin issue '["token.issuer", "10000.0000 YANG", "memo YANG"]' -p token.issuer@active
cleos push action yanggangcoin transfer '["token.issuer", "alice", "1000.0000 YANG", "memo YANG"]' -p token.issuer@active
cleos push action yanggangcoin transfer '["token.issuer", "bob", "1000.0000 YANG", "memo YANG"]' -p token.issuer@active
cleos push action yanggangcoin transfer '["token.issuer", "tom", "1000.0000 YANG", "memo YANG"]' -p token.issuer@active
cleos push action yanggangcoin transfer '["token.issuer", "kate", "1000.0000 YANG", "memo YANG"]' -p token.issuer@active

echo "-------- vapaeetokens (CNT) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "token.issuer", "500000000.0000 CNT"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["token.issuer", "10000.0000 CNT", "memo CNT"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "alice", "1000.0000 CNT", "memo CNT"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "bob", "1000.0000 CNT", "memo CNT"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "tom", "1000.0000 CNT", "memo CNT"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "kate", "1000.0000 CNT", "memo CNT"]' -p token.issuer@active

echo "-------- vapaeetokens (BOX) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "token.issuer", "500000000.0000 BOX"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["token.issuer", "10000.0000 BOX", "memo BOX"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "alice", "1000.0000 BOX", "memo BOX"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "bob", "1000.0000 BOX", "memo BOX"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "tom", "1000.0000 BOX", "memo BOX"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "kate", "1000.0000 BOX", "memo BOX"]' -p token.issuer@active

echo "-------- vapaeetokens (VPE) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "token.issuer", "500000000.0000 VPE"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["token.issuer", "10000.0000 VPE", "memo VPE"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "alice", "1000.0000 VPE", "memo VPE"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "bob", "1000.0000 VPE", "memo VPE"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "tom", "1000.0000 VPE", "memo VPE"]' -p token.issuer@active
cleos push action vapaeetokens transfer '["token.issuer", "kate", "1000.0000 VPE", "memo VPE"]' -p token.issuer@active

echo "-------- cryptomulita (MULITA & FAKE) ---------"
cleos set contract cryptomulita $PWD -p cryptomulita@active
cleos push action cryptomulita create '[ "token.issuer", "500000000.0000 MULITA"]' -p cryptomulita@active
cleos push action cryptomulita issue '["token.issuer", "10000.0000 MULITA", "memo MULITA"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "alice", "1000.0000 MULITA", "memo MULITA"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "bob", "1000.0000 MULITA", "memo MULITA"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "tom", "1000.0000 MULITA", "memo MULITA"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "kate", "1000.0000 MULITA", "memo MULITA"]' -p token.issuer@active
cleos push action cryptomulita create '[ "token.issuer", "500000000.0000 FAKE"]' -p cryptomulita@active
cleos push action cryptomulita issue '["token.issuer", "10000.0000 FAKE", "memo FAKE"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "alice", "1000.0000 FAKE", "memo FAKE"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "bob", "1000.0000 FAKE", "memo FAKE"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "tom", "1000.0000 FAKE", "memo FAKE"]' -p token.issuer@active
cleos push action cryptomulita transfer '["token.issuer", "kate", "1000.0000 FAKE", "memo FAKE"]' -p token.issuer@active

echo "----- loading init DAO state ----"
cleos push action telosmaindex init '[]' -p telosmaindex@active
sleep 1
cleos push action telosmaindex init '[]' -p telosmaindex@active
echo "- table: state -"
cleos get table telosmaindex telosmaindex state
echo "- table: tokengroups -"
cleos get table telosmaindex telosmaindex tokengroups
echo "- table: tokens -"
cleos get table telosmaindex telosmaindex tokens
sleep 1



echo "----- token.issuer deposits enough to pay token registration ----"
cleos push action eosio.token transfer  '["token.issuer",  "telosmaindex","5000.0000 TLOS","deposit"]' -p token.issuer@active

echo "----- loading tokens ----"

# register tokens
echo "-- register TLOS --" 
# cleos push action telosmaindex addtoken '["eosio.token","TLOS",4,"token.issuer", "Telos", "https://telosfoundation.io", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/telos.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/telos-lg.png",true]' -p token.issuer
# cleos push action telosmaindex setcurrency '["TLOS", true]' -p token.issuer
echo "-- register VIITA --" 
cleos push action telosmaindex addtoken '["viitasphere1","VIITA",4,"token.issuer", "Viitasphere", "https://viitasphere.com", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/viitasphere.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/viitasphere-lg.png",true]' -p token.issuer
echo "-- register VIICT --" 
cleos push action telosmaindex addtoken '["viitasphere1","VIICT",0,"token.issuer", "Viitasphere", "https://viitasphere.com", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/viitasphere.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/viitasphere-lg.png",true]' -p token.issuer
echo "-- register QBE --" 
cleos push action telosmaindex addtoken '["qubicletoken","QBE",4,"token.issuer", "Qubicles", "https://fenero.io/qubicles", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/qbe.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/qbe-lg.png",true]' -p token.issuer
echo "-- register ACORN --" 
cleos push action telosmaindex addtoken '["acornaccount","ACORN",4,"token.issuer", "ACORN", "http://acorns.fun", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/acorn.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/acorn-lg.png",true]' -p token.issuer
echo "-- register YANG --" 
cleos push action telosmaindex addtoken '["yanggangcoin","YANG",4,"token.issuer", "Yang Gang Coin", "https://www.yang2020.com/", "Together, We Can Build a New Kind of Economy, One That Puts People First.", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/uploads/yang-banner.jpg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/yang-coin.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/yang-coin-lg.png",true]' -p token.issuer
cleos push action telosmaindex settokendata '["YANG", 0, "add", "twitter", "Official Twitter Account", "https://twitter.com/andrewyang"]' -p token.issuer


echo "-- register FUTBOL --" 
cleos push action telosmaindex addtoken '["futboltokens","FUTBOL",4,"token.issuer", "Fútbol Tokens", "http://futboltokens.online/", "Collect the best football trading cards and win prizes", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/uploads/futboltokens-banner.jpg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/futboltokens.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/futboltokens.png",true]' -p token.issuer
cleos push action telosmaindex settokendata '["FUTBOL", 0, "add", "youtube", "Video en español", "https://www.youtube.com/watch?v=4fYHjH5ylnA"]' -p token.issuer

echo "-- register LEGEND --" 
cleos push action telosmaindex addtoken '["teloslegends","LEGEND",0,"token.issuer", "Telos Legends", "http://futboltokens.online/", "Collect the best football trading cards and win prizes", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/uploads/legend-banner.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/legend.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/legend-lg.png",false]' -p token.issuer

echo "-- register OLIVE --" 
cleos push action telosmaindex addtoken '["oliveaccount","OLIVE",4,"token.issuer", "OLIVE", "http://democratic.money/olive", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/olive.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/olive-lg.png",true]' -p token.issuer
echo "-- register HEART --" 
cleos push action telosmaindex addtoken '["revelation21","HEART",4,"token.issuer", "HEART", "https://steemit.com/@steemchurch", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/beautitude.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/beautitude-lg.png",true]' -p token.issuer
echo "-- register EDNA --" 
cleos push action telosmaindex addtoken '["ednazztokens","EDNA",4,"token.issuer", "EDNA", "https://github.com/EDNA-LIFE", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/edna.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/edna-lg.png",true]' -p token.issuer
echo "-- register TEACH --" 
cleos push action telosmaindex addtoken '["teachology14","TEACH",4,"token.issuer", "Teachology", "http://teachology.io", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/teach.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/teach-lg.png",true]' -p token.issuer
echo "-- register ROBO --" 
cleos push action telosmaindex addtoken '["proxibotstkn","ROBO",4,"token.issuer", "Proxibots", "https://proxibots.io", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/proxibots.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/proxibots-lg.png",true]' -p token.issuer
echo "-- register TLOSD --" 
cleos push action telosmaindex addtoken '["stablecarbon","TLOSD",4,"token.issuer", "Carbon", "https://www.carbon.money", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/carbon.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/carbon.svg",true]' -p token.issuer
# cleos push action telosmaindex setcurrency '["TLOSD", true]' -p telosmaindex@active

echo "-- register TLOSDAC --" 
cleos push action telosmaindex addtoken '["telosdacdrop","TLOSDAC",4,"token.issuer", "TelosDAC", "https://telosdac.io/", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/telosdac.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/telosdac-lg.png",true]' -p token.issuer
echo "-- register EZAR --"
cleos push action telosmaindex addtoken '["stablecoin.z","EZAR",2,"token.issuer", "South African Rand", "https://t.me/ezartoken", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/ezar.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/ezar-lg.png",true]' -p token.issuer

echo "-- register CNT --"
cleos push action telosmaindex addtoken '["vapaeetokens", "CNT", 4, "token.issuer", "Cards & Tokens", "http://cardsandtokens.com", "A platform where you can create themed albums and trading cards to collect and play making money in the process.", "assets/img/cards-and-tokens-1200x400.jpeg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/cnt.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/cnt-lg.svg",true]' -p token.issuer
cleos push action telosmaindex settokendata '["CNT", 0, "add", "youtube", "Promo video", "https://youtu.be/YSVJgKsSobA"]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["CNT", 0, "add", "twitter", "Membership cards", "https://twitter.com/TokensCards/status/1109668817175748608"]' -p token.issuer
cleos push action telosmaindex settokendata '["CNT", 0, "add", "youtube", "Demo video", "https://www.youtube.com/watch?v=jhL1KyifGEs&list=PLIv5p7BTy5wxqwqs0fGyjtOahoO3YWX0x&index=1"]' -p token.issuer
cleos push action telosmaindex settokendata '["CNT", 0, "add", "twitter", "The CNT token airdrop", "https://twitter.com/TokensCards/status/1105088865994452993"]' -p token.issuer

echo "-- register BOX --" 
cleos push action telosmaindex addtoken '["vapaeetokens", "BOX", 4, "token.issuer", , "Board Game Box", "https://vapaee.io/bgbox", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/box.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/box-lg.png",true]' -p token.issuer
echo "-- register VPE --" 
cleos push action telosmaindex addtoken '["vapaeetokens", "VPE", 6, "token.issuer", , "Vapaée", "https://vapaee.io", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/vapaee.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/vapaee-lg.png",true]' -p token.issuer

echo "-- register MULITA --" 
cleos push action telosmaindex addtoken '["cryptomulita","MULITA",4,"token.issuer", "Crypto Mulita", "https://steemit.com/@viterbo", "", "", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/mulita.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/mulita.svg",true]' -p token.issuer
echo "-- register FAKE --" 
cleos push action telosmaindex addtoken '["cryptomulita","FAKE",4,"token.issuer", "FAKE", "", "", "", "", "",true]' -p token.issuer


# telosmain push action telosmaindex updatetoken '["YNT", "YNT", "https://sesacash.com", "YNT - Utility token for Sesacash (sesacash.com)", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/uploads/yensesa-logo.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/yensesa-icon-1.svg", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/yensesa-icon-1.svg",true]' -p token.issuer

# telosmain push action telosmaindex updatetoken '["LEGEND", "LEGEND", "", "THE LEGENDS OF TELOS ARE COMING!", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/uploads/legend-banner.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/legend.png", "https://raw.githubusercontent.com/vapaee/vapaee.io-website/master/www/assets/logos/legend-lg.png",false]' -p token.issuer



# add issuers to the tokens
# echo "-- adding issuers to the tokens --" 
# cleos push action telosmaindex addissuer '["telosmaindex","VPE"]' -p telosmaindex@active



echo "-------- 3_load_tokens finished ---------"