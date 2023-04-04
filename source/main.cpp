#include <au/mod.hpp>

#include <ark/hook.hpp>
#include <gen/au/PlayerControl.hpp>
#include <gen/au/PlayerTask.hpp>
#include <gen/au/Console.hpp>
#include <gen/au/MiniGame.hpp>
#include <gen/au/EndGameManager.hpp>

#include <au/ShipStatus.hpp>
#include <tmg/tusmo.hpp>
#include <tmg/ui.hpp>

// stop player when start task during moving
// block input while tusmo
// task stay visible after complete

int mod_load(au::mod& mod)
{
    // logging
    mod.log("test message from mod");

    // mod info
    ark::mod_info info;
    info.name = "Tusmongus";
    info.description = "Tasks are replaced by tusmo game";
    info.version = ark::version{ 0, 3, 0 };
    mod.set_info(std::move(info));

    // mod settings

    // events
    // mod.on_enable([&mod]{ mod.log("on_enable mod"); });
    // mod.on_disable([]{ mod.log("on_disable mod"); });

    static tmg::tusmo tusmo{ mod };
    static bool task_complete = false;


    mod.on_draw([](auto* imgui_context) {
                if (tusmo.active())
                {
                    tmg::draw_ui(imgui_context, tusmo);

                    if (tusmo.ended())
                    {
                        if (tusmo.won())
                        {
                            // notify game thread
                            task_complete = true;
                        }
                    }
                }
            });

    // drawing renders in another thread, wait events here to run au function from the same thread
    ark::hook<&au::PlayerControl::FixedUpdate>::after([](auto&& self) {
        if (task_complete)
        {
            ark_trace("task complete {}", tusmo.task()->Idk__BackingField);
            au::PlayerControl::LocalPlayer()->RpcCompleteTask(tusmo.task()->Idk__BackingField);
            au::PlayerControl::LocalPlayer()->CompleteTask(tusmo.task()->Idk__BackingField);
            task_complete = false;
        }
    });

    ark::hook<&au::Console::Use>::overwrite([&mod](auto&& original, auto&& self) {
            bool can_use, shoud_use;
            self->CanUse(au::PlayerControl::LocalPlayer()->get_Data(), can_use, shoud_use);
            ark_trace("can_use {} shoud_use {}", can_use, shoud_use);
            if (!can_use) return original(self);

            auto* task = self->FindTask(au::PlayerControl::LocalPlayer());
            if (task
                && task->TaskType != au::TaskTypes::FixComms
                && task->TaskType != au::TaskTypes::FixLights
                && task->TaskType != au::TaskTypes::ResetReactor
                && task->TaskType != au::TaskTypes::ResetSeismic)
            {
                ark_trace("begin task {}", task->Idk__BackingField);
                tusmo.begin(task);
            }
            else original(self);
        });

    // stop move during the tusmo
    ark::hook<&au::PlayerControl::get_CanMove>::overwrite([&mod](auto&& original, auto&& self) -> bool {
            if (tusmo.active()) return false;
            else return original(self);
        });

    // close tusmo events
    ark::hook<&au::ShipStatus::StartMeeting>::after([](auto&& self, auto, auto) {
        tusmo.end();
    });
    ark::hook<&au::PlayerControl::Die>::after([](auto&& self, auto, auto) {
        if (au::PlayerControl::LocalPlayer() == self) tusmo.end();
    });

    ark::hook<&au::EndGameManager::Start>::after([](auto&& self) {
        tusmo.end();
    });


    return 0;
}