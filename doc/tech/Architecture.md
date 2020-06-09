# Telos DEX Modules Architecture
Telos DEX is a complex software that not only allows trade between parties, but also allow auto registration of new Tokens and UIs, and community-management as a DAO.

To accomplish that, Telos DEX was designed as a modules based system in which each module has a specific responsability

[index](./README.md)

## DAO
DAO Module solves all the taking decision functionalities of the DEX. It integrates with Telos Decide services to do so.    
- read more about [DAO](./DAO.md).
- code: [dao.hpp](../../src/include/dex/modules/dao.hpp)

## Deposit
Deposit module handles all transfers of tokens from the outside to the contract, from the contract to the outside and internal transfers between accounts.
- code: [deposit.hpp](../../src/include/dex/modules/deposit.hpp)   

## Error
Error module centralize all the errors that the contract can throw. Each has a specific name and its used just once on the code. That way if you receive an error after pushing some action, you will receive three things: an error's name, a description of the error and one or more values related with the error. All that informatio is very usefull for the developers to understand what's happening and find the error much faster than a generic error message.
- code: [error.hpp](../../src/include/dex/modules/error.hpp)   

## Exchange  
Exchange module is responsible for all the trading management, handling all the orders.
- code: [exchange.hpp](../../src/include/dex/modules/exchange.hpp)   

## Experience  
Experience module is an experimental module. The goal is to reward users with some kind of recognition for being DEX users. So every time a deal is made, both traders earn POINTS and EXP. Also if any user executes the maintenance actions and it actually does some work, the user will also receive POINTS and EXP. For now, those credits are just for fun. They don't serve any other purpose other than lealty user recognition.
- code: [experience.hpp](../../src/include/dex/modules/experience.hpp)   

## Global  
Global is a module that implementates a state for the contract using singletton patern. Most of their properties can be modified by the community using DAO funcitonalities. Internally in the contract it serves the prorpuse of sharing state.
- code: [global.hpp](../../src/include/dex/modules/global.hpp)   

## Maintenance
Maintenance module is responsible for cleaning and pruning the tables as times goes by. All entries will be removed if they excede the expirate age limit. Also if any token gets blacklisted, all the markets in which it are involved will be blacklisted too, and the Maintenance module will clean them up, slowly.
- code: [maintenance.hpp](../../src/include/dex/modules/maintenance.hpp)   

## Market
Market module is responsible for the management of the markets, currencies and token groups. Mainly, it verifies if a new market can be created.
- read more about [Currencies and Token Groups](./Currencies.md).  
- read more about [Markets](./Markets.md).
- code: [market.hpp](../../src/include/dex/modules/market.hpp)

## Record
Record is a auxiliar module responsible for recording all events in different tables and sending events to other smart contracts.
- code: [record.hpp](../../src/include/dex/modules/record.hpp)

## Token
Token module is responsible for all token registrations and management of its data. Each token admin can register a token and manage its information to be shown on the DEX.
- code: [token.hpp](../../src/include/dex/modules/token.hpp)

## Client
Client Module is responsible for all User Interfaces registration as clients for the Telos DEX and its data auto management. Telos DEX can have multiple UI's and each of them must be registered as client in the contract.
- code: [client.hpp](../../src/include/dex/modules/client.hpp)

## Utils
Utils is a auxiliar module that provides many utility tools for sepeedy coding.
- code: [utils.hpp](../../src/include/dex/modules/utils.hpp)