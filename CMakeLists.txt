cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(FRAME "luss")
set(WORK   "io")



project(${WORK} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_DIR ${FRAME}/${WORK})

set(HEADERS
    ${TARGET_DIR}/export.h
    ${TARGET_DIR}/lfd.h
    ${TARGET_DIR}/listener.h
    ${TARGET_DIR}/tcp_socket.h
)


add_library("${FRAME}.${WORK}" STATIC

    ${HEADERS}
    ${TARGET_DIR}/lfd.cc
    ${TARGET_DIR}/listener.cc
    ${TARGET_DIR}/tcp_socket.cc
    # --- For luss.whatever!
    # ${PROJECT_NAME}/io/kdb.cc 
    # ${PROJECT_NAME}/io/vchar.cc
    # ${PROJECT_NAME}/io/console.cc

)

target_include_directories("${FRAME}.${WORK}" PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           $<INSTALL_INTERFACE:include/${TARGET_DIR}>
)

target_compile_definitions("${FRAME}.${WORK}" PUBLIC "${FRAME}.${WORK}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header("${FRAME}.${WORK}" EXPORT_FILE_NAME "${FRAME}.${WORK}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()

# static libluss.a should have been put into the current project archive file (libluss.io.a). So no need to link again with luss.a in the other project.
target_link_libraries("${FRAME}.${WORK}" ${CMAKE_DL_LIBS} luss)





install(TARGETS "${FRAME}.${WORK}"
        EXPORT  "${FRAME}.${WORK}"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(FILES ${HFILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${TAGET_DIR}")


add_custom_target("uninstall_${FRAME}.${WORK}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${FRAME}.${WORK}"
    POST_BUILD
    COMMENT "Uninstall ${FRAME}.${WORK} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${TARGET_DIR} ${CMAKE_INSTALL_PREFIX}/lib/lib${FRAME}.${WORK}* || echo Nothing in install_manifest.txt to be uninstalled!
)


#add_subdirectory(test.app)
