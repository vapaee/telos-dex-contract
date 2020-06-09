# Telos DEX - API
This is an exhaustive list of all actions in the contract and a minor description of the parameters.   

[index](./README.md)

## DEPOSITS ACTIONS
The contracts cannot manipulate your tokens directly(*). Therefore, you need to transfer your tokens to the core contract and then use our money in the contract. In this case you need to deposit funds before creating any order.

### [withdraw](../../src/contracts/telosmaindex/telosmaindex.hpp#L117)   
The singning account (owner) withdraws own tokens from the Telos DEX contract.

    ACTION withdraw(name owner, const asset & quantity, uint64_t client)

|param|description|
|-----|-----------|
|owner|account name of the owner of this tokens|
|quantity|amount of tokens to withdraw from the contract (use the real token's precision) |
|client|user interface id used by the owner|

### [swapdeposit](../../src/contracts/telosmaindex/telosmaindex.hpp#L123) 
Once any registered token has been deposited into the DEX contract, it can be transferred to other users just like the real tokens. The only two differences are: the action name is not *transfer* but **swapdeposit**, and the second one is that the contract receiving the action (and performing the transfer) is not the tokens' contract but the Telos DEX contract. That means that all deposit swaps are made inside Telos DEX contract and must be withdrawn at some point.

    ACTION swapdeposit(name from, name to, const asset & quantity, string memo)

|param|description|
|-----|-----------|
|from|who's sending the tokens|
|to|who must receive it|
|quantity|how much of what tokens should be sent|
|memo|optional text that will bo no stored in ram|

### [deps2earn](../../src/contracts/telosmaindex/telosmaindex.hpp#L157)   
This is a **private action** which means only the contract itself can push. It transfers, from the Telos DEX contract to the UI receiver account, the number of tokes that quantity says.

    ACTION deps2earn(const uint64_t client, const asset & quantity)

|param|description|
|-----|-----------|
|client|id of client that will earn the tokens|
|quantity|how much of what tokens will be earn by the ui|


### [reward](../../src/contracts/telosmaindex/telosmaindex.hpp#L164)   
This is a **private action** which means only the contract itself can push. It rewards the a user with points and experience.

    ACTION reward(name user, const asset & points, const asset & exp)

|param|description|
|-----|-----------|
|user|user who is earning the rewards|
|points|amount of points to give this user temporarily|
|exp|amount of experience to give this user permanently|


------------------------
## EXCHANGE ACTIONS
In order to exchange tokens with other user, you must have some deposits in the contract. Then you can create and cancel buy and sell orders. If another user likes your offer, a deals is made and you trade your tokens at the exchange ratio you defined (known as price).

### [order](../../src/contracts/telosmaindex/telosmaindex.hpp#L109)  
This action is meant to be pushed by the users from a registered client. Anybody can buy or sell a total of any commodity token at a given price in any currency token.

    ACTION order(name owner, name type, const asset & total, const asset & price, uint64_t client)

|param|description|
|-----|-----------|
|owner|user creating an order|
|type|word 'buy' or 'sell' indicating the intention of the order|
|total|the total amount of commodity tokens offered or required|
|price|price of each commodity token expressed in any currency token|
|client|id of the user client by the owner|

### [cancel](../../src/contracts/telosmaindex/telosmaindex.hpp#L103)  
This actions is ment to be pushed by the users from a registered UI. Anybody can cancel any previously created order. If all the orders belong to the same market, they can be all included in the same orders' list to cancel.

    ACTION cancel(name owner, name type, const symbol_code & commodity, const symbol_code & currency, const std::vector<uint64_t> & orders)

|param|description|
|-----|-----------|
|owner|user canceling some orders|
|type|word 'buy' or 'sell' indicating what kind of order was|
|commodity|what was the commodity token involved|
|currency|what was the currency token involved|
|orders|list of ids of all the orders to be cancel|


------------------------
## TOKEN ACTIONS
Any standard token deployed on Telos blockchain can be registered in Telos DEX by its creator or issuer, becoming the token's admin inside Telos DEX. All tokens registered can have their own info-page and can be traded in Telos DEX unless they are blacklisted.

By default the TLOS token is settted as currency en the main token group (with id zero). More currencies can be added to the main token group but only by DAO functionalities (unig Telos Decide). All aother token groups ar private and can be managed by their admins/creators.

All the token activity can trigger events to be andeled aouside th DEX by another contract. This can be configured by the admins.

### [addtoken](../../src/contracts/telosmaindex/telosmaindex.hpp#L45)  
This action allows anyone token creator or issuer to register the token in Telos DEX.

    ACTION addtoken (name contract, const symbol_code & symbol, uint8_t precision, name admin, string title, string website, string brief, string banner, string icon, string iconlg, string pcontact, string gcontact, bool tradeable)

|param|description|
|-----|-----------|
|contract|name of the contract in which the token is deployed|
|symbol|symbol code of the contract (the name in caps next to the amount)|
|precision|how many digits must be used for fractions|
|admin|name of the admin of the token inside Telos DEX|
|title|the name of the token or the project behind the token|
|website|website url|
|brief|brief description of the token. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|icon|small square image url (from 16px to 32px)|
|iconlg|big square image url (from 64px 1o 512px)|
|pcontact|free text to indicate a wey of contact the person responsible for this token. A telegram Link is strongly recommended (https://t.me/person_xxxxxxxxxxxxxx)|
|gcontact|free text to indicate a wey of contact the community gruop where everybody participates in public way. A telegram group link is strongly recommended (https://t.me/group_xxxxxxxxxxxxxx)|
|tradeable|indicates if the token is allowed to be traded or it must be only listed just to be shown|

### [updatetoken](../../src/contracts/telosmaindex/telosmaindex.hpp#L53)  
All the token data of any registered token can be updated by the admin. This time the admin can change the default list of token groups this token is allowed to participate. The default is that all tokens can participate in market zero (0).

    ACTION updatetoken (const symbol_code & sym_code, string title, string website, string brief, string banner, string icon, string iconlg, string pcontact, string gcontact, vector<uint64_t> groups, bool tradeable)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token inside the Telos DEX|
|title|the name of the token or the project behind the token|
|website|website url|
|brief|brief description of the token. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|icon|small square image url (from 16px to 32px)|
|iconlg|big square image url (from 64px 1o 512px)|
|pcontact|free text to indicate a wey of contact the person responsible for this token. A telegram Link is strongly recommended (https://t.me/person_xxxxxxxxxxxxxx)|
|gcontact|free text to indicate a wey of contact the community gruop where everybody participates in public way. A telegram group link is strongly recommended (https://t.me/group_xxxxxxxxxxxxxx)|
|groups|list of token groups in which this token is allowed to participate. Default is [0]|
|tradeable|indicates if the token is allowed to be traded or it must be only listed just to be shown|


### [tokenadmin](../../src/contracts/telosmaindex/telosmaindex.hpp#L59)  
This action change the token admin.

    ACTION tokenadmin (const symbol_code & sym_code, name admin)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token|
|admin|new admin account name|


### [setcurrency](../../src/contracts/telosmaindex/telosmaindex.hpp#L65)  
This is a **private action** which means only the contract itself can push. It sets a token as a currency for the token group zero. The token group zero is the only one that needs DAO approval, currencies in other token groups are managed by the token group admin alone.

    ACTION setcurrency (const symbol_code & sym_code, bool is_currency)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token|
|is_currency|boolean indicating if the token should be set as currency or removed from being one|
|token_group|id of the token group in which this token should be added or removed as currency|


### [settokendata](../../src/contracts/telosmaindex/telosmaindex.hpp#L71)  
Each token registered in Telos DEX can have its own list of extra data that can be used to enrich the token's page.  

    ACTION settokendata (const symbol_code & sym_code, uint64_t id, name action, name category, string text, string link)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token|
|id|id of the entry in the table of tokendata|
|action|the word 'add', 'remove' or 'update' can be used to specify what kind of action must be performed|
|text|texto to show|
|link|link to use|
|shownas|a word describing how to use the link when shown ('youtube', 'twitter', 'link', 'image')|


### [edittkevent](../../src/contracts/telosmaindex/telosmaindex.hpp#L77)  
Each token registered in Telos DEX can trigger events for other contracts to react when some operations occur inside Telos DEX. The token admin can register a list of events (that wants to react to) and for each, an account name in which a contract should implement a handler for the event.

    ACTION edittkevent (const symbol_code & sym_code, name event, name action, name contract)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token|
|event|a word inentifying the internal event to react to (withdraw, deposit, swapdeposit, order, cancel, deal)|
|action|the word 'add', 'remove' or 'update' can be used to specify what kind of action must be performed|
|contract|account name of the contract that will handles the event|


### [addtnkgroup](../../src/contracts/telosmaindex/telosmaindex.hpp#L83)  
Anyone can create a token group but only the token admins can add or remove their tokens from a token group. This action allows anyone to create a group and set the list of currencies for this group (the currencies must be added to the group by their admins).

    ACTION addtnkgroup (name admin, string title, string website, string brief, string banner, string thumbnail, vector<symbol_code> currencies)

|param|description|
|-----|-----------|
|admin|account name of the admin|
|title|title for the token group|
|website|website url|
|brief|brief description of the token group. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|thumbnail|small rectangular thumbnail image url|


### [uptnkgroup](../../src/contracts/telosmaindex/telosmaindex.hpp#L89)  
Thia action allows to update the token group data.

    ACTION uptnkgroup (uint64_t group_id, name admin, string title, string website, string brief, string banner, string thumbnail)

|param|description|
|-----|-----------|
|group_id|id of the group|
|admin|account name of the admin|
|title|title for the token group|
|website|website url|
|brief|brief description of the token group. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|thumbnail|small rectangular thumbnail image url|



### [chnggroups](../../src/contracts/telosmaindex/telosmaindex.hpp#L95)  
Thia action allows to update the token group data.

    ACTION chnggroups (const symbol_code & sym_code, vector<uint64_t> groups)

|param|description|
|-----|-----------|
|sym_code|symbol code that identifies the token|
|groups|list of token groups in which this token is allowed to participate. Default is [0]|


------------------------
## CLIENT ACTIONS
Telos DEX can have multiple clients and user interfaces. Anyone that imlpements a client should register it in the DEX and start earning fees from all the its users.

### [addclient](../../src/contracts/telosmaindex/telosmaindex.hpp#L31)  
Register a new client for the DEX.

    ACTION addclient (name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail)

|param|description|
|-----|-----------|
|admin|account name of the client's admin|
|receiver|account name of the account to transfer all fees earned|
|params|string to include in the memo of the transfer (for handling)|
|title|name of the client|
|website|website url|
|brief|brief description of the user interface. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|thumbnail|small rectangular thumbnail image url|


### [updateclient](../../src/contracts/telosmaindex/telosmaindex.hpp#L37)  
Update client data.

    ACTION updateclient (uint64_t client, name admin, name receiver, string params, string title, string website, string brief, string banner, string thumbnail)

|param|description|
|-----|-----------|
|client|client id|
|admin|account name of the client's admin|
|receiver|account name of the account to transfer all fees earned|
|params|string to include in the memo of the transfer (for handling)|
|title|name of the client|
|website|website url|
|brief|brief description of the user interface. Some markdown and basic HTML can be used for rich-text|
|banner|very wide header banner image url|
|thumbnail|small rectangular thumbnail image url|


------------------------
## DAO ACTIONS
Many of the configuration values of Telos DEX can be adjusted by DAO functionalities using Telos Decide. Who ever initiates a ballot to make a change on the sistem sould must pay the Telos Decide fees for creating a ballot. Those fees will be taken from the user's deposits and not from the user liquid balance.

### [balloton](../../src/contracts/telosmaindex/telosmaindex.hpp#L190)  
Creates a query on Telos Decide about whether or not to perform one of the possible operations configured by the parameter list.

    ACTION balloton (name operation, vector<string> params, string arguments, name feepayer)

|param|description|
|-----|-----------|
|operation|a word identifying on of the many operation to perform (bantoken, savetoken, makerfee, takerfee, setcurrency, historyprune, hblockprune, eventsprune, pointsprune, ballotsprune, approvalmin, regcost)|
|params|list of strings contaigning where each of them is parseable and a specific typed value can be extracted (like assets or symbol_codes)|
|arguments|A string agruing about the need or reason for this ballot.|
|feepayer|account name of the Telos Decide fees for creating a ballot|

------------------------
## GLOBAL ACTIONS

### [init](../../src/contracts/telosmaindex/telosmaindex.hpp#L180)  
Executed just once to initialize the contract state. It creates the main token group registering TLOS token and setting it as currency for this token group zero.

    ACTION init ()

### [maintenance](../../src/contracts/telosmaindex/telosmaindex.hpp#L172)  
This action can be executed by anyone and should never fail. It performes a maintenance task to prune expired entries from history logs and clean up markets data for blacklisted tokens.

    ACTION maintenance (name credits_to)

|param|description|
|-----|-----------|
|credits_to|name of the user to reward in recognition for the maintenance help|

------------------------
## HANDLERS
Telos DEX reacts to transfers and ballots on the Telos Decide system and the handlers solve part of the interaction.

### [htransfer](../../src/contracts/telosmaindex/telosmaindex.hpp#L130)  
This handles de transfer event to register a deposit from a user.

    HANDLER htransfer(name from, name to, asset quantity, string  memo )

### [hbroadcast](../../src/contracts/telosmaindex/telosmaindex.hpp#L197)  
This handles the ending of a ballot in Telos Decide created by Telos DEX for DAO capabilities.

    HANDLER hbroadcast(name ballot_name, map<name, asset> final_results, uint32_t total_voters) 

------------------------
## DEBUG ACTIONS
Debugging and development action tools

### hotfix

    ACTION hotfix (int max, name scope, asset q)

### testdao

    ACTION testdao (name ballot_name, map<name, asset> final_results, uint32_t total_voters)

### timeoffset

    ACTION timeoffset (uint32_t offset)




------------------------
(*) There's an exception to that and that occurs when the token is implemented in the same contract,