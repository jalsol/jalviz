#include "code_highlighter.hpp"

#include "raylib.h"
#include "utils.hpp"

namespace component {

void CodeHighlighter::render() {
    for (int i = 0; i < m_src_code.size(); ++i) {
        Color bg_color = (i == m_highlighted_line) ? BLACK : VIOLET;
        DrawRectangle(head_pos.x, head_pos.y + i * height, width, height,
                      bg_color);
        utils::DrawText(m_src_code.at(i),
                        {head_pos.x + 5, head_pos.y + i * height + 5}, WHITE,
                        20, 2);
    }
}

void CodeHighlighter::set_code(core::DoublyLinkedList<const char*>&& src_code) {
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
