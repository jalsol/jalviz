#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <array>
#include <cstddef>
#include <string>

#include "raylib.h"

/**
 * @brief The settings
 */
class Settings {
public:
    /**
     * @brief The number of colors
     */
    static constexpr int num_color = 9;

    /**
     * @brief The default colors
     */
    static constexpr std::array<unsigned, num_color> default_color{{
        0x00000000,
        0x82828200,
        0xffa10000,
        0x00e43000,
        0x873cbe00,
        0xe6293700,
        0x0079f100,
        0xff6dc200,
        0xf5f5f500,
    }};

    /**
     * @brief Deleted copy constructor
     */
    Settings(const Settings&) = delete;

    /**
     * @brief Deleted move constructor
     */
    Settings(Settings&&) = delete;

    /**
     * @brief Deleted copy assignment operator
     */
    Settings& operator=(const Settings&) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    Settings& operator=(Settings&&) = delete;

    /**
     * @brief Destructor
     */
    ~Settings();

    /**
     * @brief Gets the instance
     * @return Settings& The instance
     */
    static Settings& get_instance();

    /**
     * @brief Gets the color
     * @param index The index of the color
     * @return Color& The color
     */
    Color& get_color(std::size_t index);

    /**
     * @brief Gets the color
     * @param index The index of the color
     * @return Color The color
     */
    Color get_color(std::size_t index) const;

    /**
     * @brief Saves the settings to a file
     * @param path The path to the file
     */
    void save_to_file(const std::string& path);

private:
    /**
     * @brief Private constructor
     */
    Settings() = default;

    /**
     * @brief The colors
     */
    std::array<Color, num_color> m_colors{};
};

#endif  // SETTINGS_HPP_
