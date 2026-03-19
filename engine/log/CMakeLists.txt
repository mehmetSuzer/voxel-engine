
file(GLOB_RECURSE SOURCE_FILES 
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(log STATIC ${SOURCE_FILES})
    
target_include_directories(log
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)

