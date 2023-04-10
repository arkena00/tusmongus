#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <tmg/tusmo.hpp>

namespace tmg
{
    void draw_ui(ImGuiContext* imgui_context, tmg::tusmo& tusmo)
    {
        ImGui::SetCurrentContext(imgui_context);

        ImGuiIO& io = ImGui::GetIO();

        ImVec2 window_size;
        ImVec2 window_pos;
        window_size.x = io.DisplaySize.x * 0.75;
        window_size.y = io.DisplaySize.y * 0.75;
        window_pos.x = (io.DisplaySize.x - window_size.x) / 2;
        window_pos.y = (io.DisplaySize.y - window_size.y) / 2;
        ImGui::SetNextWindowPos(window_pos);
        ImGui::SetNextWindowSize(window_size);
        ImGui::Begin("##TUSMO", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            tusmo.try_word(tusmo.input());
        }
        else if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Backspace)))
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
        float cell_width = 40;
        float cell_margin = 4;
        float font_size = 36;

        float letter_padding_x = cell_width - font_size + (cell_margin * 2) + 1;
        float letter_padding_y = cell_width - font_size;

        std::vector<std::string> preview(10, ".");

        for (int y = 0; y < tmg::tusmo::max_attemps; ++y)
        {
            for (int x = 0; x < tusmo.word().size(); ++x)
            {
                ImColor color = color::blue;
                if (x == 0 && y <= tusmo.attempts().size()) color = color::red;

                posx = p.x + x * cell_width;
                posy = p.y + y * cell_width;

                // draw cell background
                draw_list->AddRectFilled(ImVec2(posx + cell_margin, posy + cell_margin), ImVec2(posx + cell_width, posy + cell_width), color, 0.5);

                if (y < tusmo.attempts().size() && x < tusmo.attempt(y).size())
                {
                    auto placement = tusmo.attempt(y).placement(x);

                    if (placement == letter_placement::wrong)
                    {
                        color = color::yellow;
                        draw_list->AddCircleFilled(ImVec2(posx + (cell_width + cell_margin) / 2, posy + (cell_width + cell_margin) / 2), cell_width / 2 - 2, color);
                    } else
                    {
                        if (placement == letter_placement::good)
                        {
                            color = color::red;
                            preview[x] = tusmo.word_letter(x);
                        }
                        draw_list->AddRectFilled(ImVec2(posx + cell_margin, posy + cell_margin), ImVec2(posx + cell_width, posy + cell_width), color);
                    }
                }

                // current line
                if (y == tusmo.attempts().size())
                {
                    if (x < tusmo.input().size())
                    {
                        draw_list->AddRectFilled(ImVec2(posx + cell_margin, posy + cell_margin), ImVec2(posx + cell_width, posy + cell_width), color::current);
                        draw_list->AddText(tusmo.font, font_size, ImVec2(posx + letter_padding_x, posy + letter_padding_y), letter_color, tusmo.input_letter(x).c_str());
                    }
                    else
                    {
                        draw_list->AddText(tusmo.font, font_size, ImVec2(posx + letter_padding_x, posy + letter_padding_y), letter_color, preview[x].c_str());
                    }
                }
                // previous attempts
                else if (y < tusmo.attempts().size())
                {
                    draw_list->AddText(tusmo.font, font_size, ImVec2(posx + letter_padding_x, posy + letter_padding_y), letter_color, tusmo.attempt_letter(x, y).c_str());
                }
            }
        }

        // Advance the ImGui cursor to claim space in the window (otherwise the window will appear small and needs to be resized)
        //ImGui::Dummy(ImVec2(800, 200));

        ImGui::End();
    }
} // tmg