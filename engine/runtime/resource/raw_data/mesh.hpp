//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_MESH_HPP
#define TAIXUENGINE_MESH_HPP

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "asset_data.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

struct Mesh final {
    std::vector<glm::vec3> vertices;

    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    std::vector<unsigned int> indices;

    std::optional<Texture *> diffuse_map;
};

}// namespace taixu

#endif//TAIXUENGINE_MESH_HPP
