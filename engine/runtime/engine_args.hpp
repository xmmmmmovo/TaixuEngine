//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include "core/base/public_singleton.hpp"
#include "graphics/render/render_api.hpp"
namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;

public:
    RenderAPI api{RenderAPI::OPENGL};
};

}// namespace taixu

#endif//TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
