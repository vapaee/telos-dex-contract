# telos-dex-contract
Telos DEX smart contract source code   
current version: v4.0.0

## About this project  
This *Telos DEX* project was initialy part of another bigger project called *[vapaee](https://github.com/vapaee/vapaee.io-source)*. This last one has a smart contract deployed in the *vapaeetokens* account, which implements every token-related service that will be needed for an even bigger project called [Cards & Tokens](https://cardsandtokens.com).

## About the project's funds
This project is built on top of Telos network, which has a *Worker Proposal System* (WPS) that helps fund projects somehow (and not always) related with this network. I presented a [proposal](https://vapaee.io/exchange/wp) and that consists of 4 deliveries. The last one was modified to separate the entire DEX service from the rest of my work, so that it was an independent project. This is what v4.x.x is all about.

## About this contract  
Vapaée DEX has its own contract called *vapaeetokens* which implements not only DEX services but also standard Token services with airdrop and staking included. After several talks with many members of the community I decided to separate de DEX part from the rest and give it away to the community. For this I created a separated contract containing only services refered to serve a DEX completely independed and managed as a DAO (using trail system).

----------------------

## versions

### v4.0.0 - DAO (Telos Decide)
- DAO: state of the cotnract can be changed throw Telos Decide ballots
- Concept of white and black token list (trusted of banned)
- Cost for registration of new token
- Maintenance implemented to prune too-old-entries from history, events of ballots tables

### v3.6.1 - UI integration
- UI registration. UI creators can now register themselves as UI
- Order action carries the UI'id, so if any fee is applied on this order, UI earns that fee.

### v3.6.0 - extracting DEX from vapaeetokens contrct to its own
- migrate code to compile with eosio.cdt 1.7.1
- migrated from vapaeetokens contract source code to telosmaindex contract source code
- restructure classes in modules
