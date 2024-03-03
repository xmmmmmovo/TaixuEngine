/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include "editor_context.hpp"
#include "imgui/file_dialog/ImGuiFileDialog.h"
#include "platform/os/path.hpp"

namespace taixu::editor {

static const IGFD::FileDialogConfig DIRECTORY_CONFIG{
        .path              = getRootPath().generic_string(),
        .countSelectionMax = 1,
        .flags             = ImGuiFileDialogFlags_Modal};


void openFileDialog(std::string_view const&       key,
                    IGFD::FileDialogConfig const& config);

void displayAndProcessFileDialog(std::string_view const& key,
                                 EnumCallbacks           callback_key);

}// namespace taixu::editor