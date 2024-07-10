set(TARGET_NAME ${SHADER_COMPILE_TARGET})

macro(GET_GLSL_SHADER_FILES varname relpath)
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

macro(GET_HLSL_SHADER_FILES varname relpath)
    file(GLOB_RECURSE ${varname} CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.hlsli"
            "${CMAKE_CURRENT_SOURCE_DIR}/${relpath}/*.hlsl"
    )
endmacro()

macro(FIND_GLSL platform suffix args)
    GET_GLSL_SHADER_FILES(${platform}_SHADER_FILES "glsl/${platform}")
    SOURCE_GROUP("shaders_${suffix}" FILES ${${platform}_SHADER_FILES})
    string(TOUPPER ${suffix} suffix_upper)

    compile_glsl_shader(
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

macro(FIND_HLSL platform suffix debug args)
    GET_HLSL_SHADER_FILES(${platform}_SHADER_FILES "hlsl/${platform}")
    SOURCE_GROUP("shaders_${suffix}" FILES ${${platform}_SHADER_FILES})
    string(TOUPPER ${suffix} suffix_upper)

    compile_hlsl_shader(
            "${${platform}_SHADER_FILES}"
            "${TARGET_NAME}_${suffix_upper}"
            "${GENERATED_SHADER_FOLDER}"
            "${HLSL_COMPILER}"
            ${debug}
            "${suffix}"
            ${args}
    )

    set_target_properties("${TARGET_NAME}_${suffix_upper}" PROPERTIES FOLDER "EngineShader")
endmacro()

# shaders
# add glsl compiler
if (USE_VULKAN)
    set(GLSLANG_VALIDATOR_EXECUTABLE ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})
    if (NOT GLSLANG_VALIDATOR_EXECUTABLE)
        find_program(GLSLC_EXECUTABLE glslc
                PATHS "${TAIXUENGINE_ROOT_DIR}/3rd_party/bin")
        if (NOT GLSLC_EXECUTABLE)
            message(FATAL_ERROR "glsl compiler not found!")
        else ()
            message("glsl ${GLSLC_EXECUTABLE}")
            set(GLSL_COMPILER ${GLSLC_EXECUTABLE})
        endif ()
    else ()
        message("glsl ${GLSLANG_VALIDATOR_EXECUTABLE}")
        set(GLSL_COMPILER ${GLSLANG_VALIDATOR_EXECUTABLE})
    endif ()
endif ()

if(USE_HLSL)
    find_program(FXC_EXECUTABLE fxc
            PATHS "${TAIXUENGINE_ROOT_DIR}/3rdparty/bin/fxc"
            DOC "The DirectX shader compiler"
    )
    if (NOT FXC_EXECUTABLE)
        message(FATAL_ERROR "fxc compiler not found!")
    else ()
        set(HLSL_COMPILER ${FXC_EXECUTABLE})
        message("fxc ${FXC_EXECUTABLE}")
    endif ()
endif ()

set(GLSL_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/glsl/include)
set(GENERATED_SHADER_FOLDER "generated")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
endif ()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
endif ()
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/cpp)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/cpp)
endif ()

include(ShaderCompile)

if (USE_VULKAN)
    FIND_GLSL(vulkan vk "-V100")
endif ()

if(USE_HLSL)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        FIND_HLSL(dx11 dx11 TRUE /Zi /Od /nologo)
    else ()
        FIND_HLSL(dx11 dx11 FALSE /O3 /nologo /WX)
    endif ()
endif ()