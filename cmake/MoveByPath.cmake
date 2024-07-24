message("from ${SRC_PATH} to ${DEST_PATH}")

get_filename_component(FILE_NAME ${SRC_PATH} NAME)
set(FULL_DEST_PATH ${DEST_PATH}/${FILE_NAME})

if ((NOT EXISTS ${FULL_DEST_PATH}) OR (${SRC_PATH} IS_NEWER_THAN ${FULL_DEST_PATH}))
    message("Move to ${DEST_PATH}...")

    file(COPY ${SRC_PATH} DESTINATION ${DEST_PATH})
else ()
    message("${SRC_PATH} is not newer than dest")
endif ()