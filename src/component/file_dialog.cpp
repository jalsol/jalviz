#include "file_dialog.hpp"

#include <fstream>
#include <string>

#include "core/deque.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace component {

void FileDialog::render(float& options_head, float head_offset) {
    if (m_file_dialog_state.windowActive) {
        GuiLock();
    }

    const char* const file_name =
        static_cast<char*>(m_file_dialog_state.fileNameText);

    const char* const text =
        (m_file_dialog_state.SelectFilePressed) ? file_name : "Select file";

    Rectangle shape{options_head, constants::scene_height - size.y, size.x,
                    size.y};

    if (GuiButton(shape, GuiIconText(ICON_FILE_OPEN, text))) {
        m_file_dialog_state.windowActive = true;
    }

    options_head += (size.x + head_offset);

    GuiUnlock();
    GuiFileDialog(&m_file_dialog_state);
}

core::Deque<int> FileDialog::extract_values() {
    std::string file_name;
    file_name += static_cast<char*>(m_file_dialog_state.dirPathText);
    file_name += '/';
    file_name += static_cast<char*>(m_file_dialog_state.fileNameText);

    std::ifstream ifs(file_name);
    char buffer[constants::text_buffer_size]{};  // NOLINT
    ifs >> buffer;

    return utils::str_extract_data(buffer);  // NOLINT
}

bool FileDialog::is_pressed() const {
    return m_file_dialog_state.SelectFilePressed;
}

void FileDialog::reset_pressed() {
    m_file_dialog_state.SelectFilePressed = false;
}

}  // namespace component
