cmake_minimum_required(VERSION 3.20)

project(TaixuApiDocs)

include(../cmake/CPM.cmake)

CPMAddPackage("gh:mosra/m.css#a0d292ec311b97fefd21e93cdefb60f88d19ede6")

# ---- Doxygen variables ----

# set Doxyfile variables
set(DOXYGEN_PROJECT_NAME TaixuEngine)
set(DOXYGEN_PROJECT_VERSION ${ENGINE_VERSION})
set(DOXYGEN_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")

configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${CMAKE_CURRENT_LIST_DIR}/conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/conf.py)

add_custom_target(
        TaixuApiDocs
        ${CMAKE_COMMAND} -E make_directory "${DOXYGEN_OUTPUT_DIRECTORY}"
        COMMAND "${m.css_SOURCE_DIR}/documentation/doxygen.py" "${CMAKE_CURRENT_BINARY_DIR}/conf.py"
        COMMAND echo "Docs written to: ${DOXYGEN_OUTPUT_DIRECTORY}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)