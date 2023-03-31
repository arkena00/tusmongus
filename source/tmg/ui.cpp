#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <tmg/tusmo.hpp>

namespace tmg
{
    void draw_ui(ImGuiContext* imgui_context, tmg::tusmo& tusmo)
    {
        ImGui::SetCurrentContext(imgui_context);

        ImGui::Begin("TUSMO GAME");

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            tusmo.try_word(tusmo.input());
        }
        else if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Backslash)))
        {
            tusmo.erase();
        }
        else
        {
            // update input
            for (int key = ImGuiKey_A; key < ImGuiKey_Z + 1; ++key)
            {
                if (ImGui::IsKeyPressed(ImGui::GetKeyIndex((ImGuiKey) key))) tusmo.update_input(key - ImGuiKey_A + 'A');
            }
        }

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();

        float posx = 0;
        float posy = 0;
        ImColor letter_color(255, 255, 255);
        for (int y = 0; y < tmg::tusmo::max_attemps; ++y)
        {
            for (int x = 0; x < tusmo.word().size(); ++x)
            {
                ImColor color(80, 80, 220);

                float w = 40;
                posx = p.x + x * w;
                posy = p.y + y * w;

                if (tusmo.is_attempt_letter_red(x, y)) color = ImColor(255, 0, 0);
                draw_list->AddRectFilled(ImVec2(posx + 4, posy + 4), ImVec2(posx + w, posy + w), color, 0.5);

                // current line
                if (y == tusmo.attempts().size())
                {
                    if (x < tusmo.input().size())
                    {
                        if (x == 0) color = ImColor(255, 0, 0);
                        draw_list->AddText(nullptr, 48, ImVec2(posx, posy), letter_color, tusmo.input_letter(x).c_str());
                    }
                }
                // previous attempts
                else if (y < tusmo.attempts().size())
                {
                    draw_list->AddText(nullptr, 48, ImVec2(posx, posy), letter_color, tusmo.attempt_letter(x, y).c_str());
                }
            }
        }

        // Advance the ImGui cursor to claim space in the window (otherwise the window will appear small and needs to be resized)
        ImGui::Dummy(ImVec2(800, 200));

        ImGui::End();
    }
} // tmg