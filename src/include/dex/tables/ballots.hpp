#include "./_aux.hpp"

        
        // ------------------------------------
        // TABLE ballots
        // scope: contract
        TABLE ballots_table {
            name ballot_name;
            name property;
            vector<string> params;
            name feepayer;
            time_point_sec date;
            uint64_t primary_key() const { return ballot_name.value; }
            uint64_t by_property_key() const { return property.value; }
        };

        typedef eosio::multi_index< "ballots"_n, ballots_table,
            indexed_by<"property"_n, const_mem_fun<ballots_table, uint64_t, &ballots_table::by_property_key>>
        > ballots;
        // ------------------------------------
        