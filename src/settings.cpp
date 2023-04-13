#include "settings.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "constants.hpp"
#include "raylib.h"

Settings& Settings::get_instance() {
    static Settings settings;
    return settings;
}

void Settings::save_to_file(const std::string& path) {
    std::ofstream file_out(path, std::ios::binary);

    for (auto i = 0; i < num_color; ++i) {
        unsigned value = ColorToInt(m_colors.at(i));
        file_out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
}

Settings::~Settings() { save_to_file(constants::default_color_path); }

Color& Settings::get_color(std::size_t index) { return m_colors.at(index); }

Color Settings::get_color(std::size_t index) const {
    return m_colors.at(index);
}
