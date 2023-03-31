#pragma once

struct ImGuiContext;

namespace tmg
{
    class tusmo;

    void draw_ui(ImGuiContext* imgui_context, tmg::tusmo& tusmo);
} // tmg