#ifndef GUI_BASE_GUI_HPP_
#define GUI_BASE_GUI_HPP_

#include "raylib.h"

namespace gui::internal {

/**
 * @brief The base class for all GUI classes
 */

class Base {
public:
    /**
     * @brief Constructs a Base object
     */
    Base() = default;

    /**
     * @brief Copy constructor
     */
    Base(const Base&) = default;

    /**
     * @brief Move constructor
     */
    Base(Base&&) = default;

    /**
     * @brief Copy assignment operator
     */
    Base& operator=(const Base&) = default;

    /**
     * @brief Move assignment operator
     */
    Base& operator=(Base&&) = default;

    /**
     * @brief Destructor
     */
    virtual ~Base() = default;

    /**
     * @brief Updates the GUI
     */
    virtual void update() = 0;

    /**
     * @brief Renders the GUI
     */
    virtual void render() = 0;

private:
    /**
     * @brief Renders a link between two elements
     * @param src The source position
     * @param dest The destination position
     */
    virtual void render_link(Vector2 src, Vector2 dest) = 0;
};

}  // namespace gui::internal

#endif  // GUI_BASE_GUI_HPP_
