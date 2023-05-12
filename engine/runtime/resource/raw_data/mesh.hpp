//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_MESH_HPP
#define TAIXUENGINE_MESH_HPP

#include <cstddef>
#include <cstdint>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "asset_data.hpp"
#include "management/graphics/render/vertex_array.hpp"
#include "material.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"

namespace taixu {

struct MeshGPU final {
    std::unique_ptr<IVertexArray> vao;
    std::uint32_t                 index_count{};
    std::optional<std::uint32_t>  mat_index{};
};

struct Mesh final {
    std::vector<glm::vec3> vertices;

    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    std::vector<std::uint32_t> indices;

    std::optional<std::uint32_t> material_id{std::nullopt};
};

inline MeshGPU transferCPUMesh2GPU(Mesh const &mesh) {
    MeshGPU mesh_gpu{};

    if (EngineArgs::getInstance().api == GraphicsAPI::OPENGL) {
        auto vao = std::make_unique<OGLVertexArray>();

        vao->bind();
        vao->addVBO(OGLVertexBuffer{mesh.vertices.size(),
                                    &mesh.vertices.front(), GL_STATIC_DRAW, 3});
        
        if (!mesh.normals.empty()) {
            vao->addVBO(OGLVertexBuffer{mesh.normals.size(),
                                        &mesh.normals.front(), GL_STATIC_DRAW,
                                        3});
        }

        if (!mesh.tex_coords.empty()) {
            vao->addVBO(OGLVertexBuffer{mesh.tex_coords.size(),
                                        &mesh.tex_coords.front(),
                                        GL_STATIC_DRAW, 2});
        }

        if (!mesh.tangents.empty()) {
            vao->addVBO(OGLVertexBuffer{mesh.tangents.size(),
                                        &mesh.tangents.front(), GL_STATIC_DRAW,
                                        3});
            vao->addVBO(OGLVertexBuffer{mesh.bitangents.size(),
                                        &mesh.bitangents.front(),
                                        GL_STATIC_DRAW, 3});
        }

        vao->setEBO(OGLElementBuffer{mesh.indices, GL_STATIC_DRAW});

        vao->unbind();
        mesh_gpu.vao = std::move(vao);
    }

    mesh_gpu.index_count = mesh.indices.size();
    mesh_gpu.mat_index   = mesh.material_id;

    return mesh_gpu;
}


}// namespace taixu

#endif//TAIXUENGINE_MESH_HPP
