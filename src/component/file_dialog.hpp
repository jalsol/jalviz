#ifndef COMPONENT_FILE_DIALOG_HPP_
#define COMPONENT_FILE_DIALOG_HPP_

#include "constants.hpp"
#include "core/deque.hpp"
#include "gui_file_dialog.h"
#include "raylib.h"

namespace component {

class FileDialog {
private:
    GuiFileDialogState m_file_dialog_state{
        InitGuiFileDialog(GetWorkingDirectory())};

    char m_file_input[constants::text_buffer_size] = "";  // NOLINT

public:
    static constexpr Vector2 size{200, 50};

    void render(float& options_head, float head_offset);
    core::Deque<int> extract_values();
    bool is_pressed() const;
    void reset_pressed();
};

}  // namespace component

#endif  // COMPONENT_FILE_DIALOG_HPP_
