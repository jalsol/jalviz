#ifndef COMPONENT_FILE_DIALOG_HPP_
#define COMPONENT_FILE_DIALOG_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "gui_file_dialog.h"
#include "raylib.h"

namespace component {

/**
 * @brief File Dialog for opening and saving files
 */

class FileDialog {
public:
    /**
     * @brief The size of the file dialog
     */
    static constexpr Vector2 size{200, 50};

    /**
     * @brief Constructs a FileDialog object
     */
    FileDialog();

    /**
     * @brief Constructs a FileDialog object
     * @param mode the mode of the file dialog (open or save)
     * @param title the title of the file dialog
     * @param message the message of the file dialog
     */
    FileDialog(int mode, const char* title, const char* message);

    /**
     * @brief Renders the file dialog, updates the head position with offset
     * @param options_head the head position of the options
     * @param head_offset the offset of the head position
     * @return -1 if the file dialog is not active, 0/1 if a file was selected
     */
    int render_head(float& options_head, float head_offset);

    /**
     * @brief Renders the file dialog
     * @param x the x position of the file dialog
     * @param y the y position of the file dialog
     * @return -1 if the file dialog is not active, 0/1 if a file was selected
     */
    int render(float x, float y);

    /**
     * @brief Extracts the values from the file
     * @return the values from the file
     */
    core::Deque<int> extract_values();

    /**
     * @brief Checks if the file dialog is active
     * @return true if the file dialog is active, false otherwise
     */
    bool is_active() const;

    /**
     * @brief Gets the path of the file
     * @return the path of the file
     */
    std::string get_path();

    /**
     * @brief Sets the mode of the file dialog to open
     */
    void set_mode_open();

    /**
     * @brief Sets the mode of the file dialog to save
     */
    void set_mode_save();

    /**
     * @brief Sets the message of the file dialog
     * @param message the message of the file dialog
     */
    void set_message(const char* message);

    /**
     * @brief Sets the title of the file dialog
     * @param title the title of the file dialog
     */
    void set_title(const char* title);

private:
    /**
     * @brief The state of the file dialog
     */
    GuiFileDialogState m_file_dialog_state{
        InitGuiFileDialog(GetWorkingDirectory())};

    /**
     * @brief The path of the file
     */
    char m_file_input[constants::text_buffer_size] = "";  // NOLINT

    /**
     * @brief The mode of the file dialog (open or save)
     */
    int m_mode{};

    /**
     * @brief The message of the file dialog
     */
    const char* m_message;

    /**
     * @brief The title of the file dialog
     */
    const char* m_title;
};

}  // namespace component

#endif  // COMPONENT_FILE_DIALOG_HPP_
