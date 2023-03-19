#include <au/mod.hpp>

#include <amodus/gamestate.hpp>
#include <amodus/player.hpp>

int mod_load(au::mod& mod)
{
    // logging
    mod.log("test message from mod");

    // mod info
    ark::mod_info info;
    info.name = "Amodus";
    info.description = "A mod with many roles";
    info.version = ark::version{ 0, 0, 8 };
    mod.set_info(std::move(info));

    // mod settings
    mod.add_setting("test_setting", 1);

    // use custom au api classes
    mod.register_class<amodus::gamestate>();
    mod.register_class<amodus::player>();

    // events
    // mod.on_enable([]{ mod.log("on_enable mod"); });
    // mod.on_disable([]{ mod.log("on_disable mod"); });


    // raw hook
    /*mod.register_hook<&au::PlayerControl::SetName>::before([this](auto&&, auto name)
    {
        // mod.log("test message from mod");
    });*/

    return 0;
}