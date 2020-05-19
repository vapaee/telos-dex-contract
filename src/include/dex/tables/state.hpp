#include "./_aux.hpp"

        // scope: singleton
        TABLE state {
            asset maker_fee;
            asset taker_fee;
            int hprune; // amount of days in which a HISTORY entry must be considered expired and must be removed 
            int bprune; // amount of maximun finished BALLOT entries allowed.
            int eprune; // amount of days in which a EVNET entry must be considered expired and must be removed 
            asset regcost; // token registration cost (in TLOS)
            uint64_t next_market; // id of the next market
            AUX_DEBUG_CODE(uint32_t time_offset;)
        };
        typedef singleton<name("state"), state> global_state_singleton;
