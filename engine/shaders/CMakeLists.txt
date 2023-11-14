set(TARGET_NAME ${SHADER_COMPILE_TARGET})

macro(GET_SHADER_FILES varname relpath)
    file(GLOB_RECURSE ${varname} CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.vert"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.frag"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.comp"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.geom"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.tesc"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.tese"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.mesh"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.task"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.rgen"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.rchit"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.rmiss"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.rcall"
    )
endmacro()

macro(FIND_GLSL platform suffix args)
    GET_SHADER_FILES(${platform}_SHADER_FILES "glsl/${platform}")
    SOURCE_GROUP("shaders_${suffix}" FILES ${${platform}_SHADER_FILES})
    string(TOUPPER ${suffix} suffix_upper)

    compile_shader(
            "${${platform}_SHADER_FILES}"
            "${TARGET_NAME}_${suffix_upper}"
            "${GLSL_INCLUDE_FOLDER}"
            "${GENERATED_SHADER_FOLDER}"
            "${GLSL_COMPILER}"
            "${suffix}"
            "${args}"
    )

    set_target_properties("${TARGET_NAME}_${suffix_upper}" PROPERTIES FOLDER "EngineShader")
endmacro()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
endif ()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
endif ()
include(${PROJECT_SOURCE_DIR}/cmake/ShaderCompile.cmake)

set(GLSL_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/glsl/include)
set(GENERATED_SHADER_FOLDER "generated")

if (USE_VULKAN)
    FIND_GLSL(vulkan vk "-V100")
endif ()
