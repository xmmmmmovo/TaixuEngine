//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_RENDER_API_HPP
#define TAIXUENGINE_RENDER_API_HPP

namespace taixu {

/**
 * @brief 决定渲染API
 * I1 版本暂时只有 Opengl
 */
enum class RenderAPI { NONE, OPENGL };

/**
 * @brief 决定shaderAPI
 */
enum class ShaderAPI { NONE, GLSL, HLSL };

[[maybe_unused]] void loadAPI(RenderAPI api);

}// namespace taixu

#endif//TAIXUENGINE_RENDER_API_HPP
