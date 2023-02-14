function(transform_shader SHADERS TARGET_NAME SHADER_INCLUDE_FOLDER GENERATED_DIR)

    set(working_dir "${CMAKE_CURRENT_SOURCE_DIR}")

    set(ALL_GENERATED_CPP_FILES "")

    foreach (SHADER ${SHADERS})
        # Prepare a header name and a global variable for this shader
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        string(REPLACE "." "_" HEADER_NAME ${SHADER_NAME})
        string(TOUPPER ${HEADER_NAME} GLOBAL_SHADER_VAR)

        set(CPP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_DIR}/cpp/${HEADER_NAME}.h")

        add_custom_command(
                OUTPUT ${CPP_FILE}
                COMMAND ${CMAKE_COMMAND} -DPATH=${SHADER} -DHEADER="${CPP_FILE}"
                -DGLOBAL="${GLOBAL_SHADER_VAR}" -P "${PROJECT_SOURCE_DIR}/cmake/GenerateShaderSourceCPPFile.cmake"
                DEPENDS ${SHADER}
                WORKING_DIRECTORY "${working_dir}")

        list(APPEND ALL_GENERATED_CPP_FILES ${CPP_FILE})

    endforeach ()

    add_custom_target(${TARGET_NAME}
            DEPENDS ${ALL_GENERATED_CPP_FILES} SOURCES ${SHADERS})

endfunction()