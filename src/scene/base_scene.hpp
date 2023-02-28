#ifndef SCENE_BASE_SCENE_HPP_
#define SCENE_BASE_SCENE_HPP_

#include "core/stack.hpp"

namespace scene {

template<typename T>
class BaseScene {
protected:
    BaseScene() = default;

public:
    BaseScene(const BaseScene&) = delete;
    BaseScene(BaseScene&&) = delete;
    BaseScene& operator=(const BaseScene&) = delete;
    BaseScene& operator=(BaseScene&&) = delete;
    virtual ~BaseScene() = default;

    static BaseScene& get_instance();
    virtual void render() = 0;
    virtual void interact() = 0;
};

template<typename T>
BaseScene<T>& BaseScene<T>::get_instance() {
    static BaseScene<T> scene;
    return scene;
}

}  // namespace scene

#endif  // SCENE_BASE_SCENE_HPP_
