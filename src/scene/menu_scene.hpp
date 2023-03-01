#ifndef SCENE_MENU_SCENE_HPP_
#define SCENE_MENU_SCENE_HPP_

#include "base_scene.hpp"

namespace scene {

class MenuScene : public internal::BaseScene {
private:
    bool m_start{};
    bool m_quit{};

    MenuScene() = default;

public:
    MenuScene(const MenuScene&) = delete;
    MenuScene(MenuScene&&) = delete;
    MenuScene& operator=(const MenuScene&) = delete;
    MenuScene& operator=(MenuScene&&) = delete;
    ~MenuScene() override = default;

    static MenuScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_MENU_SCENE_HPP_
