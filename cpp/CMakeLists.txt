set(RUST_PROJECT_DIR ${CMAKE_SOURCE_DIR}/rust)
set(RUST_TARGET_DIR ${RUST_PROJECT_DIR}/target/release)
set(RUST_LIB ${RUST_TARGET_DIR}/librustlib.so)

# Build Rust shared lib
add_custom_command(
    OUTPUT ${RUST_LIB}
    COMMAND cargo build --release
    WORKING_DIRECTORY ${RUST_PROJECT_DIR}
    COMMENT "Building Rust shared lib"
)

add_custom_target(rustlib_build
    DEPENDS ${RUST_LIB}
)

# Import Rust so
add_library(rustlib SHARED IMPORTED)
set_target_properties(rustlib PROPERTIES
    IMPORTED_LOCATION ${RUST_LIB}
)

add_dependencies(rustlib rustlib_build)

# C++ exe
add_executable(app main.cpp)
target_include_directories(app PRIVATE include)
target_link_libraries(app PRIVATE rustlib)

# Make runtime linker find the so
set_target_properties(app PROPERTIES
    BUILD_RPATH ${RUST_TARGET_DIR}
)
