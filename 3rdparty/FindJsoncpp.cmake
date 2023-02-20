# jsoncpp
#CPMAddPackage(
#        NAME jsoncpp
#        GITHUB_REPOSITORY open-source-parsers/jsoncpp
#        GIT_TAG 1.9.5
#        OPTIONS
#        "JSONCPP_WITH_TESTS OFF"
#        "JSONCPP_WITH_POST_BUILD_UNITTEST OFF"
#        "JSONCPP_WITH_CMAKE_PACKAGE ON"
#        "JSONCPP_WITH_PKGCONFIG_SUPPORT ON"
#        "JSONCPP_WITH_EXAMPLE OFF"
#)

CPMAddPackage(
        NAME nlohmann_json
        VERSION 3.11.2
        GITHUB_REPOSITORY nlohmann/json
        OPTIONS
        "JSON_BuildTests OFF"
)