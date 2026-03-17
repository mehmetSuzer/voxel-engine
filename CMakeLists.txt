
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
)

target_link_options(${PROJECT_NAME} 
    PRIVATE $<$<CONFIG:Release>:-flto>
)

add_subdirectory(engine/host)
add_subdirectory(engine/graphics)

target_link_libraries(${PROJECT_NAME}
    PRIVATE host
    PRIVATE graphics
)

# --------------------------------------
# Copy GLSL Shaders
# --------------------------------------
set(GLSL_INPUT_DIR  ${CMAKE_SOURCE_DIR}/shaders/glsl)
set(GLSL_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders/glsl)
if(EXISTS ${GLSL_INPUT_DIR})
    file(GLOB_RECURSE GLSL_FILES RELATIVE "${GLSL_INPUT_DIR}" "${GLSL_INPUT_DIR}/*.glsl")
    set(GLSL_OUTPUTS)

    foreach(FILE ${GLSL_FILES})
        set(SRC "${GLSL_INPUT_DIR}/${FILE}")
        set(DST "${GLSL_OUTPUT_DIR}/${FILE}")
        get_filename_component(DST_DIR "${DST}" DIRECTORY)
        
        file(MAKE_DIRECTORY "${DST_DIR}")

        add_custom_command(
            OUTPUT "${DST}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SRC}" "${DST}"
            DEPENDS "${SRC}"
            COMMENT "Copying GLSL shader: ${FILE}"
            VERBATIM
        )

        list(APPEND GLSL_OUTPUTS "${DST}")
    endforeach()

    add_custom_target(copy_glsl ALL DEPENDS ${GLSL_OUTPUTS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLSL_SHADERS_DIR="${GLSL_OUTPUT_DIR}")
    add_dependencies(${PROJECT_NAME} copy_glsl)
endif()

