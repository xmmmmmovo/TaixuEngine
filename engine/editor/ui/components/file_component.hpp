//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include <filesystem>
#include <string>
#include <vector>

#include<spdlog/spdlog.h>
#include "interface/component.hpp"

namespace taixu::editor {
static const std::filesystem::path s_AssetPath = "E:/TP/TaixuEngine/engine/assets";
class FileComponent : public IUIComponent {
private:
    std::vector<std::string_view> file_tree;
    static ImGuiWindowFlags constexpr window_flags =
            ImGuiWindowFlags_HorizontalScrollbar;

    std::filesystem::path m_CurrentDirectory = s_AssetPath;

public:
    void init() override {}
    void update() override {
        { 

            ImGui::BeginChild("FileTree",ImVec2(ImGui::GetWindowContentRegionWidth() * 0.2f, 0.f),false, window_flags);
            for (int i = 0; i < 100; i++)
                ImGui::Text("%04d: scrollable region", i);
            ImGui::EndChild();
        }
        // Child 1: no border, enable horizontal scrollbar

        ImGui::SameLine();
        // Child 2: rounded border
        {
            ImGui::BeginChild("ChildR", ImVec2(0, 260), false, window_flags);
            
            if (m_CurrentDirectory != std::filesystem::path(s_AssetPath)) {
                if (ImGui::Button("<-")) {
                    m_CurrentDirectory = m_CurrentDirectory.parent_path();
                }
            }

            static float padding       = 16.0f;
            static float thumbnailSize = 128.0f;
            float        cellSize      = thumbnailSize + padding;

            float panelWidth  = ImGui::GetContentRegionAvail().x;
            int   columnCount = (int) (panelWidth / cellSize);
            if (columnCount < 1) columnCount = 1;

            if (ImGui::BeginTable("split", columnCount,ImGuiTableFlags_Resizable |ImGuiTableFlags_NoSavedSettings)) 
            {              
                for (auto& directoryEntry :std::filesystem::directory_iterator(m_CurrentDirectory)) 
                {
                    const auto& path = directoryEntry.path();
                    auto        relativePath = std::filesystem::relative(path, s_AssetPath);
                    std::string filenameString = relativePath.filename().string();
                    
                    ImGui::Button(filenameString.c_str(),
                                  {thumbnailSize, thumbnailSize});
                    if (ImGui::IsItemHovered() &&ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        if (directoryEntry.is_directory())
                            m_CurrentDirectory /= path.filename();
                    }
                    ImGui::TextWrapped(filenameString.c_str());
                    ImGui::TableNextColumn();
                }
                ImGui::EndTable();
            }

            ImGui::Columns(1);

            ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
            ImGui::SliderFloat("Padding", &padding, 0, 32);
            ImGui::EndChild();
        }
        /*ImGui::Begin("Content Browser");
        static float padding       = 16.0f;
        static float thumbnailSize = 128.0f;
        float        cellSize      = thumbnailSize + padding;

        float panelWidth  = ImGui::GetContentRegionAvail().x;
        int   columnCount = (int) (panelWidth / cellSize);
        if (columnCount < 1) columnCount = 1;

        ImGui::Columns(columnCount, 0, false);
        ImGui::Button("chennuo", {thumbnailSize, thumbnailSize});
        ImGui::Text("chennuo");

        ImGui::Columns(1);

        ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
        ImGui::SliderFloat("Padding", &padding, 0, 32);

        ImGui::End;*/
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_FILE_COMPONENT_HPP
