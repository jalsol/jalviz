#include "file_dialog.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "core/deque.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace component {

FileDialog::FileDialog(int mode, const char* title, const char* message)
    : m_mode{mode}, m_title{title}, m_message{message} {
    m_file_dialog_state.windowActive = false;
    m_file_dialog_state.SelectFilePressed = false;
}

FileDialog::FileDialog() : FileDialog(0, "Open file...", "Open file") {}

int FileDialog::render(float x, float y) {
    if (m_file_dialog_state.windowActive) {
        GuiLock();
    }

    Rectangle shape{x, y, size.x, size.y};

    if (GuiButton(shape, GuiIconText(ICON_FILE_OPEN, "Select file"))) {
        m_file_dialog_state.windowActive = true;
    }

    GuiUnlock();
    GuiFileDialog(&m_file_dialog_state);

    if (m_file_dialog_state.SelectFilePressed) {
        m_file_dialog_state.SelectFilePressed = false;
        return 1;
    } else if (!m_file_dialog_state.windowActive) {
        return -1;
    } else {
        return 0;
    }

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
std::string FileDialog::get_path() {
    return TextFormat("%s/%s",
                      m_file_dialog_state.dirPathText,
                      m_file_dialog_state.fileNameText);
}

}  // namespace component
