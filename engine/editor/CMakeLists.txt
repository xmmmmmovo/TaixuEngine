file(GLOB_RECURSE EDITOR_SOURCES "*.hpp" "*.cpp")

add_executable(editor ${EDITOR_SOURCES})

target_link_libraries(editor Vulkan::Vulkan glm glfw)