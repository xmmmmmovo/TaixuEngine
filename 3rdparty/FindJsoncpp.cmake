#CPMAddPackage(
#        NAME nlohmann_json
#        VERSION 3.11.2
#        GITHUB_REPOSITORY nlohmann/json
#        OPTIONS
#        "JSON_BuildTests OFF"
#)

CPMAddPackage(
        NAME simdjson
        VERSION 3.2.1
        GIT_SHALLOW TRUE
        GITHUB_REPOSITORY simdjson/simdjson
)