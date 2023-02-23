//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_TEXTURE_HPP
#define TAIXUENGINE_TEXTURE_HPP
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <stb_image.h>

#include"graphics/render/mesh.hpp"
namespace taixu 
{
class Texture_Data
{
public:
    unsigned int id;
    std::string  type;
    std::string  path;
    //for call of model 
    unsigned int TextureFromFile(const char        *path,
                                          const std::string &directory,
                                          bool               gamma);
    //TODO::if we know the definite path
    unsigned int TextureFromFile(std::string file_path,bool gamma);

};

}

#endif//TAIXUENGINE_TEXTURE_HPP
