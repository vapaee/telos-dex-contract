#!/bin/bash

"""Start keosd and nodeos
link: https://docs.telos.net/developers/platform/
development-environment/start-your-node-setup
"""

set -e

# Step 1.1: Start keosd
keosd &

# Step 1.2: Start nodeos
nodeos -e -p eosio \
--max-transaction-time=2000 \
--plugin eosio::producer_plugin \
--plugin eosio::producer_api_plugin \
--plugin eosio::chain_api_plugin \
--plugin eosio::http_plugin \
--plugin eosio::history_plugin \
--plugin eosio::history_api_plugin \
--filter-on="*" \
--access-control-allow-origin='*' \
--contracts-console \
--http-validate-host=false \
--verbose-http-errors >> /tmp/nodeos.log 2>&1 &

sleep 1

cleos wallet create --to-console

cleos wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
cleos wallet import --private-key 5J1astpVJcAJVGX8PGWN9KCcHU5DMszi4gJgCEpWc5DxmpTsKqp

cleos create account eosio eosio.token EOS8RoCAXxWYUW2v4xkG19F57BDVBzpt9NN2iDsD1ouQNyV2BkiNc
cleos create account eosio telosprofile EOS8RoCAXxWYUW2v4xkG19F57BDVBzpt9NN2iDsD1ouQNyV2BkiNc
cleos create account eosio telosmaindex EOS8RoCAXxWYUW2v4xkG19F57BDVBzpt9NN2iDsD1ouQNyV2BkiNc
cleos create account eosio eventhandler EOS8RoCAXxWYUW2v4xkG19F57BDVBzpt9NN2iDsD1ouQNyV2BkiNc
cleos create account eosio vapaeetokens EOS8RoCAXxWYUW2v4xkG19F57BDVBzpt9NN2iDsD1ouQNyV2BkiNc

sleep 1
cd /telos-dex-contract
sleep 1
ls
#sleep 1
#make deploy

bash