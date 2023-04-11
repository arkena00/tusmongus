#include <tmg/mod.hpp>

#include <ark/hook.hpp>
#include <gen/au/PlayerControl.hpp>
#include <gen/au/PlayerTask.hpp>
#include <gen/au/Console.hpp>
#include <gen/au/MiniGame.hpp>
#include <gen/au/EndGameManager.hpp>
#include <gen/au/PlayerPhysics.hpp>
#include <gen/au/AmongUsClient.hpp>
#include <gen/au/AbilityButton.hpp>

#include <au/ShipStatus.hpp>
#include <tmg/tusmo.hpp>
#include <tmg/ui.hpp>
#include <tmg/font.hpp>

#include <imgui_internal.h>

static bool task_complete = false;

namespace tmg
{
    mod::mod(ark::mod_api& api)
        : au::mod(api)
        , tusmo_{ *this }
    {
        ark::mod_info info;
        info.name = "Tusmongus";
        info.description = "Tasks are replaced by tusmo game";
        info.version = ark::version{ 0, 3, 5 };
        info.authors.emplace_back("Arkena", "https://github.com/arkena00");
        info.authors.emplace_back("nico5br", "https://www.twitch.tv/nico5br");
        set_info(std::move(info));

        add_setting("word.max_size", 4, "Choose the max letters for a word");

        hook();

        // create font
        tusmo_.font = ui_context()->IO.Fonts->AddFontFromMemoryCompressedTTF(font_compressed_data, font_compressed_size, 36);
        //tusmo_.word_size = setting<int>("word.max_size");
    }

    void mod::on_draw()
    {
        if (tusmo_.active())
        {
            tmg::draw_ui(ui_context(), tusmo_);

            if (tusmo_.ended())
            {
                if (tusmo_.won())
                {
                    // notify game thread
                    task_complete = true;
                }
            }
        }
    }

    void mod::on_enable() {}

    void mod::hook()
    {
        // drawing renders in another thread, wait events here to run au function from the same thread
        ark::hook<&au::PlayerControl::FixedUpdate>::after([this](auto&& self) {
            if (task_complete)
            {
                au::PlayerControl::LocalPlayer()->RpcCompleteTask(tusmo_.task()->Idk__BackingField);
                au::PlayerControl::LocalPlayer()->CompleteTask(tusmo_.task()->Idk__BackingField);
                task_complete = false;
            }
        });

        ark::hook<&au::Console::Use>::overwrite([this](auto&& original, auto&& self) {
                bool can_use, shoud_use;
                self->CanUse(au::PlayerControl::LocalPlayer()->get_Data(), can_use, shoud_use);
                if (!can_use) return original(self);

                auto* task = self->FindTask(au::PlayerControl::LocalPlayer());
                if (task
                    && task->TaskType != au::TaskTypes::FixComms
                    && task->TaskType != au::TaskTypes::FixLights
                    && task->TaskType != au::TaskTypes::ResetReactor
                    && task->TaskType != au::TaskTypes::ResetSeismic)
                {
                    // stop player movement
                    au::PlayerControl::LocalPlayer()->MyPhysics->SetNormalizedVelocity({});
                    tusmo_.begin(task);
                }
                else original(self);
            });

        // stop move during the tusmo
        ark::hook<&au::PlayerControl::get_CanMove>::overwrite([this](auto&& original, auto&& self) -> bool {
                if (tusmo_.active()) return false;
                else return original(self);
            });

        // close tusmo events
        ark::hook<&au::ShipStatus::StartMeeting>::after([this](auto&& self, auto, auto) {
            tusmo_.end();
        });
        ark::hook<&au::PlayerControl::Die>::after([this](auto&& self, auto, auto) {
            if (au::PlayerControl::LocalPlayer() == self) tusmo_.end();
        });
        ark::hook<&au::EndGameManager::Start>::after([this](auto&& self) {
            tusmo_.end();
        });
        ark::hook<&au::AmongUsClient::ExitGame>::after([this](auto&& self, auto) {
            tusmo_.end();
        });

        ark::hook<&au::AbilityButton::DoClick>::overwrite([this](auto&& original, auto&& self) {
            if (!tusmo_.active()) original(self);
        });
    }
} // tmg