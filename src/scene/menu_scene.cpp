#include "menu_scene.hpp"

#include <iostream>

#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"
#include "scene_registry.hpp"
#include "utils.hpp"

namespace scene {

MenuScene::MenuScene() {
    constexpr int block_width = component::MenuItem::block_width;
    constexpr int block_height = component::MenuItem::block_height;
    constexpr int button_width = component::MenuItem::button_width;
    constexpr int button_height = component::MenuItem::button_height;
    constexpr int gap = 20;

    constexpr int first_row_y =
        constants::scene_height / 16.0F * 5 - block_height / 2.0F;

    // first row
    {
        constexpr int row_width =
            3 * component::MenuItem::block_width + 2 * gap;
        constexpr int row_x = constants::scene_width / 2.0F - row_width / 2.0F;
        constexpr int row_y = first_row_y;

        for (auto i = 0; i < 3; ++i) {
            m_menu_items[i] = component::MenuItem(
                i, labels[i], row_x + i * (block_width + gap), row_y,
                img_paths[i]);
        }
    }

    // second row
    {
        constexpr int row_width = 4 * block_width + 3 * gap;
        constexpr int row_x = constants::scene_width / 2.0F - row_width / 2.0F;
        constexpr int row_y = first_row_y + block_height + gap;

        for (auto i = 3; i < 7; ++i) {
            m_menu_items[i] = component::MenuItem(
                i, labels[i], row_x + (i - 3) * (block_width + gap), row_y,
                img_paths[i]);
        }
    }
}

void MenuScene::render() {
    // Menu text
    constexpr int menu_font_size = 60;
    constexpr int menu_font_spacing = 5;

    constexpr const char* menu_text = "CS162 - VisuAlgo.net clone in C++";

    const Vector2 menu_text_size =
        utils::MeasureText(menu_text, menu_font_size, menu_font_spacing);

    const Vector2 menu_text_pos{
        constants::scene_width / 2.0F - menu_text_size.x / 2,
        constants::scene_height / 16.0F - menu_text_size.y / 2};

    utils::DrawText(menu_text, menu_text_pos, BLACK, menu_font_size,
                    menu_font_spacing);

    // Sub text
    constexpr int sub_font_size = 30;
    constexpr int sub_font_spacing = 2;

    constexpr const char* sub_text = "By Quang-Truong Nguyen (@jalsol)";

    const Vector2 sub_text_size =
        utils::MeasureText(sub_text, sub_font_size, sub_font_spacing);

    const Vector2 sub_text_pos{
        constants::scene_width / 2.0F - sub_text_size.x / 2,
        menu_text_pos.y + menu_text_size.y / 2 + sub_text_size.y};

    utils::DrawText(sub_text, sub_text_pos, BLACK, sub_font_size,
                    sub_font_spacing);

    // Button
    constexpr int block_width = 300;
    constexpr int block_height = 200;
    constexpr int button_width = block_width;
    constexpr int button_height = 50;
    constexpr int gap = 20;
    constexpr int first_row_y =
        constants::scene_height / 16.0F * 5 - block_height / 2.0F;

    for (auto i = 0; i < 7; ++i) {
        m_menu_items[i].render();
    }

    const Rectangle quit_button_shape{
        constants::scene_width / 2.0F - 128,
        constants::scene_height / 16.0F * 15 - block_height / 2.0F, 256, 64};

    m_quit = GuiButton(quit_button_shape, "Quit");

    // Bottom text
    constexpr int bot_font_size = 20;
    constexpr int bot_font_spacing = 2;

    constexpr const char* bot_text =
        "(pls read the src code, i tried so hard for this)";

    const Vector2 bot_text_size =
        utils::MeasureText(bot_text, bot_font_size, bot_font_spacing);

    const Vector2 bot_text_pos{
        constants::scene_width / 2.0F - bot_text_size.x / 2,
        constants::scene_height - 1.5F * bot_text_size.y};

    utils::DrawText(bot_text, bot_text_pos, BLACK, bot_font_size,
                    bot_font_spacing);
}

void MenuScene::interact() {
    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();

    if (m_quit) {
        registry.close_window();
        return;
    }

    for (auto i = 0; i < 7; ++i) {
        if (m_menu_items[i].clicked()) {
            m_next_scene = i;
            m_start = true;
        }
    }

    for (auto i = 0; i < 7; ++i) {
        m_menu_items[i].reset();
    }

    if (m_start) {
        registry.set_scene(m_next_scene);
        m_start = false;
    }
}

}  // namespace scene
