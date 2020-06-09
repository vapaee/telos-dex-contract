# Telos DEX - Tables
This is an exhaustive list of all tables in the contract and a minor description of the fields.

[index](./README.md)


## [ballots](../../src/include/dex/tables/ballots.hpp)   
- **description:** all ballots created from Telos DEX are stored in this table with the finished field set in Infinity. When the ballot is solved in Teos Decide the corresponding entry in this table is updated with the results and finished is updated with the current date.   
- **scope:** DEX smart contract name   
- **id:** auto-generated   

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|ballot_name|name|foreign key of the ballot created in Telos Decide tables|
|operation|name|a word identifying one of the many operations that can be performed a ballot on (bantoken, savetoken, makerfee, takerfee, setcurrency, historyprune, hblockprune, eventsprune, pointsprune, ballotsprune, approvalmin, regcost)|
|params|vector<string>|list of strings contaigning where each of them is parseable and a specific typed value can be extracted (like assets or symbol_codes)|
|feepayer|name|account name of the user to be charged for the Telos Decide fees|
|started|time_point_sec|date of creation|
|finished|time_point_sec|date of results|
|arguments|string|optional string to explain the reason for this ballot|
|approved|bool|was it approved after finished|
|results|map<name, asset>|results mapping of votes after finished|


## [blacklist](../../src/include/dex/tables/blacklist.hpp)   
- **description:** A token can be found fraudulent or scam so the community can put this token in a blacklist an prevent any operation with this token.   
- **scope:** DEX smart contract name   
- **id:** auto-generated   

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|symbol|symbol_code|symbol of the token|
|precision|uint8_t|symbol of the token|
|contract|name|symbol of the token|
|ballot|name|ballot id in which this token was blacklisted|


## [clients](../../src/include/dex/tables/clients.hpp)   
- **description:** This table holds the registered clients for Telos DEX.     
- **scope:** DEX smart contract name     
- **id:** auto-generated    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|admin|name|account name of the client admin|
|receiver|name|account name to transfer the fees from deals|
|params|string|string to be included in the transfer's memo|
|title|string|name of the client|
|website|string|website url|
|brief|string|brief description of the client. Some markdown and basic HTML can be used for rich-text|
|banner|string|very wide header banner image url|
|thumbnail|string|small rectangular thumbnail image url|
|date|time_point_sec|date of the last update|


## [delmarkets](../../src/include/dex/tables/delmarkets.hpp)   
- **description:** if a token is blacklisted, all the market activity from any market in which this token was involved must be deleted. This is can be a huge task and that's why it's performed slowly by the maintenance process. This table helps in this process of cleaning up those tables.   
- **scope:** DEX smart contract name    
- **id:** copied from market table   

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the market that must be cleaned up|
|table|name|label for the table|


## [deposits](../../src/include/dex/tables/deposits.hpp)   
- **description:** This table holds the current deposit balances for any user.    
- **scope:** owner account name   
- **id:** symbol code of the amount   

|field|type|description|
|-----|----|-----------|
|amount|asset|balance of the user in this token|


## [depusers](../../src/include/dex/tables/depusers.hpp)   
- **description:** this table is a simple list of all users that has any deposits into this DEX     
- **scope:** DEX smart contract name     
- **id:** owner account name   

|field|type|description|
|-----|----|-----------|
|account|name|account name that has at least un deposit|


## [events](../../src/include/dex/tables/events.hpp)   
- **description:** This is an exhaustive list of all events inside the DEX. This table is pruned by the maintenance proccess and the expiration window time can be adjusted by DAO functionalities.       
- **scope:** DEX smart contract name    
- **id:** auto-generated    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|user|name|useer who generates the event|
|event|name|descrives what happened|
|params|string|a pipe-separated string '\|' containing extra data of the event|
|date|time_point_sec|date of the event|


## [exp](../../src/include/dex/tables/exp.hpp)   
- **description:** List of all users and theirs EXP (experience points). This EXP are permanent for the user and not transferibles.       
- **scope:** DEX smart contract name    
- **id:** owner name    

|field|type|description|
|-----|----|-----------|
|owner|name|user name|
|exp|asset|balance of the EXP units|


## [history](../../src/include/dex/tables/history.hpp)   
- **description:** Each token pair defines two markets, the canonical and the inverse. But both markets share history in this table, using the canonical market id as the scope.    
- **scope:** canonical market-id    
- **id:** auto-generated    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|date|time_point_sec|date of the deal|
|buyer|name|account name of the buyer|
|seller|name|account name of the seller|
|price|asset|currency-token expressing the price|
|inverse|asset|commodity-token expressing the inverse of the price|
|amount|asset|commodity-token expressing the amount of commodity offering|
|payment|asset|currency-token expressing the total of currency to pay for this amount at this price|
|buyfee|asset|currency-token expressing the fees to charge the buyer|
|sellfee|asset|commodity-token expressing the fees to charge the seller|
|isbuy|bool|indicates if it was a buy-order or a sell-order that triggers the deal|


## [historyall](../../src/include/dex/tables/historyall.hpp)   
- **description:** this table mixes all history tables in one, only to have a way of sorting them all by date. This is a helpper table for the maintenance proccess which prunes too old history entries. The expiration time can be adjusted by DAO functionalities     
- **scope:** DEX smart contract name    
- **id:** auto-generated   

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|key|uint64_t|foreign key of the real entry in the market's history table|
|market|uint64_t|canonical market id to use as scope for the histroy table|
|date|time_point_sec|date of the deal indexed to sort by this field|


## [historyblock](../../src/include/dex/tables/historyblock.hpp)   
- **description:** this table summarizes the all deals in one hour for a canonical market id. Thi is a one-hour-block sumary of the history table. It also get prued by the maintenance proccess.    
- **scope:** canonical market-id     
- **id:** auto-generated      

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|hour|uint64_t|number of hours since epoch which identifies the block|
|price|asset|currency-token expressing current or last price|
|inverse|asset|commodity-token expressing the inverse of the price|
|entrance|asset|currency-token expressing the first price of the block|
|max|asset|currency-token expressing the max price reached|
|min|asset|currency-token expressing the min price reached|
|volume|asset|currency-token expressing the total volume traded|
|amount|asset|commodity-token expressing the total amount traded|
|date|time_point_sec|date of the last update of the block|


## [last24hs](../../src/include/dex/tables/last24hs.hpp)   
- **description:** this table is similar to hitosyblock but is meant to hold just the las 24hs information (25 entries max, 24 per each hour and one for lastone)    
- **scope:** canonical market-id     
- **id:** label    

|field|type|description|
|-----|----|-----------|
|label|name|id of the entry, "lastone", "h.zero", "h.one", ..., "h.twentythree"|
|price|asset|currency-token expressing current or last price|
|inverse|asset|commodity-token expressing the inverse of the price|
|entrance|asset|currency-token expressing the first price of the block|
|max|asset|currency-token expressing the max price reached|
|min|asset|currency-token expressing the min price reached|
|volume|asset|currency-token expressing the total volume traded|
|amount|asset|commodity-token expressing the total amount traded|
|hour|uint64_t|number of hours since epoch which identifies the block|
|date|time_point_sec|date of the last update of the block|


## [markets](../../src/include/dex/tables/markets.hpp)   
- **description:** Given two tokens we have two markets: the canonical and the inverse. These two markets are always registered together in such a way that the canonical always is the lower pair number (therefore the inverse is the canonical+1).      
- **scope:** DEX smart contract name     
- **id:** auto-generated     

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|table|name|label for the market|
|commodity|symbol_code|token as commodity|
|currency|symbol_code|token as currency|


## [ordersummary](../../src/include/dex/tables/ordersummary.hpp)   
- **description:** this table sumarizes many agregated numbers such as total of deals and not pending orders (supply and demand). This information is only available for the canonical market id because de inverse share info.    
- **scope:** DEX smart contract name     
- **id:** foreign key of markets table     

|field|type|description|
|-----|----|-----------|
|market|uint64_t|id of the cacnonical market|
|sell|symbol_code|symbol code of the commodity-token|
|pay|symbol_code|symbol code of the currency-token|
|supply.total|asset|commodity-token expressing the total supply|
|supply.orders|int|amount of sell orders|
|supply.ascurrency|int|amount of time deals have been fulfilled using commodity-token as currency|
|demand.total|asset|currency-token expressing the total demand|
|demand.orders|int|amount of buy orders|
|demand.ascurrency|int|amount of time deals have been fulfilled using currency-token as currency|
|deals|int|total amount of deals (should be the same as the last history entry id)|
|blocks|int|amounts of history blocks created|


## [points](../../src/include/dex/tables/points.hpp)   
- **description:** List of all users and theirs points. The POINTS are not permanent, they are only remembered 'pprune' weeks, number that can be changed by votting like a DAO on the operation 'pointsprune'
- **scope:** DEX smart contract name    
- **id:** owner name    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|week|uint32_t|weeks since epoch, identifies the week|
|owner|name|user name|
|points|asset|balance of the POINTS units|


## [sellorders](../../src/include/dex/tables/sellorders.hpp)   
- **description:** This table holds the sell-orders for the given market id (as scope). It turns out that the buy-orders of the canonical market id is the the ones in the sellorders table for the inverse market id (as scope) and vise versa.    
- **scope:** market-id      
- **id:** auto-generated     

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|client|uint64_t|client id used to create this order (will earn the deal fees)|
|owner|name|user creating the order|
|price|asset|currency-token expressing the price|
|inverse|asset|commodity-token expressing the inverse of the price|
|selling|asset|commodity-token expressing the amount of commodity offering|
|total|asset|currency-token expressing the total of currency to pay for this amount at this price|


## [state](../../src/include/dex/tables/state.hpp)   
- **description:** This is a singleton table to hold the state for the Telos DEX. Most of the state properties can be modified by DAO functionalities    
- **scope:** DEX smart contract name    
- **id:** Unique entry (singleton)    

|field|type|description|
|-----|----|-----------|
|maker_fee|asset|the fee to charge the market maker (pending orders)|
|taker_fee|asset|the fee to charge the market taker (orders that fulfill immediately)|
|hprune|int|amount of days in which a HISTORY entry must be considered expired and must be removed |
|kprune|int|amount of days in which a HISTORY BLOCK entry must be considered expired and must be removed |
|bprune|int|amount of maximun finished BALLOT entries allowed|
|eprune|int|amount of days in which a EVENT entry must be considered expired and must be removed |
|pprune|int|amount of weeks in which a POINTS entry must be considered expired and must be removed |
|approvalmin|asset|minimum participation percent for ballot approval|
|regcost|asset|token registration cost (in TLOS)|
|next_market|uint64_t|id of the next market|


## [tokendata](../../src/include/dex/tables/tokendata.hpp)   
- **description:** each token can have extra data entries and this table holds those entries.    
- **scope:** symbol code of the related token    
- **id:** auto-generated    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|text|string|string with a text to show|
|link|string|a link to a resource|
|shownas|name|indicates how to use the link to display the resource|
|date|time_point_sec|date of last update|


## [tokenevents](../../src/include/dex/tables/tokenevents.hpp)   
- **description:** Each registered token can have a list of events configured to trigger an inline action to the destination registered for each event. This table holds all the events to which Telos DEX should generate an inline action.   
- **scope:** symbol code of the related token       
- **id:** event name    

|field|type|description|
|-----|----|-----------|
|event|name|event name|
|receptor|name|account name of the event receiver|


## [tokengroups](../../src/include/dex/tables/tokengroups.hpp)   
- **description:** table holding the token groups registered in Telos DEX.    
- **scope:** DEX smart contract name    
- **id:** auto-generated    

|field|type|description|
|-----|----|-----------|
|id|uint64_t|id of the entry|
|admin|name|account name of the admin of the token group|
|title|string|name of the group|
|website|string|website url|
|brief|string|brief description of the group. Some markdown and basic HTML can be used for rich-text|
|banner|string|very wide header banner image url|
|thumbnail|string|small rectangular thumbnail image url|
|currencies|vector<symbol_code>|list of currencies for this group|

## [tokens](../../src/include/dex/tables/tokens.hpp)   
- **description:** table holding all registered tokens in Telos DEX.    
- **scope:** DEX smart contract name    
- **id:** symbol code of the related token    

|field|type|description|
|-----|----|-----------|
|symbol|symbol_code|symbol code of the token|
|groups|vector<uint64_t>|list of token groups in which this token is allowed to participate. Default is [0]|
|precision|uint8_t|token precision|
|contract|name|account name of the token's contract|
|admin|name|account name of admin of the contract|
|title|string|the name of the token or the project behind the token|
|website|string|website url|
|brief|string|brief description of the token. Some markdown and basic HTML can be used for rich-text|
|banner|string|very wide header banner image url|
|icon|string|small square image url (from 16px to 32px)|
|iconlg|string|big square image url (from 64px 1o 512px)|
|pcontact|string|free text to indicate a wey of contact the person responsible for this token. A telegram Link is strongly recommended (https://t.me/person_xxxxxxxxxxxxxx)|
|gcontact|string|free text to indicate a wey of contact the community gruop where everybody participates in public way. A telegram group link is strongly recommended (https://t.me/group_xxxxxxxxxxxxxx)|
|date|time_point_sec|date of the last update|
|data|uint32_t|amount of etra data in tokendata table|
|tradeable|bool|boolean idicating if the admin allows this token to be traded in Telos DEX|
|currency|bool|boolean idicating if this token is seted as currency on the token group zero|

## [userorders](../../src/include/dex/tables/userorders.hpp)   
- **description:** this table maitains a list of sell orders' id for each market in which the user has any order. This is a helpper table to locate the user orders fery fast.    
- **scope:** user account name    
- **id:** foreign key of markets table    

|field|type|description|
|-----|----|-----------|
|market|uint64_t|id of the entry, foreign key of markets table|
|table|string|label of the table|
|ids|vector<uint64_t>|list of foreign keys of order for that market|

## [whitelist](../../src/include/dex/tables/whitelist.hpp)   
- **description:** this table holds a list of whitelisted tokens in Telos DEX. a token can be added or remover from this list by DAO functionalities        
- **scope:** DEX smart contract name    
- **id:** symbol code of the related token   

|field|type|description|
|-----|----|-----------|
|symbol|symbol_code|symbol code of the whitelisted token|
|contract|name|contract name of the token|
|ballot|name|ballon id in which this token was saved|

