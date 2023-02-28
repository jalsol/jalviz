#ifndef SCENE_MENU_SCENE_HPP_
#define SCENE_MENU_SCENE_HPP_

#include "base_scene.hpp"

namespace scene {

class MenuScene : public BaseScene<void> {
private:
    bool m_start{false};
    bool m_quit{false};

public:
    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_MENU_SCENE_HPP_
