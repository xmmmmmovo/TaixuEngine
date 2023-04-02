//
// Created by xmmmmmovo on 2023/2/25.
//Written by JoeEsong on 2023/4/3
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "graphics/render/vertex_array.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"
#include "resource/asset_manager.hpp"
#include <sstream>
TEST_CASE("noncopyable") {
    //    taixu::Asset_Manager manager{};
    //    manager.loadAsset("assets/asset.json");
    //    manager.writeAsset();
    // 创建测试数据
    taixu::AssetManager manager;
    manager.loadAsset("models/test_model.obj", taixu::AssetType::MODEL);
    manager.loadAsset("textures/test_texture.png", taixu::AssetType::TEXTURE);

    // 执行函数
    std::string file_path   = "test.json";
    manager.asset_file_path = file_path;
    manager.writeAsset();

    // 读取生成的JSON文件
    std::ifstream     i(file_path);
    std::stringstream buffer{};
    buffer << i.rdbuf();
    std::string json_str = buffer.str();
    i.close();
    // 检查生成的JSON文件是否正确
    std::stringstream ss;
    ss << "{\"assets\":[{\"guid\":\"" << manager.asset_list[0].guid
       << "\",\"name\":\"" << manager.asset_list[0].name << "\",\"location\":\""
       << manager.asset_list[0].location << "\",\"type\":\""
       << manager.asset_list[0].type << "\"},{\"guid\":\""
       << manager.asset_list[1].guid << "\",\"name\":\""
       << manager.asset_list[1].name << "\",\"location\":\""
       << manager.asset_list[1].location << "\",\"type\":\""
       << manager.asset_list[1].type << "\"}]}";
    std::string result = ss.str();
    
    REQUIRE(json_str == result);
}