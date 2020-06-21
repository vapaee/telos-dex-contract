# Maintenance and user's score.

[index](./README.md)

All historical data is saved in RAM for fast and easy access (especially for other contracts), but this can not be there forever. To solve this problem a maintenance task was added in order to keep this storage cost under control and the expiration limits can be changed by the community voting as DAO.

This task search for the firsts expired entries of all history-related tables and drops them to release RAM space. For each drop that this task performs, the user who called the action will receive an accumulative recognition score as a reward. This promotes the user to keep calling the task (until no more expired entries are found and the user stops receiving rewards).

## Historical tables
There are five tables storing historical data which entries after a certain time become just documental and is no longer needed to be available in RAM. 
- **history** ([code](../../src/include/dex/tables/history.hpp), [doc](./Tables.md#history))    
  Each canonical market hast its own history table of all deals made in the canonical or the inverse market.   
    
- **historyall** ([code](../../src/include/dex/tables/historyall.hpp), [doc](./Tables.md#historyall))   
  The history table uses the market id as scope, so we need to iterate all of them to find the oldest entry in the maitenance task. So every entry in any history table has a reference entry in this historyall table which scope is the name of the contract.   
    
- **historyblock** ([code](../../src/include/dex/tables/historyblock.hpp), [doc](./Tables.md#historyblock))   
  This table is similar to history but it keeps aggregated data from all transactions within the same hour (like entrance, max, min, volume, etc). This helps to quickly build a last-24h-state of any market and also provides preprocessed data for fast chart rendering.
    
- **ballots** ([code](../../src/include/dex/tables/ballots.hpp), [doc](./Tables.md#ballots))   
  Telos DEX uses [Telos Decide](https://docs.telos.net/developers/services/telos-decide) to create ballots for the community to vote and participate in the governance of the System and this table holds a reference of all created ballots. This info is needed to know what to do when a ballot finishes. Once it's closed, the entry becomes just documental and can be deleted anytime.   
    
- **events** ([code](../../src/include/dex/tables/events.hpp), [doc](./Tables.md#events))   
  All the system events are registered in a single table, this coul'd be the most spensive and less usefull table af all, so it should be pruded fricuently (because it can grow very fast).

## Scores: POINTS & EXP
In order to create some motivation for the users to voluntarily call the maintenance action, a gamification score is introduced. All Telos DEX users will have some POINTS and EXP balances which are not transferable.

The Points are a temporary score while the Experience is a permanent recognition. These score balances do not affect in any way the functioning of the DEX and do not give the user any grant in the system. They are just a competition gaming concept just to bring some fun and enthusiasm.

Each time a user calls the maintenance action the user receives some score as a reward for each entry pruned of any table. Another way of earning some score is when the user makes a deal with another user. Then both users earn some score (more for the taker than for the maker) and this score is based on the volume of the deal (only apply for markets with TLOS as currency).

## Hidden Maintenance
Each time a new technology arrives, it comes with new strategies and good practices, and the blockchain is not an exception. As it can be observed in other systems (like REX), there's a maintenance task hidden in the ordinary execution of certain not time-consuming actions.

In Telos DEX there are two of these actions and those are: canceling an existing order and created a not satisfied new order (market maker). In any of these two cases the smart contract executes the maintenance task on behalf of the user's CPU resource. If the task finds an expired entry, it will be dropped and the user rewarded with a score.

---------------------
DAO related documentation:   
- read more about ACTION balloton [hblockprune](./DAO.md#hblockprune).
- read more about ACTION balloton [eventsprune](./DAO.md#eventsprune).
- read more about ACTION balloton [pointsprune](./DAO.md#pointsprune).
- read more about ACTION balloton [ballotsprune](./DAO.md#ballotsprune).


