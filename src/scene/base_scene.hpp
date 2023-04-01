#ifndef SCENE_BASE_SCENE_HPP_
#define SCENE_BASE_SCENE_HPP_

#include "component/code_highlighter.hpp"
#include "component/sequence_controller.hpp"
#include "raylib.h"
#include "scene_options.hpp"

namespace scene::internal {

class BaseScene {
protected:
    static constexpr Vector2 button_size{200, 50};
    static constexpr int head_offset = 20;
    float options_head{};

    virtual bool render_go_button() const;
    virtual void render_options(SceneOptions& scene_config);
    virtual void render_inputs(){};

    component::SequenceController m_sequence_controller;
    component::CodeHighlighter m_code_highlighter;

    bool m_edit_mode{};
    bool m_edit_action{};

public:
    BaseScene() = default;
    BaseScene(const BaseScene&) = delete;
    BaseScene(BaseScene&&) = delete;
    BaseScene& operator=(const BaseScene&) = delete;
    BaseScene& operator=(BaseScene&&) = delete;

    virtual ~BaseScene() = default;

    virtual void render() {}
    virtual void interact(){};
};

}  // namespace scene::internal

#endif  // SCENE_BASE_SCENE_HPP_
