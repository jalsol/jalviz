#include "menu_scene.hpp"

#include <iostream>

#include "constants.hpp"
#include "raygui.h"
#include "utils.hpp"
#include "scene_registry.hpp"

namespace scene {

MenuScene& MenuScene::get_instance() {
    static MenuScene scene;
    return scene;
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
        constants::scene_height / 3.0F - menu_text_size.y / 2};

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
    constexpr int button_width = 256;
    constexpr int button_height = 64;

    const Rectangle start_button_shape{
        constants::scene_width / 2.0F - button_width / 2.0F,
        constants::scene_height / 16.0F * 9 - button_height / 2.0F,
        button_width, button_height};

    m_start = GuiButton(start_button_shape, "Start");

    const Rectangle quit_button_shape{
        start_button_shape.x,
        constants::scene_height / 16.0F * 11 - button_height / 2.0F,
        button_width, button_height};

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

    if (m_start) {
        registry.set_scene(Stack);
    } else if (m_quit) {
        std::cout << "aww man\n";
        m_quit = false;
    }
}

}  // namespace scene
