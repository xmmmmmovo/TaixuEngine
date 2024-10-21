# taskflow
CPMAddPackage(
        NAME taskflow
        GITHUB_REPOSITORY taskflow/taskflow
        GIT_TAG bd150cedd257b682006a54b64068ff20cde0f771
        OPTIONS
        "TF_BUILD_CUDA OFF"
        "TF_BUILD_TESTS OFF"
        "TF_BUILD_EXAMPLES OFF"
)
