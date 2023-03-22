#pragma once

#include <string>

namespace au
{
    enum class DeathReason : int32_t
    {
        Exile
        , Kill
        , Disconnect
    };
} // au

#pragma once



namespace au
{
    class PlayerControl;
    class mod;
    class gamestate;

    class ARK_SHARED player
    {
    public:
        player();

        virtual void on_die(au::DeathReason reason, bool assignGhostRole) {}

        au::mod& mod();
        au::gamestate& gamestate();

        std::string name() const;

        static au::player& local();

    private:
        static std::unique_ptr<au::player> local_player;

        au::PlayerControl* au_player_ = nullptr;
        au::mod* mod_ = nullptr;

        friend class core;
    };
} // au