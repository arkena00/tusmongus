#pragma once

#include <au/player.hpp>
#include <vector>

namespace au
{
    class core;
    class mod;

    class ARK_SHARED gamestate
    {
    public:
        virtual void on_start_meeting(au::player& reporter/*, au::playerstate& target*/);

        au::mod& mod();
        const std::vector<au::player>& players();
    };
} // auv