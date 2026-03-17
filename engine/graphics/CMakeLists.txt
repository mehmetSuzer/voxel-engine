
find_package(OpenGL REQUIRED)
find_package(cglm REQUIRED)

include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE IMPORTED)
set_target_properties(stb PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${stb_SOURCE_DIR}"
)

file(GLOB_RECURSE SOURCE_FILES 
    CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(graphics ${SOURCE_FILES})
    
target_include_directories(graphics
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(graphics
    PUBLIC OpenGL
    PUBLIC cglm
    PUBLIC stb
)

