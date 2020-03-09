#include "./_aux.hpp"

        // TABLE whitelist -----------
        // scope: contract
        TABLE whitelist_table {
            uint64_t id;
            symbol_code symbol;
            name contract;
            name ballot;
            uint64_t primary_key() const { return id; }
            uint64_t by_symbol_key() const { return symbol.raw(); }
        };
        typedef eosio::multi_index< "whitelist"_n, whitelist_table,
            indexed_by<"symbol"_n, const_mem_fun<whitelist_table, uint64_t, &whitelist_table::by_symbol_key>>
        > whitelist;
        // ------------------------------------
