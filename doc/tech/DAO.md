# Telos DEX is a DAO (Decentralized Autonomous Organization)

[index](./README.md)

DEX is a smart contract that provides token exchange services in a decentralized way. In order for decision-making to be decentralized too, the services of Telos Decide were used to provide Telos DEX with the characteristics of a DAO.

In order to change some of the properties of the state users can initiate a ballot on any operation, give the parameters, a brief explanation and pay the Telos Decide fees (that will be subtracted from the user deposits in Telos DEX smart contract)

There's a token blacklist for the tokens that were banned from the DEX for any reason. Those tokens are not allowed to be traded or even deposited in the Telos DEX. The community can ban any token voting as a DAO.

There's a token whitelist for tokens that are widely recognized as trusted tokens. These tokens are prevented from being banned and can be used by any client to filter the token list. The community can decide as a DAO to save a token or stop supporting it.

In the exchange, there are market makers (the ones who create orders and wait for others to make a deal) and there are market takers (the ones who create an order over some else's previous order price and seal a deal). Each has a different fee to pay and those fees can be modified by the community voting as DAO.

Telos DEX has a maintenance process that prunes some tables based on expiration time periods. Those expirations can be modified by the community voting as DAO. 

Finally, there's a token registration cost that can be adjusted by the community voting as DAO. 

# List of operations

All ballots in Telos DEX can be initiated by push a balloton action to the cotnract. The signing account must have enough deposits (inside Telos DEX) to cover the Telos Decides fees for creating a ballot.

## savetoken
This operation is used to add token to the whitelist

    cleos push action telosmaindex balloton '["savetoken", ["TLOS","eosio.token"], "this is the main token", "creator"]' -p creator@active

## bantoken
This operation is used to add token to the blacklist

    cleos push action telosmaindex balloton '["bantoken", ["FAKE","anyfaketoken"], "this is a fake token", "creator"]' -p creator@active

## makerfee
This operation is used change the market-maker fee

    cleos push action telosmaindex balloton '["makerfee", ["0.00000000 FEE"], "The maket maker should not be charged with fees", "creator"]' -p creator@active

## takerfee
This operation is used change the market-taker fee

    cleos push action telosmaindex balloton '["takerfee", ["0.02500000 FEE"], "The market taker should pay 2.5% in fee", "creator"]' -p creator@active

## setcurrency
This operation is used set a token as a currency for the token group zero

    cleos push action telosmaindex balloton '["setcurrency", ["DAI","dstabletoken"], "This is a decentralized stable token pegged to the dollar", "creator"]' -p creator@active

## historyprune
This operation is used change the amount of days that a history entry should be pruned

    cleos push action telosmaindex balloton '["historyprune", ["180"], "six months is more than enough", "creator"]' -p creator@active

## hblockprune
This operation is used change the amount of days that a history block entry should be pruned

    cleos push action telosmaindex balloton '["hblockprune", ["360"], "a year is ok to have 1-hour-block history", "creator"]' -p creator@active

## eventsprune
This operation is used change the amount of days that an event entry should be pruned

    cleos push action telosmaindex balloton '["eventsprune", ["15"], "Two weeks is more than enough", "creator"]' -p creator@active

## pointsprune
This operation is used change the amount of weeks the the user's points should be considered up to date

    cleos push action telosmaindex balloton '["pointsprune", ["8"], "Two months for the points to be remembered", "creator"]' -p creator@active

## ballotsprune
This operation is used change the amount of max entries that the ballots table should have

    cleos push action telosmaindex balloton '["ballotsprune", ["1000"], "Let's give it a huge margin", "creator"]' -p creator@active

## approvalmin
This operation is used change minimum percent of participation for ballot approval. Valid values start at 0.0 meaning no restriction to 1.0 meaning everybody must vote. Default value is 0.25 meaning a minimum of 25% participation for approval.

    cleos push action telosmaindex balloton '["approvalmin", ["0.35"], "We should increase the minimum percent to restrict even more.", "creator"]' -p creator@active

## regcost
This operation is used change the cost for new tokens registration

    cleos push action telosmaindex balloton '["regcost", ["5000.0000 TLOS"], "We should restrict more the token registration", "creator"]' -p creator@active

