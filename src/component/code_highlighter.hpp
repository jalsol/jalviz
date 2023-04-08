#ifndef COMPONENT_CODE_HIGHLIGHTER_HPP_
#define COMPONENT_CODE_HIGHLIGHTER_HPP_

#include "constants.hpp"
#include "core/doubly_linked_list.hpp"
#include "raylib.h"

namespace component {

class CodeHighlighter {
private:
    static constexpr int width = 400;
    static constexpr int height = 30;
    static constexpr Vector2 head_pos{constants::scene_width - width,
                                      2.5F * height};

    core::DoublyLinkedList<const char*> m_src_code;
    core::DoublyLinkedList<int> m_sequence;
    int m_highlighted_line{-1};

public:
    void render();
    void set_code(core::DoublyLinkedList<const char*>&& src_code);
    void push_into_sequence(int line_number);
    void highlight(int frame_idx);
    void clear();
};

}  // namespace component

#endif  // COMPONENT_CODE_HIGHLIGHTER_HPP_
