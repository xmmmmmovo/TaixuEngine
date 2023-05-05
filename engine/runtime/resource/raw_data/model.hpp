//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP

#include "mesh.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"
#include "resource/raw_data/asset_data.hpp"

#include <cstdint>
#include <vector>


namespace taixu {

struct Model final : public BaseAssetData {
    std::vector<Mesh>     meshes;
    std::vector<Material> materials;
};

struct ModelGPU final {
    std::unique_ptr<IVertexArray> vao;
    std::uint32_t                 index_count{};
    std::optional<std::uint32_t>  mat_index{};
};

inline std::vector<ModelGPU> transferCPUModel2GPU(Model const *model) {
    std::vector<ModelGPU> ret{};
    ret.reserve(model->meshes.size());

    for (auto const &mesh : model->meshes) {
        ModelGPU model_gpu{};

        if (EngineArgs::getInstance().api == GraphicsAPI::OPENGL) {
            auto vao = std::make_unique<OGLVertexArray>();

            vao->bind();
            vao->addVBO(OGLVertexBuffer{mesh.vertices.size(),
                                        &mesh.vertices.front(), GL_STATIC_DRAW,
                                        3});

            if (!mesh.normals.empty()) {
                vao->addVBO(OGLVertexBuffer{mesh.normals.size(),
                                            &mesh.normals.front(),
                                            GL_STATIC_DRAW, 3});
            }

            if (!mesh.tex_coords.empty()) {
                vao->addVBO(OGLVertexBuffer{mesh.tex_coords.size(),
                                            &mesh.tex_coords.front(),
                                            GL_STATIC_DRAW, 2});
            }

            if (!mesh.tangents.empty()) {
                vao->addVBO(OGLVertexBuffer{mesh.tangents.size(),
                                            &mesh.tangents.front(),
                                            GL_STATIC_DRAW, 3});
                vao->addVBO(OGLVertexBuffer{mesh.bitangents.size(),
                                            &mesh.bitangents.front(),
                                            GL_STATIC_DRAW, 3});
            }

            vao->setEBO(OGLElementBuffer{mesh.indices, GL_STATIC_DRAW});

            vao->unbind();
            model_gpu.vao = std::move(vao);
        }

        model_gpu.index_count = mesh.indices.size();
        model_gpu.mat_index   = mesh.material_id;

        ret.push_back(std::move(model_gpu));
    }

    return ret;
}

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
