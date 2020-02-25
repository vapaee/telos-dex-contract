#!/bin/bash
# rm /var/www/blockchain/eosio/data -fr




./1_create_accounts.sh

./2_deploy_contract.sh

./3_load_system.sh

./4_load_tokens.sh

./5_register_interfaces.sh

./6_deposits.sh

./7_orders.sh