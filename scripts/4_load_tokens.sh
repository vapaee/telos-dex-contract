#!/bin/bash
HOME=/var/www/telos-dex-contract

echo "-------- 4_load_tokens ---------"
sleep 1

cd $HOME/src/contracts/telos.contracts/contracts/eosio.token

echo "-------- eosio.token (TLOS) ---------"
cleos set contract eosio.token $PWD -p eosio.token@active
cleos push action eosio.token create '[ "telosmaindex", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token create '[ "telosmaindex", "1000000000.0000 TLOS"]' -p eosio.token@active
cleos push action eosio.token issue '["telosmaindex", "10000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "alice", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "alice", "1001.0000 TLOS", "memo 1001 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "bob", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "tom", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active
cleos push action eosio.token transfer '["telosmaindex", "kate", "1000.0000 TLOS", "memo 1000 TLOS"]' -p telosmaindex@active

echo "-------- acornaccount (ACORN) ---------"
cleos set contract acornaccount $PWD -p acornaccount@active
cleos push action acornaccount create '[ "telosmaindex", "461168601842738.0000 ACORN"]' -p acornaccount@active
cleos push action acornaccount issue '["telosmaindex", "10000.0000 ACORN", "memo ACORN"]' -p telosmaindex@active
cleos push action acornaccount transfer '["telosmaindex", "alice", "1000.0000 ACORN", "memo ACORN"]' -p telosmaindex@active
cleos push action acornaccount transfer '["telosmaindex", "bob", "1000.0000 ACORN", "memo ACORN"]' -p telosmaindex@active
cleos push action acornaccount transfer '["telosmaindex", "tom", "1000.0000 ACORN", "memo ACORN"]' -p telosmaindex@active
cleos push action acornaccount transfer '["telosmaindex", "kate", "1000.0000 ACORN", "memo ACORN"]' -p telosmaindex@active

echo "-------- oliveaccount (OLIVE) ---------"
cleos set contract oliveaccount $PWD -p oliveaccount@active
cleos push action oliveaccount create '[ "telosmaindex", "461168601842738.0000 OLIVE"]' -p oliveaccount@active
cleos push action oliveaccount issue '["telosmaindex", "1000.0000 OLIVE", "memo OLIVE"]' -p telosmaindex@active
cleos push action oliveaccount transfer '["telosmaindex", "alice", "100.0000 OLIVE", "memo OLIVE"]' -p telosmaindex@active
cleos push action oliveaccount transfer '["telosmaindex", "bob", "100.0000 OLIVE", "memo OLIVE"]' -p telosmaindex@active
cleos push action oliveaccount transfer '["telosmaindex", "tom", "100.0000 OLIVE", "memo OLIVE"]' -p telosmaindex@active
cleos push action oliveaccount transfer '["telosmaindex", "kate", "100.0000 OLIVE", "memo OLIVE"]' -p telosmaindex@active

echo "-------- revelation21 (HEART) ---------"
cleos set contract revelation21 $PWD -p revelation21@active
cleos push action revelation21 create '[ "telosmaindex", "2100000000.0000 HEART"]' -p revelation21@active
cleos push action revelation21 issue '["telosmaindex", "1000.0000 HEART", "memo HEART"]' -p telosmaindex@active
cleos push action revelation21 transfer '["telosmaindex", "alice", "100.0000 HEART", "memo HEART"]' -p telosmaindex@active
cleos push action revelation21 transfer '["telosmaindex", "bob", "100.0000 HEART", "memo HEART"]' -p telosmaindex@active
cleos push action revelation21 transfer '["telosmaindex", "tom", "100.0000 HEART", "memo HEART"]' -p telosmaindex@active
cleos push action revelation21 transfer '["telosmaindex", "kate", "100.0000 HEART", "memo HEART"]' -p telosmaindex@active

echo "-------- futboltokens (FUTBOL) ---------"
cleos set contract futboltokens $PWD -p futboltokens@active
cleos push action futboltokens create '[ "telosmaindex", "2100000000.0000 FUTBOL"]' -p futboltokens@active
cleos push action futboltokens issue '["telosmaindex", "10000.0000 FUTBOL", "memo FUTBOL"]' -p telosmaindex@active
cleos push action futboltokens transfer '["telosmaindex", "alice", "1000.0000 FUTBOL", "memo FUTBOL"]' -p telosmaindex@active
cleos push action futboltokens transfer '["telosmaindex", "bob", "1000.0000 FUTBOL", "memo FUTBOL"]' -p telosmaindex@active
cleos push action futboltokens transfer '["telosmaindex", "tom", "1000.0000 FUTBOL", "memo FUTBOL"]' -p telosmaindex@active
cleos push action futboltokens transfer '["telosmaindex", "kate", "1000.0000 FUTBOL", "memo FUTBOL"]' -p telosmaindex@active

echo "-------- teloslegends (LEGEND) ---------"
cleos set contract teloslegends $PWD -p teloslegends@active
cleos push action teloslegends create '[ "telosmaindex", "12 LEGEND"]' -p teloslegends@active
cleos push action teloslegends issue '["telosmaindex", "10 LEGEND", "memo LEGEND"]' -p telosmaindex@active
cleos push action teloslegends transfer '["telosmaindex", "alice", "1 LEGEND", "memo LEGEND"]' -p telosmaindex@active
cleos push action teloslegends transfer '["telosmaindex", "bob", "1 LEGEND", "memo LEGEND"]' -p telosmaindex@active
cleos push action teloslegends transfer '["telosmaindex", "tom", "1 LEGEND", "memo LEGEND"]' -p telosmaindex@active
cleos push action teloslegends transfer '["telosmaindex", "kate", "1 LEGEND", "memo LEGEND"]' -p telosmaindex@active

echo "-------- viitasphere1 (VIITA) ---------"
cleos set contract viitasphere1 $PWD -p viitasphere1@active
cleos push action viitasphere1 create '[ "telosmaindex", "10000000000.0000 VIITA"]' -p viitasphere1@active
cleos push action viitasphere1 issue '["telosmaindex", "1000.0000 VIITA", "memo VIITA"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "alice", "100.0000 VIITA", "memo VIITA"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "bob", "100.0000 VIITA", "memo VIITA"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "tom", "100.0000 VIITA", "memo VIITA"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "kate", "100.0000 VIITA", "memo VIITA"]' -p telosmaindex@active

echo "-------- viitasphere1 (VIICT) ---------"
cleos push action viitasphere1 create '[ "telosmaindex", "500000 VIICT"]' -p viitasphere1@active
cleos push action viitasphere1 issue '["telosmaindex", "1000 VIICT", "memo VIICT"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "alice", "100 VIICT", "memo VIICT"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "bob", "100 VIICT", "memo VIICT"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "tom", "100 VIICT", "memo VIICT"]' -p telosmaindex@active
cleos push action viitasphere1 transfer '["telosmaindex", "kate", "100 VIICT", "memo VIICT"]' -p telosmaindex@active

echo "-------- qubicletoken (QBE) ---------"
cleos set contract qubicletoken $PWD -p qubicletoken@active
cleos push action qubicletoken create '[ "telosmaindex", "100000000.0000 QBE"]' -p qubicletoken@active
cleos push action qubicletoken issue '["telosmaindex", "1000.0000 QBE", "memo QBE"]' -p telosmaindex@active
cleos push action qubicletoken transfer '["telosmaindex", "alice", "100.0000 QBE", "memo QBE"]' -p telosmaindex@active
cleos push action qubicletoken transfer '["telosmaindex", "bob", "100.0000 QBE", "memo QBE"]' -p telosmaindex@active
cleos push action qubicletoken transfer '["telosmaindex", "tom", "100.0000 QBE", "memo QBE"]' -p telosmaindex@active
cleos push action qubicletoken transfer '["telosmaindex", "kate", "100.0000 QBE", "memo QBE"]' -p telosmaindex@active

echo "-------- ednazztokens (EDNA) ---------"
cleos set contract ednazztokens $PWD -p ednazztokens@active
cleos push action ednazztokens create '[ "telosmaindex", "1300000000.0000 EDNA"]' -p ednazztokens@active
cleos push action ednazztokens issue '["telosmaindex", "1000.0000 EDNA", "memo EDNA"]' -p telosmaindex@active
cleos push action ednazztokens transfer '["telosmaindex", "alice", "100.0000 EDNA", "memo EDNA"]' -p telosmaindex@active
cleos push action ednazztokens transfer '["telosmaindex", "bob", "100.0000 EDNA", "memo EDNA"]' -p telosmaindex@active
cleos push action ednazztokens transfer '["telosmaindex", "tom", "100.0000 EDNA", "memo EDNA"]' -p telosmaindex@active
cleos push action ednazztokens transfer '["telosmaindex", "kate", "100.0000 EDNA", "memo EDNA"]' -p telosmaindex@active

echo "-------- teachology14 (TEACH) ---------"
cleos set contract teachology14 $PWD -p teachology14@active
cleos push action teachology14 create '[ "telosmaindex", "10000000000.0000 TEACH"]' -p teachology14@active
cleos push action teachology14 issue '["telosmaindex", "1000.0000 TEACH", "memo TEACH"]' -p telosmaindex@active
cleos push action teachology14 transfer '["telosmaindex", "alice", "100.0000 TEACH", "memo TEACH"]' -p telosmaindex@active
cleos push action teachology14 transfer '["telosmaindex", "bob", "100.0000 TEACH", "memo TEACH"]' -p telosmaindex@active
cleos push action teachology14 transfer '["telosmaindex", "tom", "100.0000 TEACH", "memo TEACH"]' -p telosmaindex@active
cleos push action teachology14 transfer '["telosmaindex", "kate", "100.0000 TEACH", "memo TEACH"]' -p telosmaindex@active

echo "-------- proxibotstkn (ROBO) ---------"
cleos set contract proxibotstkn $PWD -p proxibotstkn@active
cleos push action proxibotstkn create '[ "telosmaindex", "1000000000.0000 ROBO"]' -p proxibotstkn@active
cleos push action proxibotstkn issue '["telosmaindex", "1000.0000 ROBO", "memo ROBO"]' -p telosmaindex@active
cleos push action proxibotstkn transfer '["telosmaindex", "alice", "100.0000 ROBO", "memo ROBO"]' -p telosmaindex@active
cleos push action proxibotstkn transfer '["telosmaindex", "bob", "100.0000 ROBO", "memo ROBO"]' -p telosmaindex@active
cleos push action proxibotstkn transfer '["telosmaindex", "tom", "100.0000 ROBO", "memo ROBO"]' -p telosmaindex@active
cleos push action proxibotstkn transfer '["telosmaindex", "kate", "100.0000 ROBO", "memo ROBO"]' -p telosmaindex@active

echo "-------- stablecarbon (TLOSD) ---------"
cleos set contract stablecarbon $PWD -p stablecarbon@active
cleos push action stablecarbon create '[ "telosmaindex", "1000000000.0000 TLOSD"]' -p stablecarbon@active
cleos push action stablecarbon issue '["telosmaindex", "10000.0000 TLOSD", "memo TLOSD"]' -p telosmaindex@active
cleos push action stablecarbon transfer '["telosmaindex", "alice", "1000.0000 TLOSD", "memo TLOSD"]' -p telosmaindex@active
cleos push action stablecarbon transfer '["telosmaindex", "bob", "1000.0000 TLOSD", "memo TLOSD"]' -p telosmaindex@active
cleos push action stablecarbon transfer '["telosmaindex", "tom", "1000.0000 TLOSD", "memo TLOSD"]' -p telosmaindex@active
cleos push action stablecarbon transfer '["telosmaindex", "kate", "1000.0000 TLOSD", "memo TLOSD"]' -p telosmaindex@active

echo "-------- telosdacdrop (TLOSDAC) ---------"
cleos set contract telosdacdrop $PWD -p telosdacdrop@active
cleos push action telosdacdrop create '[ "telosmaindex", "1000000000.0000 TLOSDAC"]' -p telosdacdrop@active
cleos push action telosdacdrop issue '["telosmaindex", "500000.0000 TLOSDAC", "memo TLOSDAC"]' -p telosmaindex@active
cleos push action telosdacdrop transfer '["telosmaindex", "alice", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p telosmaindex@active
cleos push action telosdacdrop transfer '["telosmaindex", "bob", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p telosmaindex@active
cleos push action telosdacdrop transfer '["telosmaindex", "tom", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p telosmaindex@active
cleos push action telosdacdrop transfer '["telosmaindex", "kate", "50000.0000 TLOSDAC", "memo TLOSDAC"]' -p telosmaindex@active

echo "-------- stablecoin.z (EZAR) ---------"
cleos set contract stablecoin.z $PWD -p stablecoin.z@active
cleos push action stablecoin.z create '[ "telosmaindex", "1000000000.00 EZAR"]' -p stablecoin.z@active
cleos push action stablecoin.z issue '["telosmaindex", "10000.00 EZAR", "memo EZAR"]' -p telosmaindex@active
cleos push action stablecoin.z transfer '["telosmaindex", "alice", "1000.00 EZAR", "memo EZAR"]' -p telosmaindex@active
cleos push action stablecoin.z transfer '["telosmaindex", "bob", "1000.00 EZAR", "memo EZAR"]' -p telosmaindex@active
cleos push action stablecoin.z transfer '["telosmaindex", "tom", "1000.00 EZAR", "memo EZAR"]' -p telosmaindex@active
cleos push action stablecoin.z transfer '["telosmaindex", "kate", "1000.00 EZAR", "memo EZAR"]' -p telosmaindex@active

echo "-------- yanggangcoin (YANG) ---------"
cleos set contract yanggangcoin $PWD -p yanggangcoin@active
cleos push action yanggangcoin create '[ "telosmaindex", "1000000000.0000 YANG"]' -p yanggangcoin@active
cleos push action yanggangcoin issue '["telosmaindex", "10000.0000 YANG", "memo YANG"]' -p telosmaindex@active
cleos push action yanggangcoin transfer '["telosmaindex", "alice", "1000.0000 YANG", "memo YANG"]' -p telosmaindex@active
cleos push action yanggangcoin transfer '["telosmaindex", "bob", "1000.0000 YANG", "memo YANG"]' -p telosmaindex@active
cleos push action yanggangcoin transfer '["telosmaindex", "tom", "1000.0000 YANG", "memo YANG"]' -p telosmaindex@active
cleos push action yanggangcoin transfer '["telosmaindex", "kate", "1000.0000 YANG", "memo YANG"]' -p telosmaindex@active

echo "-------- vapaeetokens (CNT) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "telosmaindex", "500000000.0000 CNT"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["telosmaindex", "10000.0000 CNT", "memo CNT"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "alice", "1000.0000 CNT", "memo CNT"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "bob", "1000.0000 CNT", "memo CNT"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "tom", "1000.0000 CNT", "memo CNT"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "kate", "1000.0000 CNT", "memo CNT"]' -p telosmaindex@active

echo "-------- vapaeetokens (BOX) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "telosmaindex", "500000000.0000 BOX"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["telosmaindex", "10000.0000 BOX", "memo BOX"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "alice", "1000.0000 BOX", "memo BOX"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "bob", "1000.0000 BOX", "memo BOX"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "tom", "1000.0000 BOX", "memo BOX"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "kate", "1000.0000 BOX", "memo BOX"]' -p telosmaindex@active

echo "-------- vapaeetokens (VPE) ---------"
cleos set contract vapaeetokens $PWD -p vapaeetokens@active
cleos push action vapaeetokens create '[ "telosmaindex", "500000000.0000 VPE"]' -p vapaeetokens@active
cleos push action vapaeetokens issue '["telosmaindex", "10000.0000 VPE", "memo VPE"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "alice", "1000.0000 VPE", "memo VPE"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "bob", "1000.0000 VPE", "memo VPE"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "tom", "1000.0000 VPE", "memo VPE"]' -p telosmaindex@active
cleos push action vapaeetokens transfer '["telosmaindex", "kate", "1000.0000 VPE", "memo VPE"]' -p telosmaindex@active



echo "----- loading tokens ----"

# register tokens
echo "-- register TLOS --" 
cleos push action telosmaindex addtoken '["eosio.token","TLOS",4,"telosmaindex", "Telos", "https://telosfoundation.io", "", "", "/assets/logos/telos.png", "/assets/logos/telos-lg.png",true]' -p telosmaindex@active
cleos push action telosmaindex setcurrency '["TLOS", true]' -p telosmaindex@active
echo "-- register VIITA --" 
cleos push action telosmaindex addtoken '["viitasphere1","VIITA",4,"telosmaindex", "Viitasphere", "https://viitasphere.com", "", "", "/assets/logos/viitasphere.png", "/assets/logos/viitasphere-lg.png",true]' -p telosmaindex@active
echo "-- register VIICT --" 
cleos push action telosmaindex addtoken '["viitasphere1","VIICT",0,"telosmaindex", "Viitasphere", "https://viitasphere.com", "", "", "/assets/logos/viitasphere.png", "/assets/logos/viitasphere-lg.png",true]' -p telosmaindex@active
echo "-- register QBE --" 
cleos push action telosmaindex addtoken '["qubicletoken","QBE",4,"telosmaindex", "Qubicles", "https://fenero.io/qubicles", "", "", "/assets/logos/qbe.png", "/assets/logos/qbe-lg.png",true]' -p telosmaindex@active
echo "-- register ACORN --" 
cleos push action telosmaindex addtoken '["acornaccount","ACORN",4,"telosmaindex", "ACORN", "http://acorns.fun", "", "", "/assets/logos/acorn.svg", "/assets/logos/acorn-lg.png",true]' -p telosmaindex@active
echo "-- register YANG --" 
cleos push action telosmaindex addtoken '["yanggangcoin","YANG",4,"telosmaindex", "Yang Gang Coin", "https://www.yang2020.com/", "Together, We Can Build a New Kind of Economy, One That Puts People First.", "/assets/uploads/yang-banner.jpg", "/assets/logos/yang-coin.png", "/assets/logos/yang-coin-lg.png",true]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["YANG", 0, "add", "twitter", "Official Twitter Account", "https://twitter.com/andrewyang"]' -p telosmaindex@active


echo "-- register FUTBOL --" 
cleos push action telosmaindex addtoken '["futboltokens","FUTBOL",4,"telosmaindex", "Fútbol Tokens", "http://futboltokens.online/", "Collect the best football trading cards and win prizes", "/assets/uploads/futboltokens-banner.jpg", "/assets/logos/futboltokens.png", "/assets/logos/futboltokens.png",true]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["FUTBOL", 0, "add", "youtube", "Video en español", "https://www.youtube.com/watch?v=4fYHjH5ylnA"]' -p telosmaindex@active

echo "-- register LEGEND --" 
cleos push action telosmaindex addtoken '["teloslegends","LEGEND",0,"telosmaindex", "Telos Legends", "http://futboltokens.online/", "Collect the best football trading cards and win prizes", "/assets/uploads/legend-banner.png", "/assets/logos/legend.png", "/assets/logos/legend-lg.png",false]' -p telosmaindex@active

echo "-- register OLIVE --" 
cleos push action telosmaindex addtoken '["oliveaccount","OLIVE",4,"telosmaindex", "OLIVE", "http://democratic.money/olive", "", "", "/assets/logos/olive.png", "/assets/logos/olive-lg.png",true]' -p telosmaindex@active
echo "-- register HEART --" 
cleos push action telosmaindex addtoken '["revelation21","HEART",4,"telosmaindex", "HEART", "https://steemit.com/@steemchurch", "", "", "/assets/logos/beautitude.png", "/assets/logos/beautitude-lg.png",true]' -p telosmaindex@active
echo "-- register EDNA --" 
cleos push action telosmaindex addtoken '["ednazztokens","EDNA",4,"telosmaindex", "EDNA", "https://github.com/EDNA-LIFE", "", "", "/assets/logos/edna.png", "/assets/logos/edna-lg.png",true]' -p telosmaindex@active
echo "-- register TEACH --" 
cleos push action telosmaindex addtoken '["teachology14","TEACH",4,"telosmaindex", "Teachology", "http://teachology.io", "", "", "/assets/logos/teach.svg", "/assets/logos/teach-lg.png",true]' -p telosmaindex@active
echo "-- register ROBO --" 
cleos push action telosmaindex addtoken '["proxibotstkn","ROBO",4,"telosmaindex", "Proxibots", "https://proxibots.io", "", "", "/assets/logos/proxibots.png", "/assets/logos/proxibots-lg.png",true]' -p telosmaindex@active
echo "-- register TLOSD --" 
cleos push action telosmaindex addtoken '["stablecarbon","TLOSD",4,"telosmaindex", "Carbon", "https://www.carbon.money", "", "", "/assets/logos/carbon.svg", "/assets/logos/carbon.svg",true]' -p telosmaindex@active
cleos push action telosmaindex setcurrency '["TLOSD", true]' -p telosmaindex@active

echo "-- register TLOSDAC --" 
cleos push action telosmaindex addtoken '["telosdacdrop","TLOSDAC",4,"telosmaindex", "TelosDAC", "https://telosdac.io/", "", "", "/assets/logos/telosdac.png", "/assets/logos/telosdac-lg.png",true]' -p telosmaindex@active
echo "-- register EZAR --"
cleos push action telosmaindex addtoken '["stablecoin.z","EZAR",2,"telosmaindex", "South African Rand", "https://t.me/ezartoken", "", "", "/assets/logos/ezar.png", "/assets/logos/ezar-lg.png",true]' -p telosmaindex@active

echo "-- register CNT --"
cleos push action telosmaindex addtoken '["vapaeetokens", "CNT", 4, "telosmaindex", "Cards & Tokens", "http://cardsandtokens.com", "A platform where you can create themed albums and trading cards to collect and play making money in the process.", "assets/img/cards-and-tokens-1200x400.jpeg", "/assets/logos/cnt.svg", "/assets/logos/cnt-lg.svg",true]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["CNT", 0, "add", "youtube", "Promo video", "https://youtu.be/YSVJgKsSobA"]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["CNT", 0, "add", "twitter", "Membership cards", "https://twitter.com/TokensCards/status/1109668817175748608"]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["CNT", 0, "add", "youtube", "Demo video", "https://www.youtube.com/watch?v=jhL1KyifGEs&list=PLIv5p7BTy5wxqwqs0fGyjtOahoO3YWX0x&index=1"]' -p telosmaindex@active
cleos push action telosmaindex settokendata '["CNT", 0, "add", "twitter", "The CNT token airdrop", "https://twitter.com/TokensCards/status/1105088865994452993"]' -p telosmaindex@active

echo "-- register BOX --" 
cleos push action telosmaindex addtoken '["vapaeetokens", "BOX", 4, "telosmaindex", , "Board Game Box", "https://vapaee.io/bgbox", "", "", "/assets/logos/box.png", "/assets/logos/box-lg.png",true]' -p telosmaindex@active
echo "-- register VPE --" 
cleos push action telosmaindex addtoken '["vapaeetokens", "VPE", 6, "telosmaindex", , "Vapaée", "https://vapaee.io", "", "", "/assets/logos/vapaee.png", "/assets/logos/vapaee-lg.png",true]' -p telosmaindex@active


# telosmain push action telosmaindex updatetoken '["YNT", "YNT", "https://sesacash.com", "YNT - Utility token for Sesacash (sesacash.com)", "/assets/uploads/yensesa-logo.svg", "/assets/logos/yensesa-icon-1.svg", "/assets/logos/yensesa-icon-1.svg",true]' -p telosmaindex@active

# telosmain push action telosmaindex updatetoken '["LEGEND", "LEGEND", "", "THE LEGENDS OF TELOS ARE COMING!", "/assets/uploads/legend-banner.png", "/assets/logos/legend.png", "/assets/logos/legend-lg.png",false]' -p telosmaindex@active



# add issuers to the tokens
# echo "-- adding issuers to the tokens --" 
# cleos push action telosmaindex addissuer '["telosmaindex","VPE"]' -p telosmaindex@active



