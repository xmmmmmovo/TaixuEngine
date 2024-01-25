//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_MESH_HPP
#define TAIXUENGINE_MESH_HPP

#include "glm/glm.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

#include "material.hpp"
#include "raw_data.hpp"

namespace taixu {

enum class MeshType { TRIANGLE, QUAD, POINT };

struct Mesh final {
    std::vector<glm::vec3> vertices;

    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    std::vector<std::uint32_t> indices;

    std::optional<std::uint32_t> material_id{std::nullopt};
};

}// namespace taixu

#endif// TAIXUENGINE_MESH_HPP
