#pragma once

#include <glad/glad.h>

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "texture.hpp"
namespace taixu {
class Model_Data {
public:
    // model data
    std::vector<Texture>
            textures_loaded;// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string       directory;
    bool              gammaCorrection;
    Model_Data(std::string const &path, bool gamma = false) { loadModel(path); }
    void loadModel(std::string const &path);
    // draws the model, and thus all its meshes
    void Draw() {}

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.

    void                 processNode(aiNode *node, const aiScene *scene);
    Mesh                 processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial   *mat,
                                              aiTextureType type,
                                              std::string   typeName);

    //unsigned int TextureFromFile(const char *path, const std::string &directory,
                                 //bool gamma);
};

}// namespace taixu