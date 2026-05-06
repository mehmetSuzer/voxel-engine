
find_package(OpenGL REQUIRED)
find_package(cglm REQUIRED)
find_package(Ktx REQUIRED)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(graphics STATIC ${SOURCE_FILES})
    
target_include_directories(graphics
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(graphics
    PRIVATE OpenGL::GL
    PRIVATE cglm::cglm
    PRIVATE KTX::ktx
    PRIVATE stb
    PRIVATE log
    PRIVATE utils
)

# --------------------------------------
# Copy GLSL Shaders
# --------------------------------------
set(GLSL_INPUT_DIR  ${CMAKE_SOURCE_DIR}/shaders)
set(GLSL_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders)
if(EXISTS ${GLSL_INPUT_DIR})
    file(GLOB_RECURSE GLSL_FILES RELATIVE "${GLSL_INPUT_DIR}" "${GLSL_INPUT_DIR}/*")
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

# --------------------------------------
# Copy Textures
# --------------------------------------
set(TEXTURES_INPUT_DIR  ${CMAKE_SOURCE_DIR}/textures)
set(TEXTURES_OUTPUT_DIR ${CMAKE_BINARY_DIR}/textures)
if(EXISTS ${TEXTURES_INPUT_DIR})
    file(GLOB_RECURSE TEXTURE_FILES RELATIVE "${TEXTURES_INPUT_DIR}" "${TEXTURES_INPUT_DIR}/*")
    set(TEXTURE_OUTPUTS)

    foreach(FILE ${TEXTURE_FILES})
        set(SRC "${TEXTURES_INPUT_DIR}/${FILE}")
        set(DST "${TEXTURES_OUTPUT_DIR}/${FILE}")
        get_filename_component(DST_DIR "${DST}" DIRECTORY)

        file(MAKE_DIRECTORY "${DST_DIR}")

        add_custom_command(
            OUTPUT "${DST}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SRC}" "${DST}"
            DEPENDS "${SRC}"
            COMMENT "Copying texture: ${FILE}"
            VERBATIM
        )

        list(APPEND TEXTURE_OUTPUTS "${DST}")
    endforeach()

    add_custom_target(copy_textures ALL DEPENDS ${TEXTURE_OUTPUTS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE TEXTURES_DIR="${TEXTURES_OUTPUT_DIR}")
    add_dependencies(${PROJECT_NAME} copy_textures)
endif()

