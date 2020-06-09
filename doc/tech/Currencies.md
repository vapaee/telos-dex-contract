# Token Groups and Currencies.

[index](./README.md)

## market
Given two tokens, there are two posible markets: the canonical market (A/B) and the inverse market (B/A). But let's forget about inverse market and focus on the canonical as 'the market' for any tokens A & B.

Most of the time the users only need one market for each token X, and that is X/TLOS because we all (in the Telos community) recognize TLOS as currency. However, someone may end up needing to exchange A tokens for B tokens. Should it be allowed the creation of the arbitrary market A/B? will it be popular of will it split the liquidity?

The best solution to that problem was the definition of currency as such inside Telos DEX and only allow markets that has at least one currency token.

## currency
All tokens are in the same group, but not all are the same. There's one of them that we recognize as currency or money (TLOS), or maybe more that one but a very few. How about a stable dollar based token? How about an EOS pegged token? would those be considered (and used) as currencies? The answer to those question should be answered by the community voting as DAO using Telos Decide.

In order to keep liquidity concentrated in few markets, the number of currencies should be considerably low and the DAO solution is perfect to control it. However, there's a use case that we are not supporting and the Token Group is a great solution.

## token group
The token group is a concept created for those apps that work with many resources implemented as standard tokens and they also have their own currency. This solution allows those apps to have an inside-app exchange of their resources using their own currency and having Telos DEX handle all hard work.

For example, a strategy game can have several resources like *stone*, *wood*, *food* or *iron* and they may have two major currencies like *gold* and *silver*. The game publisher may register on Telos DEX, all the game resources as tokens and a new token group with the name of the game. Then add all the game resource-tokens to the token group and finally define *gold* and *silver* as currencies for that same group. After doing that, the game can implement an inside-game DEX for the game resources using *gold* and *silver* as currencies without splitting the liquidity of any other token on Telos DEX and without having the community to decide anything.

## token group zero
It exists a token group zero created in the initialization of the ocontract where TLOS is seted as currency from the start. Then all new tokens are added to this group by default when registered.

The currencies of the token group zero are added by the community voting as DAO. But the rest of the groups are privated and self managed by the admin.

So... given two tokens, is the market allowed to be created? the complete answer is that only if one of them belongs to a group in which the otherone is setted as currency.

- read more about [ACTION balloton setcurrency](./DAO.md#41).
- read more about [ACTION addtnkgroup](./API.md#171).
