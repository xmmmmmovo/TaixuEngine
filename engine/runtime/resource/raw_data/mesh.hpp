//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_MESH_HPP
#define TAIXUENGINE_MESH_HPP

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "asset_data.hpp"

namespace taixu {

struct Mesh final : public BaseAssetData {
    std::vector<glm::vec3> vertices;

    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    std::vector<unsigned int> indices;
};

}// namespace taixu

#endif//TAIXUENGINE_MESH_HPP
