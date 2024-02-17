//
// Created by xmmmmmovo on 31/08/2023.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_RENDER_STRATEGY_HPP
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_RENDER_STRATEGY_HPP

namespace taixu {

class IRenderStrategy {
public:
    virtual ~IRenderStrategy() = default;

    virtual void render() = 0;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_RENDER_STRATEGY_HPP
