//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_RENDER_API_HPP
#define TAIXUENGINE_RENDER_API_HPP

#include "GLFW/glfw3.h"
#include "core/base/macro.hpp"
#include "core/base/noncopyable.hpp"
namespace taixu {

/**
 * @brief 决定渲染API
 * I1 版本暂时只有 Opengl
 */
enum class GraphicsAPI { NONE, OPENGL };

/**
 * @brief 决定shaderAPI
 */
enum class ShaderAPI { NONE, GLSL, HLSL };

/**
 * @brief 决定渲染API
 */
class AbstractGraphicsAPILoader : private noncopyable {
protected:
    GLFWwindow *_window{nullptr};

public:
    virtual void initLoad() const            = 0;
    virtual void apiLoad(GLFWwindow *window) = 0;
    virtual void swapBuffers() const         = 0;
};

std::unique_ptr<AbstractGraphicsAPILoader>
createGraphicsAPILoader(GraphicsAPI api);

}// namespace taixu

#endif//TAIXUENGINE_RENDER_API_HPP
