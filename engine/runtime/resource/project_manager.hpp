//
// Created by xmmmmmovo on 2023/2/19.
//

#include "core/base/macro.hpp"

#include <string>

#ifndef TAIXUENGINE_PROJECT_MANAGER_HPP
#define TAIXUENGINE_PROJECT_MANAGER_HPP

namespace taixu {

struct Project;

class ProjectManager {
public:
    // 
    void openProject(std::string const &path);

private:
    //TODO: Implement asset class in the future

    class assetManager;
};

}// namespace taixu

#endif//TAIXUENGINE_PROJECT_MANAGER_HPP
