#include "settings_scene.hpp"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "component/text_input.hpp"
#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"
#include "settings.hpp"
#include "utils.hpp"

namespace scene {

void SettingsScene::open_from_file(const std::string& path) {
    Settings& settings = Settings::get_instance();
    std::ifstream file_in(path);

    if (!file_in.is_open()) {
        std::ofstream file_out(path);
        file_out << "000000\n"
                    "828282\n"
                    "ffa100\n"
                    "00e430\n"
                    "873cbe\n"
                    "e62937\n"
                    "0079f1\n"
                    "ff6dc2\n"
                    "f5f5f5";
        file_out.close();
        file_in.close();
        file_in.open(path);
    }

    unsigned int hex_value;
    for (auto i = 0; i < Settings::num_color; ++i) {
        file_in >> std::hex >> hex_value;
        hex_value = (hex_value << 8) | 0xff;
        settings.get_color(i) = GetColor(hex_value);
    }

    set_buffer();
}

SettingsScene::SettingsScene() { open_from_file("data/color.txt"); }

void SettingsScene::set_buffer() {
    std::stringstream sstr;

    for (auto i = 0; i < Settings::num_color; ++i) {
        sstr << std::setfill('0') << std::setw(6) << std::hex
             << ((unsigned)ColorToInt(Settings::get_instance().get_color(i)) >>
                 8);
        std::strncpy(m_buffers.at(i), sstr.str().c_str(), 7);
        sstr.str(std::string());
    }
}

void SettingsScene::set_color() {
    for (auto i = 0; i < Settings::num_color; ++i) {
        Settings::get_instance().get_color(i) =
            utils::color_from_hex(m_buffers.at(i));
    }
}

void SettingsScene::render() {
    Settings& settings = Settings::get_instance();
    constexpr int second_col_x = constants::scene_width / 2 + head_pos.y;
    int second_col_y = 100;
    constexpr int vertical_gap = 30;
    const Color text_color =
        utils::adaptive_text_color(settings.get_color(Settings::num_color - 1));

    auto [head_x, head_y] = head_pos;

    for (auto i = 0; i < m_buffers.size(); ++i) {
        Rectangle input_shape;
        const char* text = nullptr;

        if (i + 1 != m_buffers.size()) {
            input_shape = {(float)head_x, (float)head_y, input_size.x,
                           input_size.y};
            text = TextFormat("Color %d", i + 1);
        } else {
            input_shape = {(float)second_col_x, (float)second_col_y + 400,
                           input_size.x, input_size.y};
            text = "Background color";
        }

        utils::DrawText(text, {(float)input_shape.x, (float)input_shape.y - 25},
                        text_color, 20, 2);
        DrawRectangleRec(input_shape, RAYWHITE);
        if (GuiTextBox(input_shape, m_buffers.at(i), 7, m_edit_mode.at(i))) {
            m_edit_mode.at(i) ^= 1;
        }

        const Rectangle preview_shape{input_shape.x + input_size.x + 10,
                                      input_shape.y, input_size.y,
                                      input_size.y};

        DrawRectangleRec(preview_shape, settings.get_color(i));

        if (m_selected == i) {
            DrawRectangleLinesEx(preview_shape, 3, settings.get_color(5));
        } else {
            DrawRectangleLinesEx(preview_shape, 2, text_color);
        }

        head_y += input_size.y + vertical_gap;
    }

    {
        Color& color = settings.get_color(m_selected);
        auto new_color = GuiColorPicker({second_col_x, (float)second_col_y,
                                         4 * input_size.y, 4 * input_size.y},
                                        nullptr, color);

        if (ColorToInt(color) != ColorToInt(new_color)) {
            color = new_color;
            set_buffer();
        }
    }

    {
        second_col_y += 4 * input_size.y;
        utils::DrawText("Import config",
                        {second_col_x + 10, (float)second_col_y}, text_color,
                        20, 2);
        m_open = m_open_file.render(second_col_x, (float)second_col_y + 25);
    }

    {
        second_col_y += component::FileDialog::size.y + vertical_gap;
        utils::DrawText("Export config",
                        {second_col_x + 10, (float)second_col_y}, text_color,
                        20, 2);
        m_save = m_save_file.render(second_col_x, (float)second_col_y + 25);
    }
}

void SettingsScene::interact() {
    if (m_open > 0) {
        open_from_file(m_open_file.get_path());
        return;
    }

    if (m_save > 0) {
        Settings::get_instance().save_to_file(m_save_file.get_path());
        return;
    }

    const Vector2 mouse = GetMousePosition();
    const bool left_clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    auto [head_x, head_y] = head_pos;

    for (auto i = 0; i < m_buffers.size(); ++i) {
        const Rectangle input_shape{(float)head_x, (float)head_y, input_size.x,
                                    input_size.y};
        const Rectangle preview_shape{input_shape.x + input_size.x + 10,
                                      input_shape.y, input_size.y,
                                      input_size.y};

        if (m_edit_mode.at(i)) {
            m_selected = i;
        }
    }

    set_color();
}

}  // namespace scene
