# rapidjson
CPMAddPackage(
        NAME jsoncpp
        GITHUB_REPOSITORY open-source-parsers/jsoncpp
        GIT_TAG 1.9.5
        OPTIONS
        "JSONCPP_WITH_TESTS OFF"
        "JSONCPP_WITH_POST_BUILD_UNITTEST OFF"
)