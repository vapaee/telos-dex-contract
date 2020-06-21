# Telos DEX smart contract documentation
Telos DEX is a Decentralized Exchange implemented in one smart contract running on Telos blockchain. It provides exchange services for traders, token registration services for token creators, and client registration for wallets and websites implementing a complete or partial client.

In this section you will find technical documentation about internal architecture and data structure designs and implementation details.

## Documentation 

### [API](./API.md)
This document describes the system as a black box. It shows an exhaustive list of all actions in the contract and a minor description of the parameters.

### [Tables](./Tables.md)
This document describes the system as a white box. It shows you where is stored all data and what is used for. It shows an exhaustive list of all tables in the contract and a minor description of the fields.

### [Architecture](./Architecture.md)
This document describes the internal architecture of the system, enumerating all modules and describing their responsibilities.

### [Markets (canonical and reverse)](./Markets.md)
This document talks about the canonical-reverse nature of the markets and the internal representation. Given two tokens, there are two posible markets: the canonical market (A/B) and the inverse market (B/A).

### [Currencies and Token Groups](./Currencies.md)
This document explains the model design used to simplify the balance between restrictions (to avoid splitting the liquidity) and permissions (to allow any kind of private market needs). 

### [DAO](./DAO.md)
Telos DEX will operate as a DAO (Decentralized Autonomous Organization). That means that all TLOS token holders can vote on ballots (using Telos Decide) to determine if they want to change some configuration in the system or not.

### [Maintenance](./Maintenance.md)
Since all historical data is stored in RAM, a maintenance task is needed to be executed constantly to slowly prune this data dropping expired entries. All users who help to execute this task are rewarded with not-transferable scores (Points and Experience) giving gamification features to this DEX.
