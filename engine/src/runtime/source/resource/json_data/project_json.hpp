//
// Created by xmmmmmovo on 2023/7/23.
//

#pragma once

#include <vector>

#include "common/hal/tx_container.hpp"
#include "common/hal/tx_string.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

struct TextureJson {
    tx_string texture_name{};
    tx_string texture_path{};
};

struct SkyboxSpecularJson {
    tx_string negx_path{};
    tx_string negy_path{};
    tx_string negz_path{};
    tx_string posx_path{};
    tx_string posy_path{};
    tx_string posz_path{};
};

struct GlobalJson {
    tx_vector<TextureJson> textures{};
    SkyboxSpecularJson     skybox_specular{};
};

struct TransformComponent {
    std::array<float, 3> position{};
    std::array<float, 4> rotation{};
    std::array<float, 3> scale{};
};

struct ComponentsJson {
    TransformComponent transform;
};

struct GOJson {
    ComponentsJson components;
};

struct GOInfoJson {
    tx_string GO_path{};
    tx_string GO_name{};
};

struct SceneJson {
    tx_string               name{};
    GlobalJson              global{};
    std::vector<GOInfoJson> gos{};
};

TX_NAMESPACE_END
