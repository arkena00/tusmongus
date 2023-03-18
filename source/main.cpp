#include <ark/mod.hpp>

int mod_load(ark::mod& mod)
{
    ark::mod_info info;
    info.name = "Amodus";
    info.description = "A mod with many roles";
    info.version = ark::version{ 0, 0, 8 };
    mod.set_info(std::move(info));

    mod.add_setting("test", 1);
    mod.log("test message from mod");
    /*
    mod.on_enable([]{ mod.log("on_enable mod"); });
    mod.on_disable([]{ mod.log("on_disable mod"); });

    mod.register_class<amodus::player>();
    mod.register_class<amodus::game>();

    mod.register_hook<&au::PlayerControl::SetName>::before([this](auto&&, auto name){
                on_set_name(cs_tostd(name));
            });*/

    return 0;
}