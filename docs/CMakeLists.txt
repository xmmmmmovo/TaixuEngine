cmake_minimum_required(VERSION 3.20)

# ---- Doxygen variables ----

# set Doxyfile variables
set(DOXYGEN_PROJECT_NAME TaixuEngine)
set(DOXYGEN_PROJECT_VERSION ${ENGINE_VERSION})
set(DOXYGEN_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")

configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

find_program(doxygen_exec doxygen)

add_custom_target(
        TaixuApiDocs
        ${CMAKE_COMMAND} -E make_directory "${DOXYGEN_OUTPUT_DIRECTORY}"
        COMMAND "${doxygen_exec}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        COMMAND echo "Docs written to: ${DOXYGEN_OUTPUT_DIRECTORY}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
