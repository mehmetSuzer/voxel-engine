
#include "utils/macros.h"
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/graphics.h"

typedef struct HardwareCapabilityState
{
    GLint maxViewportCount;
    GLint maxViewportDimensions[2];

    GLint maxVertexAttributeCount;
    GLint maxElementsIndexCount;
    GLint maxElementsVertexCount;

    GLint maxMSAASampleCount;
    GLint maxDrawBufferCount;
    GLint maxColourAttachmentCount;

    GLint maxTextureSize;
    GLint max3DTextureSize;
    GLint maxTextureImageUnitCount;
    GLint maxCombinedTextureImageUnitCount;
    GLfloat maxTextureMaxAnisotropy;

    GLint maxUniformBlockSize;
    GLint maxShaderStorageBlockSize;

    GLint maxUniformBufferBindingCount;
    GLint maxShaderStorageBufferBindingCount;

    GLint uniformBufferOffsetAlignment;
    GLint shaderStorageBufferOffsetAlignment;

    GLint maxDebugMessageLength;
    GLint maxDebugLoggedMessageCount;
    GLint maxDebugGroupStackDepth;

    GLint maxComputeWorkGroupCount[3];
    GLint maxComputeWorkGroupSize[3];
    GLint maxComputeWorkGroupInvocationCount;
    GLint maxComputeSharedMemorySize;
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
    UNUSED(messageLength); UNUSED(userParameters);

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
    glGetIntegerv(GL_MAX_VIEWPORTS, &graphicsState.hardwareCapability.maxViewportCount);
    logInfo("GRAPHICS", "max viewport count: %i", graphicsState.hardwareCapability.maxViewportCount);

    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, graphicsState.hardwareCapability.maxViewportDimensions);
    logInfo("GRAPHICS", "max viewport dimensions: (%i, %i)", 
        graphicsState.hardwareCapability.maxViewportDimensions[0],
        graphicsState.hardwareCapability.maxViewportDimensions[1]);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &graphicsState.hardwareCapability.maxVertexAttributeCount);
    logInfo("GRAPHICS", "max vertex attribute count: %i", graphicsState.hardwareCapability.maxVertexAttributeCount);

    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &graphicsState.hardwareCapability.maxElementsIndexCount);
    logInfo("GRAPHICS", "max elements index count: %i", graphicsState.hardwareCapability.maxElementsIndexCount);

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &graphicsState.hardwareCapability.maxElementsVertexCount);
    logInfo("GRAPHICS", "max elements vertex count: %i", graphicsState.hardwareCapability.maxElementsVertexCount);

    glGetIntegerv(GL_MAX_SAMPLES, &graphicsState.hardwareCapability.maxMSAASampleCount);
    logInfo("GRAPHICS", "max MSAA sample count: %i", graphicsState.hardwareCapability.maxMSAASampleCount);

    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &graphicsState.hardwareCapability.maxDrawBufferCount);
    logInfo("GRAPHICS", "max draw buffer count: %i", graphicsState.hardwareCapability.maxDrawBufferCount);

    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &graphicsState.hardwareCapability.maxColourAttachmentCount);
    logInfo("GRAPHICS", "max colour attachment count: %i", graphicsState.hardwareCapability.maxColourAttachmentCount);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &graphicsState.hardwareCapability.maxTextureSize);
    logInfo("GRAPHICS", "max texture size: %i", graphicsState.hardwareCapability.maxTextureSize);

    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &graphicsState.hardwareCapability.max3DTextureSize);
    logInfo("GRAPHICS", "max 3D texture size: %i", graphicsState.hardwareCapability.max3DTextureSize);

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxTextureImageUnitCount);
    logInfo("GRAPHICS", "max texture image unit count: %i", graphicsState.hardwareCapability.maxTextureImageUnitCount);

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &graphicsState.hardwareCapability.maxCombinedTextureImageUnitCount);
    logInfo("GRAPHICS", "max combined texture image unit count: %i", graphicsState.hardwareCapability.maxCombinedTextureImageUnitCount);

    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &graphicsState.hardwareCapability.maxTextureMaxAnisotropy);
    logInfo("GRAPHICS", "max texture max anisotropy: %.1f", graphicsState.hardwareCapability.maxTextureMaxAnisotropy);

    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &graphicsState.hardwareCapability.maxUniformBlockSize);
    logInfo("GRAPHICS", "max uniform block size: %i", graphicsState.hardwareCapability.maxUniformBlockSize);

    glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &graphicsState.hardwareCapability.maxShaderStorageBlockSize);
    logInfo("GRAPHICS", "max shader storage block size: %i", graphicsState.hardwareCapability.maxShaderStorageBlockSize);

    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &graphicsState.hardwareCapability.maxUniformBufferBindingCount);
    logInfo("GRAPHICS", "max uniform buffer binding count: %i", graphicsState.hardwareCapability.maxUniformBufferBindingCount);

    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &graphicsState.hardwareCapability.maxShaderStorageBufferBindingCount);
    logInfo("GRAPHICS", "max shader storage buffer binding count: %i", graphicsState.hardwareCapability.maxShaderStorageBufferBindingCount);

    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &graphicsState.hardwareCapability.uniformBufferOffsetAlignment);
    logInfo("GRAPHICS", "uniform buffer offset alignment: %i", graphicsState.hardwareCapability.uniformBufferOffsetAlignment);

    glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &graphicsState.hardwareCapability.shaderStorageBufferOffsetAlignment);
    logInfo("GRAPHICS", "shader storage buffer offset alignment: %i", graphicsState.hardwareCapability.shaderStorageBufferOffsetAlignment);

    glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &graphicsState.hardwareCapability.maxDebugMessageLength);
    logInfo("GRAPHICS", "max debug message length: %i", graphicsState.hardwareCapability.maxDebugMessageLength);

    glGetIntegerv(GL_MAX_DEBUG_LOGGED_MESSAGES, &graphicsState.hardwareCapability.maxDebugLoggedMessageCount);
    logInfo("GRAPHICS", "max debug logged message count: %i", graphicsState.hardwareCapability.maxDebugLoggedMessageCount);

    glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &graphicsState.hardwareCapability.maxDebugGroupStackDepth);
    logInfo("GRAPHICS", "max debug group stack depth: %i", graphicsState.hardwareCapability.maxDebugGroupStackDepth);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &graphicsState.hardwareCapability.maxComputeWorkGroupCount[2]);
    logInfo("GRAPHICS", "max compute work group counts: (%i, %i, %i)", 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[0], 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[1], 
        graphicsState.hardwareCapability.maxComputeWorkGroupCount[2]);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &graphicsState.hardwareCapability.maxComputeWorkGroupSize[2]);
    logInfo("GRAPHICS", "max compute work group sizes: (%i, %i, %i)", 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[0], 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[1], 
        graphicsState.hardwareCapability.maxComputeWorkGroupSize[2]);

    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &graphicsState.hardwareCapability.maxComputeWorkGroupInvocationCount);
    logInfo("GRAPHICS", "max compute work group invocation count: %i", graphicsState.hardwareCapability.maxComputeWorkGroupInvocationCount);

    glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &graphicsState.hardwareCapability.maxComputeSharedMemorySize);
    logInfo("GRAPHICS", "max compute shared memory size: %i", graphicsState.hardwareCapability.maxComputeSharedMemorySize);
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

bool graphicsInit(GraphicsFunctionLoader graphicsFunctionLoader)
{
    if (!gladLoadGLLoader(graphicsFunctionLoader))
    {
        logError("GRAPHICS", "failed to initialise");
        return false;
    }
    logInfo("GRAPHICS", "initialised");

    logInfo("GRAPHICS", "physical device: %s", (const char*)glGetString(GL_RENDERER));
    logInfo("GRAPHICS", "renderer version: %s", (const char*)glGetString(GL_VERSION));
    logInfo("GRAPHICS", "GLSL version: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

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
    logInfo("GRAPHICS", "active MSAA sample count: %i", graphicsState.multisample.samples);

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

    if ((face == FaceFront || face == FaceBoth) && (front->compareFunction != compareFunction || front->reference != reference || front->testMask != testMask))
    {
        front->compareFunction = compareFunction;
        front->reference       = reference;
        front->testMask        = testMask;
        dirty = true;
    }
    if ((face == FaceBack || face == FaceBoth) && (back->compareFunction != compareFunction || back->reference != reference || back->testMask != testMask))
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

    if ((face == FaceFront || face == FaceBoth) && (front->stencilFail != stencilFail || front->depthFail != depthFail || front->depthPass != depthPass))
    {
        front->stencilFail = stencilFail;
        front->depthFail   = depthFail;
        front->depthPass   = depthPass;
        dirty = true;
    }

    if ((face == FaceBack || face == FaceBoth) && (back->stencilFail != stencilFail || back->depthFail != depthFail || back->depthPass != depthPass))
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
        glBlendFuncSeparate(blendFactorToNative(srcRGB), blendFactorToNative(dstRGB), blendFactorToNative(srcAlpha), blendFactorToNative(dstAlpha));
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
    if (workGroupCountX > graphicsState.hardwareCapability.maxComputeWorkGroupCount[0] ||
        workGroupCountY > graphicsState.hardwareCapability.maxComputeWorkGroupCount[1] ||
        workGroupCountZ > graphicsState.hardwareCapability.maxComputeWorkGroupCount[2])
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
    glDebugMessageInsert(debugSourceToNative(debugSource), debugTypeToNative(debugType), 0, debugSeverityToNative(debugSeverity), -1, debugMessage);
}
#endif

