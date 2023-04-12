#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <array>
#include <cstddef>
#include <string>

#include "raylib.h"

class Settings {
public:
    static constexpr int num_color = 9;

private:
    Settings() = default;
    std::array<Color, num_color> m_colors{};

public:
    Settings(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings& operator=(Settings&&) = delete;
    ~Settings();

    static Settings& get_instance();

    Color& get_color(std::size_t index);
    Color get_color(std::size_t index) const;

    void save_to_file(const std::string& path);
};

#endif  // SETTINGS_HPP_
