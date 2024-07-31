/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include "editor_context.hpp"
#include "imgui/file_dialog/ImGuiFileDialog.h"
#include "platform/os/path.hpp"
#include "view_model.hpp"

namespace taixu::editor {

static const IGFD::FileDialogConfig DIRECTORY_CONFIG{.path = getRootPath().generic_string(),
                                                     .countSelectionMax = 1,
                                                     .flags = ImGuiFileDialogFlags_Modal};


void openFileDialog(tx_string_view const& key, IGFD::FileDialogConfig const& config);

void displayAndProcessFileDialog(tx_string_view const& key, ViewModel& view_model,
                                 Callbacks callback_key);

}// namespace taixu::editor
