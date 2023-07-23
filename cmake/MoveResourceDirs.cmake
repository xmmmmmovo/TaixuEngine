set(TARGET_IMGUIINI_FILE ${OUTPUT_DIR}/imgui.ini)
set(TARGET_ASSETS_DIR ${OUTPUT_DIR}/assets)
set(TARGET_RES_DIR ${OUTPUT_DIR}/res)

set(IMGUIINI_FILE ${ENGINE_ROOT_DIR}/src/editor/imgui.ini)
set(ASSETS_DIR ${ENGINE_ROOT_DIR}/assets)
set(RES_DIR ${ENGINE_ROOT_DIR}/src/editor/res)

message("copy start")

if ((NOT EXISTS ${TARGET_IMGUIINI_FILE}) OR (${IMGUIINI_FILE} IS_NEWER_THAN ${TARGET_IMGUIINI_FILE}))
    message("Move imgui.ini...")
    file(COPY ${IMGUIINI_FILE} DESTINATION ${OUTPUT_DIR})
endif ()

if ((NOT EXISTS ${TARGET_ASSETS_DIR}) OR (${ASSETS_DIR} IS_NEWER_THAN ${TARGET_ASSETS_DIR}))
    message("Move assets dir...")
    file(REMOVE_RECURSE ${TARGET_ASSETS_DIR})
    file(COPY ${ASSETS_DIR} DESTINATION ${OUTPUT_DIR})
endif ()

if ((NOT EXISTS ${TARGET_RES_DIR}) OR (${RES_DIR} IS_NEWER_THAN ${TARGET_RES_DIR}))
    message("Move res dir...")
    file(REMOVE_RECURSE ${TARGET_RES_DIR})
    file(COPY ${RES_DIR} DESTINATION ${OUTPUT_DIR})
endif ()