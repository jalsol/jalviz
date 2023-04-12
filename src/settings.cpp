#include "settings.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "raylib.h"

Settings& Settings::get_instance() {
    static Settings settings;
    return settings;
}

void Settings::save_to_file(const std::string& path) {
    std::ofstream file_out(path);

    for (auto i = 0; i < num_color; ++i) {
        file_out << std::setfill('0') << std::setw(6) << std::hex
                 << ((unsigned)(ColorToInt(m_colors.at(i))) >> 8) << '\n';
    }
}

Settings::~Settings() { save_to_file("data/color.txt"); }

Color& Settings::get_color(std::size_t index) { return m_colors.at(index); }

Color Settings::get_color(std::size_t index) const {
    return m_colors.at(index);
}
