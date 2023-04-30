#ifndef COMPONENT_CODE_HIGHLIGHTER_HPP_
#define COMPONENT_CODE_HIGHLIGHTER_HPP_

#include "constants.hpp"
#include "core/doubly_linked_list.hpp"
#include "raylib.h"

namespace component {

/**
 * @brief Code highlighter that highlights the source code on each step
 */

class CodeHighlighter {
public:
    /**
     * @brief Renders the code highlighter
     */
    void render();

    /**
     * @brief Set the source code to be highlighted
     * @param src_code a collection of lines of source code
     */
    void set_code(core::DoublyLinkedList<const char*>&& src_code);

    /**
     * @brief Pushes the line number to be highlighted into the sequence
     * @param line_number the line number to be pushed into the sequence
     */
    void push_into_sequence(int line_number);

    /**
     * @brief Highlights the line number at the given frame index
     * @param frame_idx the frame index
     */
    void highlight(int frame_idx);

    /**
     * @brief Clears the code highlighter
     */
    void clear();

private:
    /**
     * @brief The width of the code highlighter
     */
    static constexpr int width = 400;

    /**
     * @brief The height of the code highlighter
     */
    static constexpr int height = 30;

    /**
     * @brief The position of the topleft code highlighter
     */
    static constexpr Vector2 head_pos{constants::scene_width - width,
                                      2.5F * height};

    /**
     * @brief The source code to be highlighted
     */
    core::DoublyLinkedList<const char*> m_src_code;

    /**
     * @brief The sequence of line numbers to be highlighted
     */
    core::DoublyLinkedList<int> m_sequence;

    /**
     * @brief The highlighted line number
     */
    int m_highlighted_line{-1};
};

}  // namespace component

#endif  // COMPONENT_CODE_HIGHLIGHTER_HPP_
