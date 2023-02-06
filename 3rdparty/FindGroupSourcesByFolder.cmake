if(NOT GroupSourcesByFolder_ADDED)
    # Source file grouping of visual studio and xcode
    CPMAddPackage(
        NAME GroupSourcesByFolder
        GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
        VERSION 1.0
    ) 
endif()
