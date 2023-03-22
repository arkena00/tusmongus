#pragma once

#include <au/player.hpp>
#include <vector>

namespace au
{
    class core;
    class mod;
    struct PlayerControl;
    struct GameManager;

    class ARK_SHARED gamestate
    {
    public:
        gamestate();
        gamestate(const gamestate&) = delete;
        gamestate& operator=(const gamestate&) = delete;

        virtual void on_begin_play() {}
        virtual void on_die(au::player& player, au::DeathReason reason, bool assignGhostRole) {}
        virtual void on_cast_vote(uint8_t playerId, uint8_t suspectIdx) {}
        virtual void on_start_meeting(au::player& reporter, au::player* target) {}
        virtual void on_check_end(au::player& reporter, au::player& target) {}

        void add_player(std::unique_ptr<au::player>);
        void end_game(int reason);

        au::mod& mod();
        au::player* player(au::PlayerControl*);
        const std::vector<std::unique_ptr<au::player>>& players();

    private:
        friend class core;

        au::mod* mod_ = nullptr;
        au::GameManager* au_game_manager_ = nullptr;
        std::vector<std::unique_ptr<au::player>> players_;
    };
} // au