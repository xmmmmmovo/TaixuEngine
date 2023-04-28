//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include <filesystem>
#include <string>

namespace taixu::editor {

struct ViewModel {
    std::filesystem::path _project_path;
    std::filesystem::path _dir_path;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_VIEW_MODEL_HPP
