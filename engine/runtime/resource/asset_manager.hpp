//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <filesystem>
#include <spdlog/spdlog.h>

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "management/ecs/guid_genenrator.hpp"
#include "platform/os/path.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

class AssetManager {
    using TextureMapType = std::unordered_map<std::string, Texture>;
    PROTOTYPE_ONLY_GETTER(private, TextureMapType, textures);
    using MeshMapType = std::unordered_map<std::string, Mesh>;
    PROTOTYPE_ONLY_GETTER(private, MeshMapType, meshes);

public:
    void loadAsset(std::filesystem::path const &file_path);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
