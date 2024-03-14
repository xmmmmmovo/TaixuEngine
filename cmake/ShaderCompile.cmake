function(compile_glsl_shader SHADERS TARGET_NAME SHADER_INCLUDE_FOLDER GENERATED_DIR GLSLANG_BIN PLATFORM ARGS)

    set(working_dir "${CMAKE_CURRENT_SOURCE_DIR}")

    set(ALL_GENERATED_SPV_FILES "")
    set(ALL_GENERATED_CPP_FILES "")

    if (UNIX)
        execute_process(COMMAND chmod a+x ${GLSLANG_BIN})
    endif ()

    foreach (SHADER ${SHADERS})
        # Prepare a header name and a global variable for this shader
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        string(REPLACE "." "_" HEADER_NAME ${SHADER_NAME})
        string(TOUPPER ${HEADER_NAME} GLOBAL_SHADER_VAR)

        string(TOUPPER ${PLATFORM} PLATFORM_UPPER)

        set(SPV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}/spv/${PLATFORM}_${SHADER_NAME}.spv")
        set(CPP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}/cpp/${HEADER_NAME}_${PLATFORM}.h")

        add_custom_command(
                OUTPUT ${SPV_FILE}
                COMMAND ${GLSLANG_BIN} -I${SHADER_INCLUDE_FOLDER} ${ARGS} -o ${SPV_FILE} ${SHADER}
                DEPENDS ${SHADER}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_SPV_FILES ${SPV_FILE})

        add_custom_command(
                OUTPUT ${CPP_FILE}
                COMMAND ${CMAKE_COMMAND} -DPATH=${SPV_FILE} -DHEADER="${CPP_FILE}"
                -DGLOBAL="${GLOBAL_SHADER_VAR}_${PLATFORM_UPPER}" -P "${PROJECT_SOURCE_DIR}/cmake/GenerateShaderCPPFile.cmake"
                DEPENDS ${SPV_FILE}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach ()

    add_custom_target(${TARGET_NAME}
            DEPENDS ${ALL_GENERATED_SPV_FILES} ${ALL_GENERATED_CPP_FILES} SOURCES ${SHADERS})

endfunction()

function(compile_hlsl_shader SHADERS TARGET_NAME GENERATED_DIR FXC_BIN DEBUG PLATFORM ARGS)

    set(working_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(generated_path "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}")

    set(ALL_GENERATED_CPP_FILES "")

    foreach (SHADER ${SHADERS})
        # if use hlsli, continue
        get_filename_component(SHADER_EXT ${SHADER} LAST_EXT)
        if (NOT SHADER_EXT STREQUAL ".hlsl")
            continue()
        endif ()

        # Prepare a header name and a global variable for this shader
        get_filename_component(SHADER_NAME ${SHADER} NAME_WLE)
        get_filename_component(SHADER_TYPE ${SHADER_NAME} EXT)

        string(REPLACE "." "_" HEADER_NAME ${SHADER_NAME})
        string(TOUPPER ${HEADER_NAME} GLOBAL_SHADER_VAR)

        string(TOUPPER ${PLATFORM} PLATFORM_UPPER)

        set(HEADER_FILE_NAME "${HEADER_NAME}_${PLATFORM}.hpp")
        if (DEBUG)
            set(HEADER_FILE_NAME "${HEADER_NAME}_${PLATFORM}_d.hpp")
        endif ()

        set(CPP_FILE "${generated_path}/cpp/${HEADER_FILE_NAME}")

        set(ENTRY_POINT "${HEADER_NAME}_main")
        # get type
        if (SHADER_TYPE STREQUAL ".vert")
            set(SHADER_TYPE "vs_5_0")
        elseif (SHADER_TYPE STREQUAL ".frag")
            set(SHADER_TYPE "ps_5_0")
        elseif (SHADER_TYPE STREQUAL ".comp")
            set(SHADER_TYPE "cs_5_0")
        elseif (SHADER_TYPE STREQUAL ".hull")
            set(SHADER_TYPE "hs_5_0")
        elseif (SHADER_TYPE STREQUAL ".dom")
            set(SHADER_TYPE "ds_5_0")
        elseif (SHADER_TYPE STREQUAL ".geom")
            set(SHADER_TYPE "gs_5_0")
        else ()
            message(FATAL_ERROR "Unknown shader type ${SHADER_TYPE}")
        endif ()

        add_custom_command(
                OUTPUT ${CPP_FILE}
                COMMAND ${FXC_BIN} ${ARGS} /E ${ENTRY_POINT} /T ${SHADER_TYPE} /Vn ${GLOBAL_SHADER_VAR}_DX11 /Fh ${CPP_FILE} ${SHADER}
                DEPENDS ${SHADER}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach ()

    add_custom_target(${TARGET_NAME}
            DEPENDS ${ALL_GENERATED_CPP_FILES} SOURCES ${SHADERS})


endfunction()