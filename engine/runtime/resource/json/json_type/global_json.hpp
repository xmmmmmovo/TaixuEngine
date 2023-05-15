//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_RESOURCE_JSON_JSON_TYPE_GLOBAL_JSON_HPP
#define ENGINE_RUNTIME_RESOURCE_JSON_JSON_TYPE_GLOBAL_JSON_HPP

#include <string>
namespace taixu {

class RenderGlobalJson {
public:
    std::filesystem::path posx;
    std::filesystem::path negx;
    std::filesystem::path posy;
    std::filesystem::path negy;
    std::filesystem::path posz;
    std::filesystem::path negz;
};

class GlobalJson {
public:
    RenderGlobalJson render_global_json;

    std::filesystem::path render_global_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};

    void serialize()
    {
        if(render_global_path!="INVALID")
        {
            std::ofstream o(project_file_path / render_global_path);
            json j;
            j = nlohmann::json{{"posx", "assets/textures/skybox/split_skybox_sky_cloud/right.png"},
                                {"negx", "assets/textures/skybox/split_skybox_sky_cloud/left.png"},
                                {"posy", "assets/textures/skybox/split_skybox_sky_cloud/top.png"},
                                {"negy", "assets/textures/skybox/split_skybox_sky_cloud/bottom.png"},
                                {"posz", "assets/textures/skybox/split_skybox_sky_cloud/front.png"},
                                {"negz", "assets/textures/skybox/split_skybox_sky_cloud/back.png"}
                                };
            json write;
            write["skybox_specular"] = j;
            o << std::setw(4) << write;
            o.close();
        }
        
    }

    void deserialize() {
        std::ifstream f(project_file_path / render_global_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        }

        json data = json::parse(f);

        auto const &skybox_spec = data["skybox_specular"];

        render_global_json.posx =
                skybox_spec["posx"].get<std::filesystem::path>();
        render_global_json.negx =
                skybox_spec["negx"].get<std::filesystem::path>();
        render_global_json.posy =
                skybox_spec["posy"].get<std::filesystem::path>();
        render_global_json.negy =
                skybox_spec["negy"].get<std::filesystem::path>();
        render_global_json.posz =
                skybox_spec["posz"].get<std::filesystem::path>();
        render_global_json.negz =
                skybox_spec["negz"].get<std::filesystem::path>();
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_JSON_JSON_TYPE_GLOBAL_JSON_HPP
