//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP


#include "common/math/vec.hpp"

#include <optional>
#include <vector>


namespace taixu {

struct Material final {
    Vec3  diffuse{};
    Vec3  specular{};
    Vec3  ambient{};
    Vec3  emissive{};
    float opacity{1.0f};
    float refracti{1.0f};
    float shininess{32.0f};
    float strength{1.0f};

    int wireframe{0};
    int twosided{0};
};

enum class MeshType { TRIANGLE, QUAD, POINT };

struct Mesh final {
    std::vector<Vec3> vertices;

    std::vector<Vec3> normals;
    std::vector<Vec2> tex_coords;

    std::vector<Vec3> tangents;
    std::vector<Vec3> bitangents;

    std::vector<std::uint32_t> indices;

    std::optional<std::uint32_t> material_id{std::nullopt};
};

}// namespace taixu

#endif// TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
