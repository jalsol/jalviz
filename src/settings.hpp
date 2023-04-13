#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <array>
#include <cstddef>
#include <string>

#include "raylib.h"

class Settings {
public:
    static constexpr int num_color = 9;
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
