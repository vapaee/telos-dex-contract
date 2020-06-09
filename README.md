# telos-dex-contract
Telos DEX smart contract source code   
current version: v4.2.0

## Telos DEX
Telos DEX is the first truly decentralized exchange on Telos blockchain running completely on chain (100% smart contract). This project started as a private initiative but in its fourth version was separated from the original project and rewritten to achieve maximum decentralization incorporating DAO functionalities using the main TLOS token to vote using Telos Decide.
- read more about [Vapaée DEX](https://github.com/vapaee/vapaee.io-source/).
- read more about [Telos Decide](https://docs.telos.net/developers/services/telos-decide).

## Multiple UI
Telos DEX is 100% smart contract, but there's no official interface to interact with that contract. However,  the contract itself has an internal list of all registered clients and provides a way for any developer or publisher to register a new app, website, or contract as a client for this DEX. In consequence, there will be many clients and each one will have its users, but all of them will share the same liquidity in Telos DEX smart contract. 

Telos DEX provides a centralization for liquidity while promoting client competition and more options for everybody. The contract is built in such a way that the fees over deals made, will be charged to the traders involved, each in the token received, and finally transferred to the clients involved.

## DEX as DAO
DEX stands for Decentralized Exchange but is often given the meaning of running in a smart contract,  but this is not enough to be truly decentralized.

Decentralization not only applies to the way we run code but also to the way we own public systems and take care of them as a community.

Telos DEX is served as a DAO, which stands for Decentralized Autonomous Organization, to provide the community with the ability of well-organized decision-making tools to adjust the internal functionalities by voting using Telos Decide. 
- read more about [DAO](../../doc/tech/DAO.md).

## Telos core service
This smart contract wants to be included in the Telos-core set of contracts and start to be part of the basic services that Telos has to offer. This not only includes putting the contract in the repository but also the contract account in mainnet must be multi-sig by the BPs.

## How to use it?
If you want to know what Telos DEX has to offer you, it depends on who you are.

- ### Traders
  Normal trader user will have may client options to interact with the same exchange, sharing liquidity with all the clients for the same contract.

- ### Token creators
  Token creators can register their tokens in Telos DEX, adding all kinds of information and images to show on the token's page.    
  Each registered token will be automáticaly added to the *token group zero*, which is the main default group. All the tokens in that group can be traded only using currency tokens (like TLOS).   
  However, when a token creator has many tokens to register and one of them is the currency for the others, a new Token group can be created and all those tokens added, so they can be traded against their specific currency token, without splitting the liquidity for other tokens.    
  - read more about [Currencies & Token Groups](../../doc/tech/Currencies.md).

- ### Interface creators
  Developers and publishers can register their app, website, or smart contract to be a client for this DEX, bringing all the information and images to be shown on the client's page. The client can be complete, having all the tokens available to trade or can be partial, allowing a specific set of markets for its users.    
  Combining client registration with the token group creation, a game (with many resources and its own currency) can have an inside-app-exchange only for the tokens of the game and let Telos DEX deal with the hard work, all without compromising the liquidity of other tokens in the same DEX.   
  - read more about [Currencies & Token Groups](../../doc/tech/Currencies.md).

- ### Telos community members
  This DEX works as a DAO and the token that count for voting is TLOS, using Telos Decide. So if you hold TLOS in your wallet, you already own this contract.

----------------------

## Documentation 
[Index](./doc/tech/README.md)

### [API](./doc/tech/API.md)
This document describes the system as a black box. It shows an exhaustive list of all actions in the contract and a minor description of the parameters.

### [Tables](./doc/tech/Tables.md)
This document describes the system as a white box. It shows you where is stored all data and what is used for. It shows an exhaustive list of all tables in the contract and a minor description of the fields.

### [Architecture](./doc/tech/Architecture.md)
This document describes the internal architecture of the system, enumerating all modules and describing their responsibilities.

### [Markets (canonical and reverse)](./doc/tech/Markets.md)
This document talks about the canonical-reverse nature of the markets and the internal representation. Given two tokens, there are two posible markets: the canonical market (A/B) and the inverse market (B/A).

### [Currencies and Token Groups](./doc/tech/Currencies.md)
This document explains the model design used to simplify the balance between restrictions (to avoid splitting the liquidity) and permissions (to allow any kind of private market needs). 

### [DAO](./doc/tech/DAO.md)
Telos DEX will operate as a DAO (Decentralized Autonomous Organization). That means that all TLOS token holders can vote on ballots (using Telos Decide) to determine if they want to change some configuration in the system or not.


----------------------

## versions
### v4.2.0 - Rewards & Enhancements
- Trades are rewarded with points and experience when they trade
- Volunteers for maintenance are rewarded with points and experience when they trade
- Some new DAO operations were added
- Documentation enhancements

### v4.1.0 - Documentation (and minor updates)
- Docs added
- bugfix in setcurrency
- bugfix in scripts for addtoken and token.init
- minor change in tokendata (category changed for shownas)

### v4.0.0 - DAO (Telos Decide)
- DAO: state of the cotnract can be changed throw Telos Decide ballots
- Concept of white and black token list (trusted of banned)
- Cost for registration of new token
- Maintenance implemented to prune too-old-entries from history, events of ballots tables
- Auto Withdraw: once a deal is finished the funds are automatically transferred to the owner (away from the contract ownership)

### v3.6.1 - UI integration
- UI registration. UI creators can now register themselves as UI
- Order action carries the UI'id, so if any fee is applied on this order, UI earns that fee.

### v3.6.0 - extracting DEX from vapaeetokens contrct to its own
- migrate code to compile with eosio.cdt 1.7.1
- migrated from vapaeetokens contract source code to telosmaindex contract source code
- restructure classes in modules

### <= v3.5.0 - previous versions
- this project is a fork of another. Go to [this link](https://github.com/vapaee/vapaee.io-source/tree/master/contracts) to find aolder versions of this same work.