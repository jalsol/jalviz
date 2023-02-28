#ifndef GUI_BASE_HPP_
#define GUI_BASE_HPP_

#include "raylib.h"

namespace gui::internal {

template<typename T>
class Base {
    virtual void render_link(Vector2 src, Vector2 dest) = 0;

public:
    virtual void update() = 0;
    virtual void render() = 0;
};

}  // namespace gui::internal

#endif  // GUI_BASE_HPP_
