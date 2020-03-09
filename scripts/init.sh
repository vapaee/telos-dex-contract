#!/bin/bash
# rm /var/www/blockchain/eosio/data -fr




./1_create_accounts.sh

sleep 1

./2_deploy_contract.sh

sleep 1

./3_load_system.sh

sleep 1

./4_load_tokens.sh

sleep 1

./5_register_interfaces.sh

sleep 1

./6_deposits.sh

sleep 1

./7_orders.sh