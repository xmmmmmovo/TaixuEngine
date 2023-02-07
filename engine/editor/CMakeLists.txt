file(GLOB_RECURSE EDITOR_SOURCES "*.hpp" "*.cpp")

add_executable(TaixuEngineEditor ${EDITOR_SOURCES})
GroupSourcesByFolder(TaixuEngineEditor)

target_link_libraries(TaixuEngineEditor Vulkan::Vulkan glm glfw imgui)