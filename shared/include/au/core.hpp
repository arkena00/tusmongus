#pragma once

#include <au/network.hpp>

#include <memory>

namespace ark { class core; }

namespace au
{
    class gamestate;
    class player;
    class mod;

    class core
    {
    public:
        core(ark::core& core);

        void load();

        void set_gamestate_class(au::mod&, std::unique_ptr<au::gamestate>);
        void set_player_class(au::mod&, std::unique_ptr<au::player>);

        ark::core& ark_core();

    private:
        ark::core& ark_core_;
        au::network network_;
        std::unique_ptr<au::gamestate> gamestate_;
        std::unique_ptr<au::player> player_;
    };
} // au