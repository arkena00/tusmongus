#pragma once

#include <au/gamestate.hpp>

#define SERVER(Name, ReturnType, __VA_ARGS__) \
int server_##Name##_init = [this]{ mod().register_rpc(&gamestate::server_##Name##_impl_s, this); return 0; }(); \
template<class... Ts> void server_dothing(Ts&&... ts ) { server_dothing(this, ts...); }                         \
static void server_##Name(gamestate* p, int value) \
{ \
    void* v = reinterpret_cast<void*>(&gamestate::server_##Name##_impl_s); \
    /*p->mod().send_rpc(&gamestate::server_dothing_impl, value);*/ \
}

namespace amodus
{
    class gamestate : public au::gamestate
    {
    public:
        std::vector<std::function<void(ark::mod&)>> rpcs_;

        //int server_dothing_init = [this]{ rpcs_.emplace_back([this](auto& mod){ /*mod.register_rpc(&gamestate::server_dothing_impl_s, this);*/ }); return 0; }();


        void on_begin_play() override
        {
            //mod().log("gamestate::beginplay");
            //server_dothing(0);
        }

        //int server_dothing_init = [this]{ mod().register_rpc(&gamestate::server_dothing_impl_s, this); return 0; }();
        gamestate() = default;
        gamestate(au::mod& mod) : au::gamestate(mod) {}// { mod.log("ctor"); mod.register_rpc(&gamestate::server_dothing_impl_s, this); }
        void server_dothing(int value)
        {
            std::vector<std::byte> data;
            // serialize input // std::make_tuple<> // std::apply()
            mod().send_rpc(&gamestate::server_dothing_impl_s, this, data);
        }

        // SERVER(void, dothing, int, value)        {    mod().log("server_dothing_impl");    }
        static void server_dothing_impl_s(gamestate* p, const std::vector<std::byte>& data)
        {
            // auto params = deserialize<std::tuple<a, b, c>>(data)
            // std::apply(f, params);
            p->server_dothing_impl(0);
        }
        void server_dothing_impl(int value)
        {
            mod().log("server_dothing_impl");
        }

        void on_cast_vote(uint8_t playerId, uint8_t suspectIdx) override
        {
            mod().log("on_cast_vote {} voting {}", playerId, suspectIdx);
        }

        void on_die(au::player& player, au::DeathReason reason, bool assignGhostRole) override
        {
            check_wincondition();
        }

        void on_start_meeting(au::player& reporter, au::player* target) override
        {
            mod().log("amodus start meeting");

            for (const auto& player: players())
            {
                mod().log("player {}", player->name());
            }
        }

        void check_wincondition()
        {
            std::vector<au::player*> winners;
            for (const auto& player: players())
            {
                //if (player.has_win()) winners.emplace_back(player.get());
            }
        }

    private:
        //amodus::core& core_;
    };
} // auv