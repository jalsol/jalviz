#ifndef COMPONENT_FILE_DIALOG_HPP_
#define COMPONENT_FILE_DIALOG_HPP_

#include <string>

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

    int m_mode{};
    const char* m_message;
    const char* m_title;

public:
    static constexpr Vector2 size{200, 50};

    FileDialog();
    FileDialog(int mode, const char* title, const char* message);

    int render_head(float& options_head, float head_offset);
    int render(float x, float y);
    core::Deque<int> extract_values();
    bool is_active() const;
    std::string get_path();
    void set_mode_open();
    void set_mode_save();
    void set_message(const char* message);
    void set_title(const char* title);
};

}  // namespace component

#endif  // COMPONENT_FILE_DIALOG_HPP_
