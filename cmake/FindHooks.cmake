# Pre-commit hooks
IF(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/.git/hooks/pre-commit)
    message(STATUS "Installing pre-commit hooks")

    # FIND_PACKAGE(Python3 COMPONENTS Interpreter Development)
    IF(POLICY CMP0094) # https://cmake.org/cmake/help/latest/policy/CMP0094.html
        CMAKE_POLICY(SET CMP0094 NEW) # FindPython should return the first matching Python
    ENDIF()

    # needed on GitHub Actions CI: actions/setup-python does not touch registry/frameworks on Windows/macOS
    # this mirrors PythonInterp behavior which did not consult registry/frameworks first
    IF(NOT DEFINED Python_FIND_REGISTRY)
        SET(Python_FIND_REGISTRY "LAST")
    ENDIF()

    IF(NOT DEFINED Python_FIND_FRAMEWORK)
        SET(Python_FIND_FRAMEWORK "LAST")
    ENDIF()

    FIND_PACKAGE(Python REQUIRED COMPONENTS Interpreter)
    MESSAGE(STATUS "Python executable: ${Python_EXECUTABLE}")

    set(HOOK_INSTALL_PACKAGE pre-commit)

    # Find clang-format executable
    FIND_PROGRAM(CLANG_FORMAT_EXECUTABLE clang-format)

    IF(CLANG_FORMAT_EXECUTABLE)
        MESSAGE(STATUS "clang-format executable: ${CLANG_FORMAT_EXECUTABLE}")
    ELSE()
        MESSAGE(WARNING "clang-format executable not found, need install")
        SET(HOOK_INSTALL_PACKAGE ${HOOK_INSTALL_PACKAGE} clang-format)
    ENDIF()

    set(APPLE_BREW_PIP_PARAM "")

    if(APPLE)
        set(APPLE_BREW_PIP_PARAM "--break-system-packages")
    endif()

    EXECUTE_PROCESS(COMMAND ${Python_EXECUTABLE} -m pip install ${APPLE_BREW_PIP_PARAM} ${HOOK_INSTALL_PACKAGE})
    EXECUTE_PROCESS(COMMAND pre-commit install WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF()
