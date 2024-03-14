macro(FIND_GLOB_RECURSE OUT_VAR)
    file(GLOB_RECURSE ${OUT_VAR} ${ARGN})
endmacro()