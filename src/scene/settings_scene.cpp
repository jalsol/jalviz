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
    std::ifstream file_in(path, std::ios::binary);

    if (!file_in.is_open()) {
        std::ofstream file_out(path, std::ios::binary);

        for (auto i = 0; i < Settings::num_color; ++i) {
            unsigned value = Settings::default_color.at(i);
            file_out.write(reinterpret_cast<const char*>(&value),
                           sizeof(value));
        }

        file_out.close();

        file_in.close();
        file_in.open(path, std::ios::binary);
    }

    unsigned hex_value;
    for (auto i = 0; i < Settings::num_color; ++i) {
        file_in.read(reinterpret_cast<char*>(&hex_value), sizeof(hex_value));
        settings.get_color(i) = GetColor(hex_value);
    }

    set_buffer();
}

SettingsScene::SettingsScene() {
    open_from_file(constants::default_color_path);
}

void SettingsScene::set_buffer() {
    std::stringstream sstr;

    for (auto i = 0; i < Settings::num_color; ++i) {
        sstr << std::setfill('0') << std::setw(6) << std::hex
             << ((unsigned)ColorToInt(Settings::get_instance().get_color(i)) >>
                 8);
        m_inputs.at(i).set_input(sstr.str().c_str(), 7);
        sstr.str(std::string());
    }
}

void SettingsScene::set_color() {
    for (auto i = 0; i < Settings::num_color; ++i) {
        Settings::get_instance().get_color(i) =
            utils::color_from_hex(m_inputs.at(i).get_input());
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
    const auto input_size = component::TextInput::size;

    for (auto i = 0; i < m_inputs.size(); ++i) {
        Vector2 input_head;

        if (i + 1 != m_inputs.size()) {
            input_head = {(float)head_x, (float)head_y};
        } else {
            input_head = {(float)second_col_x, (float)second_col_y + 400};
        }

        // to be honest, I don't exactly know how TextFormat works
        // there are some bizarre behaviors which make me call set_label
        // every frame
        if (i + 1 != m_inputs.size()) {
            m_inputs.at(i).set_label(TextFormat("Color %d", i + 1));
        } else {
            m_inputs.at(i).set_label("Background color");
        }

        m_inputs.at(i).render(input_head.x, input_head.y);

        const Rectangle preview_shape{input_head.x + input_size.x + 10,
                                      input_head.y, input_size.y, input_size.y};

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

    for (auto i = 0; i < m_inputs.size(); ++i) {
        if (m_inputs.at(i).is_active()) {
            m_selected = i;
        }
    }

    set_color();
}

}  // namespace scene
