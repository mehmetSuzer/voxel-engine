
cmake_minimum_required (VERSION 3.28)

project (voxel-engine
    VERSION 0.1.0
    LANGUAGES C
    DESCRIPTION "Homemade Voxel Engine"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --------------------------------------
# Executable
# --------------------------------------
add_executable(${PROJECT_NAME}
    engine/main.c
)

target_compile_options(${PROJECT_NAME} 
    PRIVATE
        $<$<CONFIG:Release>:-flto>    
        -Wall
        -Wextra
        -Wshadow
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wpointer-arith
        -Wcast-align
        -Wmissing-prototypes
        -Wstrict-prototypes
        # -Werror
)

target_link_options(${PROJECT_NAME} 
    PRIVATE $<$<CONFIG:Release>:-flto>
)

add_subdirectory(engine/log)
add_subdirectory(engine/utils)
add_subdirectory(engine/platform)
add_subdirectory(engine/graphics)

target_link_libraries(${PROJECT_NAME}
    PRIVATE log
    PRIVATE utils
    PRIVATE platform
    PRIVATE graphics
)

