/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "dialog_helper.hpp"

namespace taixu::editor {

void openFileDialog(std::string_view const& key, IGFD::FileDialogConfig const& config) {
    ImGuiFileDialog::Instance()->OpenDialog(key.data(), "Choose a Directory", nullptr, config);
}

void displayAndProcessFileDialog(std::string_view const& key, ViewModel& view_model, const Callbacks callback_key) {
    if (ImGuiFileDialog::Instance()->Display(key.data())) {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string file_path = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            DEBUG_LOG("Select path: {}", file_path);
            invokeCallback(callback_key, file_path, view_model);
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}

}// namespace taixu::editor
