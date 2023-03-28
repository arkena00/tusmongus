#include <au/mod.hpp>

#include <amodus/gamestate.hpp>
#include <amodus/player.hpp>

#include <gen/au/PlayerControl.hpp>

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

    // raw hook // mod.hook_before<>

    /*ark::hook<&au::PlayerControl::Exiled>::before([&mod](auto&&...)
    {
        mod.log("manual hook OnDie");
    });

    mod.on_debug([&mod](int index)
    {
        mod.log("on_debug {}", index);
        //mod.send(id, data);
    });*/

    return 0;
}