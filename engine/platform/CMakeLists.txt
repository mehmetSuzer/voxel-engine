
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES 
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(platform STATIC ${SOURCE_FILES})
    
target_include_directories(platform
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(platform
    PRIVATE glfw
    PRIVATE log
    PRIVATE utils
)

