#include "file_dialog.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "core/deque.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace component {

FileDialog::FileDialog(int mode, const char* title, const char* message)
    : m_mode{mode}, m_title{title}, m_message{message} {}

FileDialog::FileDialog() : FileDialog(0, "Open file...", "Open file") {}

int FileDialog::render(float x, float y) {
    m_file_dialog_state.title = m_title;
    m_file_dialog_state.fileName = m_file_input;
    m_file_dialog_state.message = m_message;
    m_file_dialog_state.dialogType = m_mode;

    int result = -1;
    if (m_file_dialog_state.windowActive) {
        GuiLock();
        result = GuiFileDialog(&m_file_dialog_state);
        if (result >= 0) {
            m_file_dialog_state.windowActive = false;
        }
    }

    const Rectangle shape{x, y, size.x, size.y};

    if (GuiButton(shape, GuiIconText(ICON_FILE_OPEN, "Select file"))) {
        m_file_dialog_state.windowActive = true;
    }

    GuiUnlock();
    return result;
}

int FileDialog::render_head(float& options_head, float head_offset) {
    int ret = render(options_head, constants::scene_height - size.y);
    options_head += (size.x + head_offset);
    return ret;
}

core::Deque<int> FileDialog::extract_values() {
    std::ifstream ifs(get_path());
    char buffer[constants::text_buffer_size]{};  // NOLINT
    ifs >> buffer;

    return utils::str_extract_data(buffer);  // NOLINT
}

bool FileDialog::is_active() const { return m_file_dialog_state.windowActive; }

void FileDialog::set_mode_open() { m_mode = DIALOG_OPEN_FILE; }

void FileDialog::set_mode_save() { m_mode = DIALOG_SAVE_FILE; }

void FileDialog::set_message(const char* message) { m_message = message; }

void FileDialog::set_title(const char* title) { m_title = title; }
std::string FileDialog::get_path() { return m_file_input; }

}  // namespace component
