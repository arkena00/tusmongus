#pragma once

#include <string>

namespace au
{
    struct ARK_SHARED player
    {

        std::string name() const;

        // rpc_server(set_color)
        void server_set_color(uint32_t hex_value);
    };
} // au