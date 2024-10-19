# reflcpp
CPMAddPackage(
        NAME reflcpp
        GITHUB_REPOSITORY getml/reflect-cpp
        GIT_TAG 09eef9d5a1815b4659d095b2d403157565cb811e
        OPTIONS
        "SPDLOG_BUILD_EXAMPLE Off"
        "SPDLOG_FMT_EXTERNAL ON"
        "SPDLOG_FMT_EXTERNAL_HO OFF"
)