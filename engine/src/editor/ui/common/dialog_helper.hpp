/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <imgui/file_dialog/ImGuiFileDialog.h>

#include "taixu/platform/os/path_utils.hpp"

#include "editor_context.hpp"
#include "view_model.hpp"

namespace taixu::editor {

static const IGFD::FileDialogConfig DIRECTORY_CONFIG{.path              = getRootPath().generic_string(),
                                                     .countSelectionMax = 1,
                                                     .flags             = ImGuiFileDialogFlags_Modal};


void openFileDialog(std::string_view const& key, IGFD::FileDialogConfig const& config);

void displayAndProcessFileDialog(std::string_view const& key, ViewModel& view_model, Callbacks callback_key);

}// namespace taixu::editor
