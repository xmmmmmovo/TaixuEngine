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
                -DGLOBAL= "${GLOBAL_SHADER_VAR}_${PLATFORM_UPPER}" -P "${PROJECT_SOURCE_DIR}/cmake/GenerateShaderCPPFile.cmake"
                DEPENDS ${SPV_FILE}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach ()

    add_custom_target(${TARGET_NAME}
            DEPENDS ${ALL_GENERATED_SPV_FILES} ${ALL_GENERATED_CPP_FILES} SOURCES ${SHADERS})

endfunction()

function(compile_hlsl_shader SHADERS TARGET_NAME SHADER_INCLUDE_FILES GENERATED_DIR FXC_BIN ARGS)

    set(working_dir "${CMAKE_CURRENT_SOURCE_DIR}")

    set(ALL_GENERATED_SPV_FILES "")
    set(ALL_GENERATED_CPP_FILES "")

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
                -DGLOBAL= "${GLOBAL_SHADER_VAR}_${PLATFORM_UPPER}" -P "${PROJECT_SOURCE_DIR}/cmake/GenerateShaderCPPFile.cmake"
                DEPENDS ${SPV_FILE}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach ()

    add_custom_target(${TARGET_NAME}
            DEPENDS ${ALL_GENERATED_SPV_FILES} ${ALL_GENERATED_CPP_FILES} SOURCES ${SHADERS})


endfunction()