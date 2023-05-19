//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include "ImGuizmo.h"
#include "engine.hpp"
#include "management/ecs/components/transform/transform_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/graphics/renderer.hpp"
#include <filesystem>
#include <string>

namespace taixu::editor {

struct ViewModel {
    std::filesystem::path _project_path;
    std::filesystem::path _dir_path;

    ImGuizmo::MODE      _guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION _guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    Entity _selected_entity{0};

    Engine           *_engine_runtime_ptr{nullptr};
    AbstractRenderer *_renderer{nullptr};

    IFrameBuffer *_framebuffer{nullptr};
};

}// namespace taixu::editor

#endif//TAIXUENGINE_VIEW_MODEL_HPP
