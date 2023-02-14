####################################################################################################
# This function converts any file into C/C++ source code.
# Example:
# - input file: data.glsl
# - output file: data.h
# - variable name declared in output file: DATA
# - data length: sizeof(DATA)
# embed_resource("data.glsl" "data.h" "DATA")
####################################################################################################
function(embed_resource resource_file_name source_file_name variable_name)
    if(EXISTS "${source_file_name}")
        if("${source_file_name}" IS_NEWER_THAN "${resource_file_name}")
            return()
        endif()
    endif()

    if(EXISTS "${resource_file_name}")
        file(READ "${resource_file_name}" char_content)

        string(REPLACE "\n" "\\n" output ${char_content})

        set(array_definition "static constexpr char ${variable_name}[] =\"${output}\";")

        message(${source_file_name})
        get_filename_component(file_name ${source_file_name} NAME)
        set(source "/**\n * @file ${file_name}\n * @brief Auto generated file.\n */\n${array_definition}\n")

        file(WRITE "${source_file_name}" "${source}")
    else()
        message("ERROR: ${resource_file_name} doesn't exist")
        return()
    endif()

endfunction()

# let's use it as a script
if(EXISTS "${PATH}")
    embed_resource("${PATH}" "${HEADER}" "${GLOBAL}")
endif()
