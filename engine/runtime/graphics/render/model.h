#pragma once

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "mesh.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace taixu::cg {
class Model {
public:
    // model data
    std::vector<Texture>
            textures_loaded;// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string       directory;
    bool              gammaCorrection;
    Model(std::string const &path, bool gamma = false) { loadModel(path); }

    // draws the model, and thus all its meshes
    void Draw() {}

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void                 loadModel(std::string const &path);
    void                 processNode(aiNode *node, const aiScene *scene);
    Mesh                 processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial   *mat,
                                              aiTextureType type,
                                              std::string   typeName);

    unsigned int TextureFromFile(const char *path, const std::string &directory,
                                 bool gamma);
};

}// namespace taixu::cg