# Telos DEX Markets

[index](./README.md)

## canonical & inverse markets
Given two tokens, there are two posible markets: the canonical market (A/B) and the inverse market (B/A).

In the canonical market the commodity token A is being traded paying with currency token B. In the inverse market is the oposite situation, where you have B being traded paying with A.

The curiosity here is that the sell orders for market A/B is the exact inverse of the buy orders for market B/A, therefore, they share history and liquidity. This is why Telos DEX only keeps trak of the canonical market history.

## market creation
Not all markets are created at once when a new token is registered. They are not created until some user push an order on a new market. But, can any market be created?

While having a lot of token pairs combinations (or markets) seems to be a good idea, it can split too much liquidity. We always will prefer a small number of markets will big numbers of liquidity than vice versa. That is why the decision of adding a new currency to Telos DEX is taked by the community by voting as DAO using Telos Decide. Each new currency means a potencial new market for each token already registered.

- read more about [Currencies and Token Groups](./Currencies.md).
