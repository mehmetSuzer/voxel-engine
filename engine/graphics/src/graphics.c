
#include "utils/macros.h"
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/graphics.h"

typedef struct HardwareCapabilityState
{
    // Viewport 
    
    GLint maxViewportCount;
    GLint maxViewportDimensions[2];
    GLint viewportBoundRange[2];
    GLint viewportSubpixelBitCount;

    // Framebuffer

    GLint maxFramebufferWidth;
    GLint maxFramebufferHeight;
    GLint maxFramebufferLayerCount;
    GLint maxFramebufferSampleCount;
 
    // Draw
    
    GLint maxDrawBufferCount;
    GLint maxDualSourceDrawBufferCount;
    GLint maxColourAttachmentCount;
    GLint maxRenderBufferSize;
    GLint maxSampleCount;
    GLint maxColourTextureSampleCount;
    GLint maxDepthTextureSampleCount;
    GLint maxIntegerSampleCount;
    GLint maxElementsVertexCount;
    GLint maxElementsIndexCount;

    // Texture

    GLint maxTextureSize;
    GLint max3DTextureSize;
    GLint maxCubeMapTextureSize;
    GLint maxRectangleTextureSize;
    GLint maxTextureBufferSize;
    GLint maxArrayTextureLayerCount;
    GLint maxTextureImageUnitCount;
    GLfloat maxTextureLODBias;
    GLfloat maxTextureMaxAnisotropy;

    // Vertex Shader
  
    GLint maxVertexAtomicCounterCount;
    GLint maxVertexAtomicCounterBufferCount;
    GLint maxVertexAttributeCount;
    GLint maxVertexAttributeBindingCount;
    GLint maxVertexAttributeRelativeOffset;
    GLint maxVertexAttributeStride;
    GLint maxVertexCombinedUniformComponentCount;
    GLint maxVertexImageUniformCount;
    GLint maxVertexOutputComponentCount;
    GLint maxVertexShaderStorageBlockCount;
    GLint maxVertexStreamCount;
    GLint maxVertexTextureImageUnitCount;
    GLint maxVertexUniformVectorCount;
    GLint maxVertexUniformBlockCount;
    GLint maxVertexUniformComponentCount;

    // Tess Control Shader

    GLint maxTessControlAtomicCounterCount;
    GLint maxTessControlAtomicCounterBufferCount;
    GLint maxTessControlCombinedUniformComponentCount;
    GLint maxTessControlImageUniformCount;
    GLint maxTessControlInputComponentCount;
    GLint maxTessControlOutputComponentCount;
    GLint maxTessControlShaderStorageBlockCount;
    GLint maxTessControlTextureImageUnitCount;
    GLint maxTessControlTotalOutputComponentCount;
    GLint maxTessControlUniformBlockCount;
    GLint maxTessControlUniformComponentCount;

    // Tess Evaluation Shader
    
    GLint maxTessEvaluationAtomicCounterCount;
    GLint maxTessEvaluationAtomicCounterBufferCount;
    GLint maxTessEvaluationCombinedUniformComponentCount;
    GLint maxTessEvaluationImageUniformCount;
    GLint maxTessEvaluationInputComponentCount;
    GLint maxTessEvaluationOutputComponentCount;
    GLint maxTessEvaluationShaderStorageBlockCount;
    GLint maxTessEvaluationTextureImageUnitCount;
    GLint maxTessEvaluationUniformBlockCount;
    GLint maxTessEvaluationUniformComponentCount;

    // Geometry Shader
    
    GLint maxGeometryAtomicCounterCount;
    GLint maxGeometryAtomicCounterBufferCount;
    GLint maxGeometryCombinedUniformComponentCount;
    GLint maxGeometryImageUniformCount;
    GLint maxGeometryInputComponentCount;
    GLint maxGeometryOutputComponentCount;
    GLint maxGeometryOutputVertexCount;
    GLint maxGeometryShaderInvocationCount;
    GLint maxGeometryShaderStorageBlockCount;
    GLint maxGeometryTextureImageUnitCount;
    GLint maxGeometryTotalOutputComponentCount;
    GLint maxGeometryUniformBlockCount;
    GLint maxGeometryUniformComponentCount;

    // Fragment Shader

    GLint maxFragmentAtomicCounterCount;
    GLint maxFragmentAtomicCounterBufferCount;
    GLint maxFragmentCombinedUniformComponentCount;
    GLint maxFragmentImageUniformCount;
    GLint maxFragmentInputComponentCount;
    GLint maxFragmentInterpolationOffset;
    GLint maxFragmentShaderStorageBlockCount;
    GLint maxFragmentUniformBlockCount;
    GLint maxFragmentUniformComponentCount;

    // Compute Shader

    GLint maxComputeAtomicCounterCount;
    GLint maxComputeAtomicCounterBufferCount;
    GLint maxComputeCombinedUniformComponentCount;
    GLint maxComputeImageUniformCount; 
    GLint maxComputeShaderStorageBlockCount;
    GLint maxComputeSharedMemorySize;
    GLint maxComputeTextureImageUnitCount;
    GLint maxComputeUniformBlockCount;
    GLint maxComputeUniformComponentCount;
    GLint maxComputeWorkGroupCount[3];
    GLint maxComputeWorkGroupSize[3];
    GLint maxComputeWorkGroupInvocationCount;

    // All Shaders

    GLint maxAllAtomicCounterCount;
    GLint maxAllAtomicCounterBufferCount;
    GLint maxAllClipAndCullDistanceCount;
    GLint maxAllImageUniformCount;
    GLint maxAllImageUnitAndFragmentOutputCount;
    GLint maxAllShaderOutputResourceCount;
    GLint maxAllShaderStorageBlockCount;
    GLint maxAllTextureImageUnitCount;
    GLint maxAllUniformBlockCount;

    // Transform Feedback

    GLint maxTransformFeedbackBufferCount;
    GLint maxTransformFeedbackInterleavedComponentCount;
    GLint maxTransformFeedbackSeparateAttributeCount;
    GLint maxTransformFeedbackSeparateComponentCount;

    // Debug 

    GLint maxDebugGroupStackDepth; 
    GLint maxDebugLabelLength;
    GLint maxDebugLoggedMessageCount;
    GLint maxDebugMessageLength;

    // Other

    GLint shaderStorageBufferOffsetAlignment;
    GLint uniformBufferOffsetAlignment;
    GLint textureBufferOffsetAlignment;
    GLint maxShaderStorageBlockSize;
    GLint maxShaderStorageBufferBindingCount;
    GLint maxUniformBlockSize;
    GLint maxUniformBufferBindingCount;
    GLint maxUniformLocationCount;
    GLint maxImageUnitCount;
    GLint maxImageSampleCount;
    GLint maxPatchVertexCount;
} HardwareCapabilityState;

typedef struct ViewportState
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
} ViewportState;

typedef struct DepthTestState
{
    bool enabled;
    GLboolean writeEnabled;
    GLfloat near;
    GLfloat far;
    CompareFunction compareFunction;
} DepthTestState;

typedef struct StencilTestFaceState
{
    CompareFunction compareFunction;
    GLint reference;
    GLuint testMask;
    GLuint writeMask;
    StencilOperation stencilFail;
    StencilOperation depthFail;
    StencilOperation depthPass;
} StencilTestFaceState;

typedef struct StencilTestState
{
    bool enabled;
    StencilTestFaceState front;
    StencilTestFaceState back;
} StencilTestState;

typedef struct ScissorTestState
{
    bool enabled;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
} ScissorTestState;

typedef struct BlendState
{
    bool enabled;
    BlendFactor srcRGB;
    BlendFactor dstRGB;
    BlendFactor srcAlpha;
    BlendFactor dstAlpha;
    BlendEquation equationRGB;
    BlendEquation equationAlpha;
    GLfloat colour[4];
} BlendState;

typedef struct CullFaceState
{
    bool enabled;
    Face face;
    FrontFace frontFace;
} CullFaceState;

typedef struct DitherState
{
    bool enabled;
} DitherState;

typedef struct MultisampleState
{
    bool enabled;
    GLint samples;
} MultisampleState;

typedef struct SampleAlphaToCoverageState
{
    bool enabled;
} SampleAlphaToCoverageState;

typedef struct SampleAlphaToOneState
{
    bool enabled;
} SampleAlphaToOneState;

typedef struct SampleCoverageState
{
    bool enabled;
    GLboolean invert;
    GLfloat coverage;
} SampleCoverageState;

typedef struct DepthClampState
{
    bool enabled;
} DepthClampState;

typedef struct PolygonOffsetState
{
    bool pointEnabled;
    bool lineEnabled;
    bool fillEnabled;
    GLfloat factor;
    GLfloat units;
} PolygonOffsetState;

typedef struct ProgramPointSizeState
{
    bool enabled;
    GLfloat size;
} ProgramPointSizeState;

typedef struct FramebufferSRGBState
{
    bool enabled;
} FramebufferSRGBState;

typedef struct PrimitiveRestartState
{
    bool enabled;
    GLuint restartIndex;
} PrimitiveRestartState;

typedef struct PolygonFaceState
{
    PolygonMode mode;
} PolygonFaceState;

typedef struct PolygonState
{
    PolygonFaceState front;
    PolygonFaceState back;
} PolygonState;

typedef struct ClearState
{
    GLfloat colour[4];
    GLdouble depth;
    GLint stencil;
} ClearState;

typedef struct GraphicsState
{
    HardwareCapabilityState hardwareCapability;
    ViewportState viewport;
    DepthTestState depthTest;
    StencilTestState stencilTest;
    ScissorTestState scissorTest;
    BlendState blend;
    CullFaceState cullFace;
    PolygonState polygon;
    DitherState dither;
    MultisampleState multisample;
    SampleAlphaToCoverageState sampleAlphaToCoverage;
    SampleAlphaToOneState sampleAlphaToOne;
    SampleCoverageState sampleCoverage;
    DepthClampState depthClamp;
    PolygonOffsetState polygonOffset;
    ProgramPointSizeState programPointSize;
    FramebufferSRGBState framebufferSRGB;
    PrimitiveRestartState primitiveRestart;
    ClearState clear;
} GraphicsState;

static GraphicsState graphicsState = {
    .hardwareCapability = {0},
    .viewport = {
        .x = 0, 
        .y = 0, 
        .width = 0, 
        .height = 0,
    },
    .depthTest = {
        .enabled = false,
        .writeEnabled = GL_TRUE,
        .near = 0.0f,
        .far  = 1.0f,
        .compareFunction = CompareFunctionLess,
    },
    .stencilTest = {
        .enabled = false,
        .front = {
            .compareFunction = CompareFunctionAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFF,
            .writeMask = 0xFFFFFFFF,
            .stencilFail = StencilOperationKeep,
            .depthFail   = StencilOperationKeep,
            .depthPass   = StencilOperationKeep,
        },
        .back = {
            .compareFunction = CompareFunctionAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFF,
            .writeMask = 0xFFFFFFFF,
            .stencilFail = StencilOperationKeep,
            .depthFail   = StencilOperationKeep,
            .depthPass   = StencilOperationKeep,
        },
    },
    .scissorTest = {
        .enabled = false,
        .x = 0, 
        .y = 0, 
        .width = 0, 
        .height = 0,
    },
    .blend = {
        .enabled = false,
        .srcRGB   = BlendFactorOne,
        .dstRGB   = BlendFactorZero,
        .srcAlpha = BlendFactorOne,
        .dstAlpha = BlendFactorZero,
        .equationRGB   = BlendEquationAdd,
        .equationAlpha = BlendEquationAdd,
        .colour = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .cullFace = {
        .enabled = false,
        .face = FaceBack,
        .frontFace = FrontFaceCCW,
    },
    .dither = {
        .enabled = false,
    },
    .multisample = {
        .enabled = true,
        .samples = 1,
    },
    .sampleAlphaToCoverage = {
        .enabled = false,
    },
    .sampleAlphaToOne = {
        .enabled = false,
    },
    .sampleCoverage = {
        .enabled = false,
        .invert = GL_FALSE,
        .coverage = 1.0f,
    },
    .depthClamp = {
        .enabled = false,
    },
    .polygonOffset = {
        .pointEnabled = false,
        .lineEnabled  = false,
        .fillEnabled  = false,
        .factor = 0.0f,
        .units = 0.0f,
    },
    .programPointSize = {
        .enabled = false,
        .size = 1.0f,
    },
    .framebufferSRGB = {
        .enabled = false,
    },
    .primitiveRestart = {
        .enabled = false,
        .restartIndex = 0xFFFFFFFF,
    },
    .polygon = {
        .front = 
        {
            .mode = PolygonModeFill,
        },
        .back = {
            .mode = PolygonModeFill,
        },
    },
    .clear = {
        .colour = {0.0f, 0.0f, 0.0f, 1.0f},
        .depth = DEPTH_FURTHEST,
        .stencil = 0,
    },
};

static void APIENTRY debugMessageCallback(
    GLenum debugSourceNative, 
    GLenum debugTypeNative, 
    unsigned int debugID, 
    GLenum debugSeverity, 
    GLsizei messageLength, 
    const char* message, 
    const void* userParameters)
{
    UNUSED(messageLength); 
    UNUSED(userParameters);

    const char* debugSource =
        (debugSourceNative == GL_DEBUG_SOURCE_API)             ? "API"             :
        (debugSourceNative == GL_DEBUG_SOURCE_WINDOW_SYSTEM)   ? "window system"   :
        (debugSourceNative == GL_DEBUG_SOURCE_SHADER_COMPILER) ? "shader compiler" :
        (debugSourceNative == GL_DEBUG_SOURCE_THIRD_PARTY)     ? "third party"     :
        (debugSourceNative == GL_DEBUG_SOURCE_APPLICATION)     ? "application"     :
        (debugSourceNative == GL_DEBUG_SOURCE_OTHER)           ? "other"           : "unknown source";

    const char* debugType =
        (debugTypeNative == GL_DEBUG_TYPE_ERROR)               ? "error"                :
        (debugTypeNative == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) ? "deprecated behaviour" :
        (debugTypeNative == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)  ? "undefined behaviour"  :
        (debugTypeNative == GL_DEBUG_TYPE_PORTABILITY)         ? "portability"          :
        (debugTypeNative == GL_DEBUG_TYPE_PERFORMANCE)         ? "performance"          :
        (debugTypeNative == GL_DEBUG_TYPE_MARKER)              ? "marker"               :
        (debugTypeNative == GL_DEBUG_TYPE_PUSH_GROUP)          ? "push group"           :
        (debugTypeNative == GL_DEBUG_TYPE_POP_GROUP)           ? "pop group"            :
        (debugTypeNative == GL_DEBUG_TYPE_OTHER)               ? "other"                : "unknown type";

    switch (debugSeverity)
    {
        case GL_DEBUG_SEVERITY_NOTIFICATION: logVerbose("OPENGL", "%s | %s | %s (%u)", debugSource, debugType, message, debugID); break;
        case GL_DEBUG_SEVERITY_LOW:          logInfo("OPENGL", "%s | %s | %s (%u)", debugSource, debugType, message, debugID);    break;
        case GL_DEBUG_SEVERITY_MEDIUM:       logWarning("OPENGL", "%s | %s | %s (%u)", debugSource, debugType, message, debugID); break;
        case GL_DEBUG_SEVERITY_HIGH:         logError("OPENGL", "%s | %s | %s (%u)", debugSource, debugType, message, debugID);   break;
    }
}

static void getHardwareCapabilities(void)
{
    // Viewport

    glGetIntegerv(GL_MAX_VIEWPORTS, &graphicsState.hardwareCapability.maxViewportCount);
    logVerbose("GRAPHICS", "max viewport count: %i", graphicsState.hardwareCapability.maxViewportCount);

    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &graphicsState.hardwareCapability.maxViewportDimensions[0]);
    logVerbose("GRAPHICS", "max viewport dimensions: (%i, %i)", 
        graphicsState.hardwareCapability.maxViewportDimensions[0],
        graphicsState.hardwareCapability.maxViewportDimensions[1]);

    glGetIntegerv(GL_VIEWPORT_BOUNDS_RANGE, &graphicsState.hardwareCapability.viewportBoundRange[0]);
    logVerbose("GRAPHICS", "viewport bound range: (%i, %i)",
        graphicsState.hardwareCapability.viewportBoundRange[0],
        graphicsState.hardwareCapability.viewportBoundRange[1]);

    glGetIntegerv(GL_VIEWPORT_SUBPIXEL_BITS, &graphicsState.hardwareCapability.viewportSubpixelBitCount);
    logVerbose("GRAPHICS", "viewport subpixel bit count: %i", graphicsState.hardwareCapability.viewportSubpixelBitCount);

    // Framebuffer

    glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &graphicsState.hardwareCapability.maxFramebufferWidth);
    logVerbose("GRAPHICS", "max framebuffer width: %i", graphicsState.hardwareCapability.maxFramebufferWidth);

    glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &graphicsState.hardwareCapability.maxFramebufferHeight);
    logVerbose("GRAPHICS", "max framebuffer height: %i", graphicsState.hardwareCapability.maxFramebufferHeight);

    glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS, &graphicsState.hardwareCapability.maxFramebufferLayerCount);
    logVerbose("GRAPHICS", "max framebuffer layer count: %i", graphicsState.hardwareCapability.maxFramebufferLayerCount);

    glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &graphicsState.hardwareCapability.maxFramebufferSampleCount);
    logVerbose("GRAPHICS", "max framebuffer sample count: %i", graphicsState.hardwareCapability.maxFramebufferSampleCount);

    // Draw
    
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &graphicsState.hardwareCapability.maxDrawBufferCount);
    logVerbose("GRAPHICS", "max draw buffer count: %i", graphicsState.hardwareCapability.maxDrawBufferCount);

    glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, &graphicsState.hardwareCapability.maxDualSourceDrawBufferCount);
    logVerbose("GRAPHICS", "max dual source draw buffer count: %i", graphicsState.hardwareCapability.maxDualSourceDrawBufferCount);

    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &graphicsState.hardwareCapability.maxColourAttachmentCount);
    logVerbose("GRAPHICS", "max colour attachment count: %i", graphicsState.hardwareCapability.maxColourAttachmentCount);

    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &graphicsState.hardwareCapability.maxRenderBufferSize);
    logVerbose("GRAPHICS", "max render buffer size: %i", graphicsState.hardwareCapability.maxRenderBufferSize);

    glGetIntegerv(GL_MAX_SAMPLES, &graphicsState.hardwareCapability.maxSampleCount);
    logVerbose("GRAPHICS", "max sample count: %i", graphicsState.hardwareCapability.maxSampleCount);

    glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &graphicsState.hardwareCapability.maxColourTextureSampleCount);
    logVerbose("GRAPHICS", "max colour texture sample count: %i", graphicsState.hardwareCapability.maxColourTextureSampleCount);

    glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &graphicsState.hardwareCapability.maxDepthTextureSampleCount);
    logVerbose("GRAPHICS", "max depth texture sample count: %i", graphicsState.hardwareCapability.maxDepthTextureSampleCount);

    glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &graphicsState.hardwareCapability.maxIntegerSampleCount);
    logVerbose("GRAPHICS", "max integer sample count: %i", graphicsState.hardwareCapability.maxIntegerSampleCount);

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &graphicsState.hardwareCapability.maxElementsVertexCount);
    logVerbose("GRAPHICS", "max elements vertex count: %i", graphicsState.hardwareCapability.maxElementsVertexCount);

    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &graphicsState.hardwareCapability.maxElementsIndexCount);
    logVerbose("GRAPHICS", "max elements index count: %i", graphicsState.hardwareCapability.maxElementsIndexCount);

    // Texture

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &graphicsState.hardwareCapability.maxTextureSize);
    logVerbose("GRAPHICS", "max texture size: %i", graphicsState.hardwareCapability.maxTextureSize);

    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &graphicsState.hardwareCapability.max3DTextureSize);
    logVerbose("GRAPHICS", "max 3D texture size: %i", graphicsState.hardwareCapability.max3DTextureSize);

    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &graphicsState.hardwareCapability.maxCubeMapTextureSize);
    logVerbose("GRAPHICS", "max cube map texture size: %i", graphicsState.hardwareCapability.maxCubeMapTextureSize);

    glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE, &graphicsState.hardwareCapability.maxRectangleTextureSize);
    logVerbose("GRAPHICS", "max rectangle texture size: %i", graphicsState.hardwareCapability.maxRectangleTextureSize);

    glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &graphicsState.hardwareCapability.maxTextureBufferSize);
    logVerbose("GRAPHICS", "max texture buffer size: %i", graphicsState.hardwareCapability.maxTextureBufferSize);

    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &graphicsState.hardwareCapability.maxArrayTextureLayerCount);
    logVerbose("GRAPHICS", "max array texture layer count: %i", &graphicsState.hardwareCapability.maxArrayTextureLayerCount);

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxTextureImageUnitCount);
    logVerbose("GRAPHICS", "max texture image unit count: %i", graphicsState.hardwareCapability.maxTextureImageUnitCount);

    glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS, &graphicsState.hardwareCapability.maxTextureLODBias);
    logVerbose("GRAPHICS", "max texture LOD bias: %.1f", graphicsState.hardwareCapability.maxTextureLODBias);

    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &graphicsState.hardwareCapability.maxTextureMaxAnisotropy);
    logVerbose("GRAPHICS", "max texture max anisotropy: %.1f", graphicsState.hardwareCapability.maxTextureMaxAnisotropy);

    // Vertex Shader
  
    glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxVertexAtomicCounterCount);
    logVerbose("GRAPHICS", "max vertex atomic count count: %i", graphicsState.hardwareCapability.maxVertexAtomicCounterCount);

    glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxVertexAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max vertex atomic counter buffer count: %i", graphicsState.hardwareCapability.maxVertexAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &graphicsState.hardwareCapability.maxVertexAttributeCount);
    logVerbose("GRAPHICS", "max vertex attribute count: %i", graphicsState.hardwareCapability.maxVertexAttributeCount);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &graphicsState.hardwareCapability.maxVertexAttributeBindingCount);
    logVerbose("GRAPHICS", "max vertex attribute binding count: %i", graphicsState.hardwareCapability.maxVertexAttributeBindingCount);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, &graphicsState.hardwareCapability.maxVertexAttributeRelativeOffset);
    logVerbose("GRAPHICS", "max vertex attribute relative offset: %i", graphicsState.hardwareCapability.maxVertexAttributeRelativeOffset);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_STRIDE, &graphicsState.hardwareCapability.maxVertexAttributeStride);
    logVerbose("GRAPHICS", "max vertex attribute stride: %i", graphicsState.hardwareCapability.maxVertexAttributeStride);

    glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxVertexCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max vertex combined uniform component count: %i", graphicsState.hardwareCapability.maxVertexCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_VERTEX_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxVertexImageUniformCount);
    logVerbose("GRAPHICS", "max vertex image uniform count: %i", graphicsState.hardwareCapability.maxVertexImageUniformCount);

    glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxVertexOutputComponentCount);
    logVerbose("GRAPHICS", "max vertex output component count: %i", graphicsState.hardwareCapability.maxVertexOutputComponentCount);

    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxVertexShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max vertex shader storage block count: %i", graphicsState.hardwareCapability.maxVertexShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_VERTEX_STREAMS, &graphicsState.hardwareCapability.maxVertexStreamCount);
    logVerbose("GRAPHICS", "max vertex stream count: %i", graphicsState.hardwareCapability.maxVertexStreamCount);

    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxVertexTextureImageUnitCount);
    logVerbose("GRAPHICS", "max vertex texture image unit count: %i", graphicsState.hardwareCapability.maxVertexTextureImageUnitCount);

    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &graphicsState.hardwareCapability.maxVertexUniformVectorCount);
    logVerbose("GRAPHICS", "max vertex uniform vector count: %i", graphicsState.hardwareCapability.maxVertexUniformVectorCount);

    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxVertexUniformBlockCount);
    logVerbose("GRAPHICS", "max vertex uniform block count: %i", graphicsState.hardwareCapability.maxVertexUniformBlockCount);

    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxVertexUniformComponentCount);
    logVerbose("GRAPHICS", "max vertex uniform component count: %i", graphicsState.hardwareCapability.maxVertexUniformComponentCount);

    // Tess Control Shader

    glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxTessControlAtomicCounterCount);
    logVerbose("GRAPHICS", "max tess control atomic counter count: %i", graphicsState.hardwareCapability.maxTessControlAtomicCounterCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxTessControlAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max tess control atomic counter buffer count: %i", graphicsState.hardwareCapability.maxTessControlAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxTessControlCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max tess control combined uniform component count: %i", graphicsState.hardwareCapability.maxTessControlCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxTessControlImageUniformCount);
    logVerbose("GRAPHICS", "max tess control image uniform count: %i", graphicsState.hardwareCapability.maxTessControlImageUniformCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_INPUT_COMPONENTS, &graphicsState.hardwareCapability.maxTessControlInputComponentCount);
    logVerbose("GRAPHICS", "max tess control input component count: %i", graphicsState.hardwareCapability.maxTessControlInputComponentCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxTessControlOutputComponentCount);
    logVerbose("GRAPHICS", "max tess control output component count: %i", graphicsState.hardwareCapability.maxTessControlOutputComponentCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxTessControlShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max tess control shader storage block count: %i", graphicsState.hardwareCapability.maxTessControlShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxTessControlTextureImageUnitCount);
    logVerbose("GRAPHICS", "max tess control texture image unit count: %i", graphicsState.hardwareCapability.maxTessControlTextureImageUnitCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxTessControlTotalOutputComponentCount);
    logVerbose("GRAPHICS", "max tess control total output component count: %i", graphicsState.hardwareCapability.maxTessControlTotalOutputComponentCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxTessControlUniformBlockCount);
    logVerbose("GRAPHICS", "max tess control uniform block count: %i", graphicsState.hardwareCapability.maxTessControlUniformBlockCount);

    glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxTessControlUniformComponentCount);
    logVerbose("GRAPHICS", "max tess control uniform component count: %i", &graphicsState.hardwareCapability.maxTessControlUniformComponentCount);

    // Tess Evaluation Shader
    
    glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxTessEvaluationAtomicCounterCount);
    logVerbose("GRAPHICS", "max tess evaluation atomic counter count: %i", graphicsState.hardwareCapability.maxTessEvaluationAtomicCounterCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxTessEvaluationAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max tess evaluation atomic counter buffer count: %i", graphicsState.hardwareCapability.maxTessEvaluationAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxTessEvaluationCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max tess evaluation combined uniform component count: %i", graphicsState.hardwareCapability.maxTessEvaluationCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxTessEvaluationImageUniformCount);
    logVerbose("GRAPHICS", "max tess evaluation image uniform count: %i", graphicsState.hardwareCapability.maxTessEvaluationImageUniformCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS, &graphicsState.hardwareCapability.maxTessEvaluationInputComponentCount);
    logVerbose("GRAPHICS", "max tess evaluation input component count: %i", graphicsState.hardwareCapability.maxTessEvaluationInputComponentCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxTessEvaluationOutputComponentCount);
    logVerbose("GRAPHICS", "max tess evaluation output component count: %i", graphicsState.hardwareCapability.maxTessEvaluationOutputComponentCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxTessEvaluationShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max tess evaluation shader storage block count: %i", graphicsState.hardwareCapability.maxTessEvaluationShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxTessEvaluationTextureImageUnitCount);
    logVerbose("GRAPHICS", "max tess evaluation texture image unit count: %i", graphicsState.hardwareCapability.maxTessEvaluationTextureImageUnitCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxTessEvaluationUniformBlockCount);
    logVerbose("GRAPHICS", "max tess evaluation uniform block count: %i", graphicsState.hardwareCapability.maxTessEvaluationUniformBlockCount);

    glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxTessEvaluationUniformComponentCount);
    logVerbose("GRAPHICS", "max tess evaluation uniform component count: %i", &graphicsState.hardwareCapability.maxTessEvaluationUniformComponentCount);

    // Geometry Shader
    
    glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxGeometryAtomicCounterCount);
    logVerbose("GRAPHICS", "max geometry atomic counter count: %i", graphicsState.hardwareCapability.maxGeometryAtomicCounterCount);

    glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxGeometryAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max geometry atomic counter buffer count: %i", graphicsState.hardwareCapability.maxGeometryAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxGeometryCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max geometry combined uniform component count: %i", graphicsState.hardwareCapability.maxGeometryCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_GEOMETRY_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxGeometryImageUniformCount);
    logVerbose("GRAPHICS", "max geometry image uniform count: %i", graphicsState.hardwareCapability.maxGeometryImageUniformCount);

    glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS, &graphicsState.hardwareCapability.maxGeometryInputComponentCount);
    logVerbose("GRAPHICS", "max geometry input component count: %i", graphicsState.hardwareCapability.maxGeometryInputComponentCount);

    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxGeometryOutputComponentCount);
    logVerbose("GRAPHICS", "max geometry output component count: %i", graphicsState.hardwareCapability.maxGeometryOutputComponentCount);

    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &graphicsState.hardwareCapability.maxGeometryOutputVertexCount);
    logVerbose("GRAPHICS", "max geometry output vertex count: %i", graphicsState.hardwareCapability.maxGeometryOutputVertexCount);

    glGetIntegerv(GL_MAX_GEOMETRY_SHADER_INVOCATIONS, &graphicsState.hardwareCapability.maxGeometryShaderInvocationCount);
    logVerbose("GRAPHICS", "max geometry shader invocation count: %i", graphicsState.hardwareCapability.maxGeometryShaderInvocationCount);

    glGetIntegerv(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxGeometryShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max geometry shader storage block count: %i", graphicsState.hardwareCapability.maxGeometryShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxGeometryTextureImageUnitCount);
    logVerbose("GRAPHICS", "max geometry texture image unit count: %i", graphicsState.hardwareCapability.maxGeometryTextureImageUnitCount);

    glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &graphicsState.hardwareCapability.maxGeometryTotalOutputComponentCount);
    logVerbose("GRAPHICS", "max geometry total output component count: %i", graphicsState.hardwareCapability.maxGeometryTotalOutputComponentCount);

    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxGeometryUniformBlockCount);
    logVerbose("GRAPHICS", "max geometry uniform block count: %i", graphicsState.hardwareCapability.maxGeometryUniformBlockCount);

    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxGeometryUniformComponentCount);
    logVerbose("GRAPHICS", "max geometry uniform component count: %i", &graphicsState.hardwareCapability.maxGeometryUniformComponentCount);

    // Fragment Shader

    glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxFragmentAtomicCounterCount);
    logVerbose("GRAPHICS", "max fragment atomic counter count: %i", graphicsState.hardwareCapability.maxFragmentAtomicCounterCount);

    glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxFragmentAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max fragment atomic counter buffer count: %i", graphicsState.hardwareCapability.maxFragmentAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxFragmentCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max fragment combined uniform component count: %i", graphicsState.hardwareCapability.maxFragmentCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_FRAGMENT_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxFragmentImageUniformCount);
    logVerbose("GRAPHICS", "max fragment image uniform count: %i", graphicsState.hardwareCapability.maxFragmentImageUniformCount);

    glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &graphicsState.hardwareCapability.maxFragmentInputComponentCount);
    logVerbose("GRAPHICS", "max fragment input component count: %i", graphicsState.hardwareCapability.maxFragmentInputComponentCount);

    glGetIntegerv(GL_MAX_FRAGMENT_INTERPOLATION_OFFSET, &graphicsState.hardwareCapability.maxFragmentInterpolationOffset);
    logVerbose("GRAPHICS", "max fragment interpolation offset: %i", graphicsState.hardwareCapability.maxFragmentInterpolationOffset);

    glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxFragmentShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max fragment shader storage block count: %i", graphicsState.hardwareCapability.maxFragmentShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxFragmentUniformBlockCount);
    logVerbose("GRAPHICS", "max fragment uniform block count: %i", graphicsState.hardwareCapability.maxFragmentUniformBlockCount);

    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxFragmentUniformComponentCount);
    logVerbose("GRAPHICS", "max fragment uniform component count: %i", &graphicsState.hardwareCapability.maxFragmentUniformComponentCount);

    // Compute Shader

    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxComputeAtomicCounterCount);
    logVerbose("GRAPHICS", "max compute atomic counter count: %i", graphicsState.hardwareCapability.maxComputeAtomicCounterCount);

    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxComputeAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max compute atomic counter buffer count: %i", graphicsState.hardwareCapability.maxComputeAtomicCounterBufferCount);
    
    glGetIntegerv(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxComputeCombinedUniformComponentCount);
    logVerbose("GRAPHICS", "max compute combined uniform component count: %i", graphicsState.hardwareCapability.maxComputeCombinedUniformComponentCount);

    glGetIntegerv(GL_MAX_COMPUTE_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxComputeImageUniformCount);
    logVerbose("GRAPHICS", "max compute image uniform count: %i", graphicsState.hardwareCapability.maxComputeImageUniformCount);
    
    glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxComputeShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max compute shader storage block count: %i", graphicsState.hardwareCapability.maxComputeShaderStorageBlockCount);
    
    glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &graphicsState.hardwareCapability.maxComputeSharedMemorySize);
    logVerbose("GRAPHICS", "max compute shared memory size: %i", graphicsState.hardwareCapability.maxComputeSharedMemorySize);
    
    glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxComputeTextureImageUnitCount);
    logVerbose("GRAPHICS", "max compute texture image unit count: %i", graphicsState.hardwareCapability.maxComputeTextureImageUnitCount);

    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxComputeUniformBlockCount);
    logVerbose("GRAPHICS", "max compute uniform block count: %i", graphicsState.hardwareCapability.maxComputeUniformBlockCount);
    
    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &graphicsState.hardwareCapability.maxComputeUniformComponentCount);
    logVerbose("GRAPHICS", "max compute uniform component count: %i", graphicsState.hardwareCapability.maxComputeUniformComponentCount);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[2]);
    logVerbose("GRAPHICS", "max compute work group counts: (%i, %i, %i)", 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[0], 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[1], 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[2]);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[2]);
    logVerbose("GRAPHICS", "max compute work group sizes: (%i, %i, %i)", 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[0], 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[1], 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[2]);

    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &graphicsState.hardwareCapability.maxComputeWorkGroupInvocationCount);
    logVerbose("GRAPHICS", "max compute work group invocation count: %i", graphicsState.hardwareCapability.maxComputeWorkGroupInvocationCount);

    // All Shaders

    glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTERS, &graphicsState.hardwareCapability.maxAllAtomicCounterCount);
    logVerbose("GRAPHICS", "max all atomic counter count: %i", graphicsState.hardwareCapability.maxAllAtomicCounterCount);

    glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, &graphicsState.hardwareCapability.maxAllAtomicCounterBufferCount);
    logVerbose("GRAPHICS", "max all atomic counter buffer count: %i", graphicsState.hardwareCapability.maxAllAtomicCounterBufferCount);

    glGetIntegerv(GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES, &graphicsState.hardwareCapability.maxAllClipAndCullDistanceCount);
    logVerbose("GRAPHICS", "max all clip and cull distance count: %i", graphicsState.hardwareCapability.maxAllClipAndCullDistanceCount);

    glGetIntegerv(GL_MAX_COMBINED_IMAGE_UNIFORMS, &graphicsState.hardwareCapability.maxAllImageUniformCount);
    logVerbose("GRAPHICS", "max all image uniform count: %i", graphicsState.hardwareCapability.maxAllImageUniformCount);

    glGetIntegerv(GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS, &graphicsState.hardwareCapability.maxAllImageUnitAndFragmentOutputCount);
    logVerbose("GRAPHICS", "max all image unit and fragment output count: %i", graphicsState.hardwareCapability.maxAllImageUnitAndFragmentOutputCount);

    glGetIntegerv(GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES, &graphicsState.hardwareCapability.maxAllShaderOutputResourceCount);
    logVerbose("GRAPHICS", "max all shader output resource count: %i", graphicsState.hardwareCapability.maxAllShaderOutputResourceCount);

    glGetIntegerv(GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, &graphicsState.hardwareCapability.maxAllShaderStorageBlockCount);
    logVerbose("GRAPHICS", "max all shader storage block count: %i", graphicsState.hardwareCapability.maxAllShaderStorageBlockCount);

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxAllTextureImageUnitCount);
    logVerbose("GRAPHICS", "max all texture image unit count: %i", graphicsState.hardwareCapability.maxAllTextureImageUnitCount);

    glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &graphicsState.hardwareCapability.maxAllUniformBlockCount);
    logVerbose("GRAPHICS", "max all uniform block count: %i", graphicsState.hardwareCapability.maxAllUniformBlockCount);

    // Transform Feedback

    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_BUFFERS, &graphicsState.hardwareCapability.maxTransformFeedbackBufferCount);
    logVerbose("GRAPHICS", "max transform feedback buffer count: %i", graphicsState.hardwareCapability.maxTransformFeedbackBufferCount);

    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, &graphicsState.hardwareCapability.maxTransformFeedbackInterleavedComponentCount);
    logVerbose("GRAPHICS", "max transform feedback interleaved component count: %i", graphicsState.hardwareCapability.maxTransformFeedbackInterleavedComponentCount);

    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, &graphicsState.hardwareCapability.maxTransformFeedbackSeparateAttributeCount);
    logVerbose("GRAPHICS", "max transform feedback separate attribute count: %i", graphicsState.hardwareCapability.maxTransformFeedbackSeparateAttributeCount);

    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, &graphicsState.hardwareCapability.maxTransformFeedbackSeparateComponentCount);
    logVerbose("GRAPHICS", "max transform feedback separate component count: %i", graphicsState.hardwareCapability.maxTransformFeedbackSeparateComponentCount);

    // Debug 

    glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &graphicsState.hardwareCapability.maxDebugGroupStackDepth);
    logVerbose("GRAPHICS", "max debug group stack depth: %i", graphicsState.hardwareCapability.maxDebugGroupStackDepth);

    glGetIntegerv(GL_MAX_LABEL_LENGTH, &graphicsState.hardwareCapability.maxDebugLabelLength);
    logVerbose("GRAPHICS", "max debug label length: %i", graphicsState.hardwareCapability.maxDebugLabelLength);

    glGetIntegerv(GL_MAX_DEBUG_LOGGED_MESSAGES, &graphicsState.hardwareCapability.maxDebugLoggedMessageCount);
    logVerbose("GRAPHICS", "max debug logged message count: %i", graphicsState.hardwareCapability.maxDebugLoggedMessageCount);

    glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &graphicsState.hardwareCapability.maxDebugMessageLength);
    logVerbose("GRAPHICS", "max debug message length: %i", graphicsState.hardwareCapability.maxDebugMessageLength);
   
    // Other

    glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &graphicsState.hardwareCapability.shaderStorageBufferOffsetAlignment);
    logVerbose("GRAPHICS", "shader storage buffer offset alignment: %i", graphicsState.hardwareCapability.shaderStorageBufferOffsetAlignment);

    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &graphicsState.hardwareCapability.uniformBufferOffsetAlignment);
    logVerbose("GRAPHICS", "uniform buffer offset alignment: %i", graphicsState.hardwareCapability.uniformBufferOffsetAlignment);

    glGetIntegerv(GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, &graphicsState.hardwareCapability.textureBufferOffsetAlignment);
    logVerbose("GRAPHICS", "texture buffer offset alignment: %i", graphicsState.hardwareCapability.textureBufferOffsetAlignment);

    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &graphicsState.hardwareCapability.maxShaderStorageBlockSize);
    logVerbose("GRAPHICS", "max shader storage block size: %i", graphicsState.hardwareCapability.maxShaderStorageBlockSize);

    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &graphicsState.hardwareCapability.maxShaderStorageBufferBindingCount);
    logVerbose("GRAPHICS", "max shader storage buffer binding count: %i", graphicsState.hardwareCapability.maxShaderStorageBufferBindingCount);

    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &graphicsState.hardwareCapability.maxUniformBlockSize);
    logVerbose("GRAPHICS", "max uniform block size: %i", graphicsState.hardwareCapability.maxUniformBlockSize);

    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &graphicsState.hardwareCapability.maxUniformBufferBindingCount);
    logVerbose("GRAPHICS", "max uinform buffer binding count: %i", graphicsState.hardwareCapability.maxUniformBufferBindingCount);

    glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &graphicsState.hardwareCapability.maxUniformLocationCount);
    logVerbose("GRAPHICS", "max uniform location count: %i", graphicsState.hardwareCapability.maxUniformLocationCount);

    glGetIntegerv(GL_MAX_IMAGE_UNITS, &graphicsState.hardwareCapability.maxImageUnitCount);
    logVerbose("GRAPHICS", "max image unit count: %i", graphicsState.hardwareCapability.maxImageUnitCount);

    glGetIntegerv(GL_MAX_IMAGE_SAMPLES, &graphicsState.hardwareCapability.maxImageSampleCount);
    logVerbose("GRAPHICS", "max image sample count: %i", graphicsState.hardwareCapability.maxImageSampleCount);

    glGetIntegerv(GL_MAX_PATCH_VERTICES, &graphicsState.hardwareCapability.maxPatchVertexCount);
    logVerbose("GRAPHICS", "max patch vertex count: %i", graphicsState.hardwareCapability.maxPatchVertexCount);
}

static bool* getCapabilityStatePointer(GraphicsCapability graphicsCapability)
{
    switch (graphicsCapability)
    {
        case GraphicsCapabilityDepthTest:             return &graphicsState.depthTest.enabled;
        case GraphicsCapabilityStencilTest:           return &graphicsState.stencilTest.enabled;
        case GraphicsCapabilityScissorTest:           return &graphicsState.scissorTest.enabled;
        case GraphicsCapabilityBlend:                 return &graphicsState.blend.enabled;
        case GraphicsCapabilityCullFace:              return &graphicsState.cullFace.enabled;
        case GraphicsCapabilityDither:                return &graphicsState.dither.enabled;
        case GraphicsCapabilityMultisample:           return &graphicsState.multisample.enabled;
        case GraphicsCapabilitySampleAlphaToCoverage: return &graphicsState.sampleAlphaToCoverage.enabled;
        case GraphicsCapabilitySampleAlphaToOne:      return &graphicsState.sampleAlphaToOne.enabled;
        case GraphicsCapabilitySampleCoverage:        return &graphicsState.sampleCoverage.enabled;
        case GraphicsCapabilityDepthClamp:            return &graphicsState.depthClamp.enabled;
        case GraphicsCapabilityPolygonOffsetPoint:    return &graphicsState.polygonOffset.pointEnabled;
        case GraphicsCapabilityPolygonOffsetLine:     return &graphicsState.polygonOffset.lineEnabled;
        case GraphicsCapabilityPolygonOffsetFill:     return &graphicsState.polygonOffset.fillEnabled;
        case GraphicsCapabilityProgramPointSize:      return &graphicsState.programPointSize.enabled;
        case GraphicsCapabilityFramebufferSRGB:       return &graphicsState.framebufferSRGB.enabled;
        case GraphicsCapabilityPrimitiveRestart:      return &graphicsState.primitiveRestart.enabled;
    }

    logError("GRAPHICS", "invalid graphics capability");
    assert(0);

    return NULL;
}

bool graphicsInit(GraphicsAPILoadFunction graphicsAPILoadFunction)
{
    if (!gladLoadGLLoader(graphicsAPILoadFunction))
    {
        logError("GRAPHICS", "failed to initialise");
        return false;
    }
    logInfo("GRAPHICS", "initialised");

    logVerbose("GRAPHICS", "physical device: %s", (const char*)glGetString(GL_RENDERER));
    logVerbose("GRAPHICS", "renderer version: %s", (const char*)glGetString(GL_VERSION));
    logVerbose("GRAPHICS", "GLSL version: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    GLint contextFlagBits = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlagBits);
    if (contextFlagBits & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT) { logInfo("GRAPHICS", "forward compatibility is enabled");   }
    if (contextFlagBits & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT)      { logInfo("GRAPHICS", "robust access is enabled");           }
    if (contextFlagBits & GL_CONTEXT_FLAG_NO_ERROR_BIT)           { logInfo("GRAPHICS", "internal error checks are disabled"); }

    if (contextFlagBits & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugMessageCallback, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        logInfo("GRAPHICS", "debug output is enabled");
    }

    glGetIntegerv(GL_SAMPLES, &graphicsState.multisample.samples);
    logVerbose("GRAPHICS", "active sample count: %i", graphicsState.multisample.samples);

    getHardwareCapabilities();

    return true;
}

void graphicsEnable(GraphicsCapability graphicsCapability)
{
    bool* capabilityStatePointer = getCapabilityStatePointer(graphicsCapability);
    bool capabilityIsEnabled = *capabilityStatePointer;
    if (!capabilityIsEnabled)
    {
        *capabilityStatePointer = true;
        glEnable(graphicsCapabilityToNative(graphicsCapability));
    }
}

void graphicsDisable(GraphicsCapability graphicsCapability)
{
    bool* capabilityStatePointer = getCapabilityStatePointer(graphicsCapability);
    bool capabilityIsEnabled = *capabilityStatePointer;
    if (capabilityIsEnabled)
    {
        *capabilityStatePointer = false;
        glDisable(graphicsCapabilityToNative(graphicsCapability));
    }
}

void graphicsViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (graphicsState.viewport.x      != x     ||
        graphicsState.viewport.y      != y     ||
        graphicsState.viewport.width  != width ||
        graphicsState.viewport.height != height)
    {
        graphicsState.viewport.x      = x;
        graphicsState.viewport.y      = y;
        graphicsState.viewport.width  = width;
        graphicsState.viewport.height = height;
        glViewport(x, y, width, height);
    }
}

void graphicsDepthFunction(CompareFunction compareFunction)
{
    if (graphicsState.depthTest.compareFunction != compareFunction)
    {
        graphicsState.depthTest.compareFunction = compareFunction;
        glDepthFunc(compareFunctionToNative(compareFunction));
    }
}

void graphicsDepthWriteEnable(bool writeEnabled)
{
    if (graphicsState.depthTest.writeEnabled != writeEnabled)
    {
        graphicsState.depthTest.writeEnabled = writeEnabled;
        glDepthMask(writeEnabled);
    }
}

void graphicsDepthRange(float near, float far)
{
    if (graphicsState.depthTest.near != near ||
        graphicsState.depthTest.far  != far)
    {
        graphicsState.depthTest.near = near;
        graphicsState.depthTest.far  = far;
        glDepthRangef(near, far);
    }
}

void graphicsStencilFunction(Face face, CompareFunction compareFunction, int32_t reference, uint32_t testMask)
{
    bool dirty = false;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && 
        (front->compareFunction != compareFunction || front->reference != reference || front->testMask != testMask))
    {
        front->compareFunction = compareFunction;
        front->reference       = reference;
        front->testMask        = testMask;
        dirty = true;
    }
    if ((face == FaceBack || face == FaceBoth) && 
        (back->compareFunction != compareFunction || back->reference != reference || back->testMask != testMask))
    {
        back->compareFunction = compareFunction;
        back->reference       = reference;
        back->testMask        = testMask;
        dirty = true;
    }

    if (dirty)
    {
        glStencilFuncSeparate(faceToNative(face), compareFunctionToNative(compareFunction), reference, testMask);
    }
}

void graphicsStencilWriteMask(Face face, uint32_t writeMask)
{
    bool dirty = false;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && front->writeMask != writeMask)
    {
        front->writeMask = writeMask;
        dirty = true;
    }
    if ((face == FaceBack || face == FaceBoth) && back->writeMask != writeMask)
    {
        back->writeMask = writeMask;
        dirty = true;
    }

    if (dirty)
    {
        glStencilMaskSeparate(faceToNative(face), writeMask);
    }
}

void graphicsStencilOperation(Face face, StencilOperation stencilFail, StencilOperation depthFail, StencilOperation depthPass)
{
    bool dirty = false;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && 
        (front->stencilFail != stencilFail || front->depthFail != depthFail || front->depthPass != depthPass))
    {
        front->stencilFail = stencilFail;
        front->depthFail   = depthFail;
        front->depthPass   = depthPass;
        dirty = true;
    }

    if ((face == FaceBack || face == FaceBoth) && 
        (back->stencilFail != stencilFail || back->depthFail != depthFail || back->depthPass != depthPass))
    {
        back->stencilFail = stencilFail;
        back->depthFail   = depthFail;
        back->depthPass   = depthPass;
        dirty = true;
    }

    if (dirty)
    {
        glStencilOpSeparate(
            faceToNative(face), 
            stencilOperationToNative(stencilFail), 
            stencilOperationToNative(depthFail), 
            stencilOperationToNative(depthPass));
    }
}

void graphicsScissor(int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (graphicsState.scissorTest.x      != x     ||
        graphicsState.scissorTest.y      != y     ||
        graphicsState.scissorTest.width  != width ||
        graphicsState.scissorTest.height != height)
    {
        graphicsState.scissorTest.x      = x;
        graphicsState.scissorTest.y      = y;
        graphicsState.scissorTest.width  = width;
        graphicsState.scissorTest.height = height;
        glScissor(x, y, width, height);
    }
}

void graphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
{
    if (graphicsState.blend.srcRGB   != srcRGB   ||
        graphicsState.blend.dstRGB   != dstRGB   ||
        graphicsState.blend.srcAlpha != srcAlpha ||
        graphicsState.blend.dstAlpha != dstAlpha)
    {
        graphicsState.blend.srcRGB   = srcRGB;
        graphicsState.blend.dstRGB   = dstRGB;
        graphicsState.blend.srcAlpha = srcAlpha;
        graphicsState.blend.dstAlpha = dstAlpha;

        glBlendFuncSeparate(
            blendFactorToNative(srcRGB), 
            blendFactorToNative(dstRGB), 
            blendFactorToNative(srcAlpha), 
            blendFactorToNative(dstAlpha));
    }
}

void graphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha)
{
    if (graphicsState.blend.equationRGB   != equationRGB ||
        graphicsState.blend.equationAlpha != equationAlpha)
    {
        graphicsState.blend.equationRGB   = equationRGB;
        graphicsState.blend.equationAlpha = equationAlpha;
        glBlendEquationSeparate(blendEquationToNative(equationRGB), blendEquationToNative(equationAlpha));
    }
}

void graphicsBlendColour(vec4 colour)
{
    if (graphicsState.blend.colour[0] != colour[0] ||
        graphicsState.blend.colour[1] != colour[1] ||
        graphicsState.blend.colour[2] != colour[2] ||
        graphicsState.blend.colour[3] != colour[3])
    {
        graphicsState.blend.colour[0] = colour[0];
        graphicsState.blend.colour[1] = colour[1];
        graphicsState.blend.colour[2] = colour[2];
        graphicsState.blend.colour[3] = colour[3];
        glBlendColor(colour[0], colour[1], colour[2], colour[3]);
    }
}

void graphicsCullFace(Face face)
{
    if (graphicsState.cullFace.face != face)
    {
        graphicsState.cullFace.face = face;
        glCullFace(faceToNative(face));
    }
}

void graphicsFrontFace(FrontFace frontFace)
{
    if (graphicsState.cullFace.frontFace != frontFace)
    {
        graphicsState.cullFace.frontFace = frontFace;
        glFrontFace(frontFaceToNative(frontFace));
    }
}

void graphicsSampleCoverage(float coverage, bool invert)
{
    if (graphicsState.sampleCoverage.coverage != coverage ||
        graphicsState.sampleCoverage.invert   != invert)
    {
        graphicsState.sampleCoverage.coverage = coverage;
        graphicsState.sampleCoverage.invert   = invert;
        glSampleCoverage(coverage, invert);
    }
}

void graphicsPolygonOffset(float factor, float units)
{
    if (graphicsState.polygonOffset.factor != factor ||
        graphicsState.polygonOffset.units  != units)
    {
        graphicsState.polygonOffset.factor = factor;
        graphicsState.polygonOffset.units  = units;
        glPolygonOffset(factor, units);
    }
}

void graphicsPointSize(float size)
{
    if (graphicsState.programPointSize.size != size)
    {
        graphicsState.programPointSize.size = size;
        glPointSize(size);
    }
}

void graphicsPrimitiveRestartIndex(uint32_t restartIndex)
{
    if (graphicsState.primitiveRestart.restartIndex != restartIndex)
    {
        graphicsState.primitiveRestart.restartIndex = restartIndex;
        glPrimitiveRestartIndex(restartIndex);
    }
}

void graphicsPolygonMode(Face face, PolygonMode polygonMode)
{
    bool dirty = false;
    if ((face == FaceFront || face == FaceBoth) && graphicsState.polygon.front.mode != polygonMode)
    {
        graphicsState.polygon.front.mode = polygonMode;
        dirty = true;
    }
    if ((face == FaceBack || face == FaceBoth) && graphicsState.polygon.back.mode != polygonMode)
    {
        graphicsState.polygon.back.mode = polygonMode;
        dirty = true;
    }
    
    if (dirty)
    {
        glPolygonMode(faceToNative(face), polygonModeToNative(polygonMode));
    }
}

void graphicsClearColour(vec4 colour)
{
    if (graphicsState.clear.colour[0] != colour[0] ||
        graphicsState.clear.colour[1] != colour[1] ||
        graphicsState.clear.colour[2] != colour[2] ||
        graphicsState.clear.colour[3] != colour[3])        
    {
        graphicsState.clear.colour[0] = colour[0];
        graphicsState.clear.colour[1] = colour[1];
        graphicsState.clear.colour[2] = colour[2];
        graphicsState.clear.colour[3] = colour[3];
        glClearColor(colour[0], colour[1], colour[2], colour[3]);
    }
}

void graphicsClearDepth(double depth)
{
    if (graphicsState.clear.depth != depth)
    {
        graphicsState.clear.depth = depth;
        glClearDepth(depth);
    }
}

void graphicsClearStencil(int32_t stencil)
{
    if (graphicsState.clear.stencil != stencil)
    {
        graphicsState.clear.stencil = stencil;
        glClearStencil(stencil);
    }
}

void graphicsClear(BufferBit bufferBits)
{
    glClear(bufferBitsToNative(bufferBits));
}

void graphicsDispatchCompute(uint32_t workGroupCountX, uint32_t workGroupCountY, uint32_t workGroupCountZ)
{
    if ((GLint)workGroupCountX > graphicsState.hardwareCapability.maxComputeWorkGroupCount[0] ||
        (GLint)workGroupCountY > graphicsState.hardwareCapability.maxComputeWorkGroupCount[1] ||
        (GLint)workGroupCountZ > graphicsState.hardwareCapability.maxComputeWorkGroupCount[2])
    {
        logError("GRAPHICS", "compute work group counts (%u, %u, %u) exceed the limits (%i, %i, %i)", 
            workGroupCountX, workGroupCountY, workGroupCountZ, 
            graphicsState.hardwareCapability.maxComputeWorkGroupCount[0], 
            graphicsState.hardwareCapability.maxComputeWorkGroupCount[1], 
            graphicsState.hardwareCapability.maxComputeWorkGroupCount[2]);
        return;
    }

    glDispatchCompute(workGroupCountX, workGroupCountY, workGroupCountZ);
}

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits)
{
    glMemoryBarrier(memoryBarrierBitsToNative(memoryBarrierBits));
}

#ifndef NDEBUG
void graphicsInsertDebugMessage(DebugSource debugSource, DebugType debugType, DebugSeverity debugSeverity, const char* debugMessage)
{
    glDebugMessageInsert(
        debugSourceToNative(debugSource), 
        debugTypeToNative(debugType), 
        0, 
        debugSeverityToNative(debugSeverity), 
        -1, 
        debugMessage);
}

int32_t graphicsGetMaxDebugLabelLength(void)
{
    return graphicsState.hardwareCapability.maxDebugLabelLength;
}
#endif

