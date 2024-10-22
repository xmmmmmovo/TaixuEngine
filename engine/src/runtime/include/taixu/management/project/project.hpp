/**
 * @file project.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-10-20
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <filesystem>

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class ProjectRaw {
public:
    std::filesystem::path project_path;
};

class Project {
public:
    ProjectRaw raw;
};

TX_NAMESPACE_END
