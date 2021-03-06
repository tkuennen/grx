
set (MEMORY_SOURCE_FILES
    vd_mem.c
)

set (MEMORY_MODULES
    gmodule-export-2.0
)
pkg_check_modules (MEMORY_DEPS REQUIRED ${MEMORY_MODULES})

string (REPLACE ";" " " link_flags "${MEMORY_DEPS_LDFLAGS}")

add_library (grx_memory MODULE ${MEMORY_SOURCE_FILES})
target_compile_options (grx_memory PRIVATE "-Wall" "-Werror")
target_include_directories (grx_memory
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_BINARY_DIR}/src/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${MEMORY_DEPS_INCLUDE_DIRS}
)
target_link_libraries (grx_memory ${MEMORY_DEPS_LIBRARIES} ${SHARED_LIBRARY_TARGET})
set_target_properties (grx_memory PROPERTIES
    OUTPUT_NAME ${PACKAGE_NAME}-vdriver-memory
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LINK_FLAGS "${link_flags}"
)
add_dependencies (plugins grx_memory)
install (TARGETS grx_memory LIBRARY DESTINATION ${CMAKE_INSTALL_PKGPLUGINDIR})
