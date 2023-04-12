#include "code_highlighter.hpp"

#include "raylib.h"
#include "settings.hpp"
#include "utils.hpp"

namespace component {

void CodeHighlighter::render() {
    for (int i = 0; i < m_src_code.size(); ++i) {
        const Settings& settings = Settings::get_instance();

        Color bg_color = (i == m_highlighted_line) ? settings.get_color(4)
                                                   : settings.get_color(0);
        Rectangle shape{head_pos.x, head_pos.y + i * height, width, height};
        Vector2 text_head = {head_pos.x + 10, head_pos.y + i * height + 5};

        DrawRectangleRec(shape, bg_color);
        utils::DrawText(m_src_code.at(i), text_head, WHITE, 20, 2);
    }
}

void CodeHighlighter::set_code(core::DoublyLinkedList<const char*>&& src_code) {
    clear();
    m_src_code = src_code;
}

void CodeHighlighter::push_into_sequence(int line_number) {
    m_sequence.insert(m_sequence.size(), line_number);
}

void CodeHighlighter::highlight(int frame_idx) {
    m_highlighted_line = m_sequence.at(frame_idx);
}

void CodeHighlighter::clear() {
    m_src_code.clear();
    m_sequence.clear();
}

}  // namespace component
