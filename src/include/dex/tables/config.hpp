#include "./_aux.hpp"

        // scope: singleton
        TABLE config {
            double maker_fee;
            double taker_fee;
            time_point_sec prune;
        };
        typedef singleton<name("config"), config> config_singleton;