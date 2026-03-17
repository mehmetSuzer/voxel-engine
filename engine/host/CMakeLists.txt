
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES 
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(host STATIC ${SOURCE_FILES})
    
target_include_directories(host
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(host
    PUBLIC glfw
)

