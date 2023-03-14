#ifndef GUI_BASE_GUI_HPP_
#define GUI_BASE_GUI_HPP_

#include "raylib.h"

namespace gui::internal {

class Base {
    virtual void render_link(Vector2 src, Vector2 dest) = 0;

public:
    Base() = default;
    Base(const Base&) = default;
    Base(Base&&) = default;
    Base& operator=(const Base&) = default;
    Base& operator=(Base&&) = default;

    virtual ~Base() = default;

    virtual void update() = 0;
    virtual void render() = 0;
};

}  // namespace gui::internal

#endif  // GUI_BASE_GUI_HPP_
