
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/graphics.h"

typedef struct HardwareCapabilityState
{
    int32_t maxViewportCount;
    ivec2 maxViewportDimensions;

    int32_t maxVertexAttributeCount;
    int32_t maxElementsIndexCount;
    int32_t maxElementsVertexCount;

    int32_t maxSampleCount;
    int32_t maxDrawBufferCount;
    int32_t maxColourAttachmentCount;

    int32_t maxTextureSize;
    int32_t max3DTextureSize;
    int32_t maxTextureImageUnitCount;
    int32_t maxCombinedTextureImageUnitCount;
    float maxTextureMaxAnisotropy;

    int32_t maxUniformBlockSize;
    int32_t maxShaderStorageBlockSize;

    int32_t maxUniformBufferBindingCount;
    int32_t maxShaderStorageBufferBindingCount;

    int32_t uniformBufferOffsetAlignment;
    int32_t shaderStorageBufferOffsetAlignment;

    int32_t maxDebugMessageLength;
    int32_t maxDebugLoggedMessageCount;
    int32_t maxDebugGroupStackDepth;

    ivec3 maxComputeWorkGroupCount;
    ivec3 maxComputeWorkGroupSize;
    int32_t maxComputeWorkGroupInvocationCount;
    int32_t maxComputeSharedMemorySize;
} HardwareCapabilityState;

typedef struct Rectangle
{
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
} Rectangle;

typedef struct DepthTestState
{
    bool enabled;
    bool writeEnabled;
    float near;
    float far;
    CompareFunc compareFunc;
} DepthTestState;

typedef struct StencilTestFaceState
{
    CompareFunc compareFunc;
    int32_t reference;
    uint32_t testMask;
    uint32_t writeMask;
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
    Rectangle rectangle;
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
    vec4 colour;
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
    int32_t samples;
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
    bool invert;
    float coverage;
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
    float factor;
    float units;
} PolygonOffsetState;

typedef struct ProgramPointSizeState
{
    bool enabled;
    float size;
} ProgramPointSizeState;

typedef struct FramebufferSRGBState
{
    bool enabled;
} FramebufferSRGBState;

typedef struct PrimitiveRestartState
{
    bool enabled;
    uint32_t restartIndex;
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
    vec4 colour;
    float depth;
    int32_t stencil;
} ClearState;

typedef struct GraphicsState
{
    HardwareCapabilityState hardwareCapability;
    Rectangle viewport;
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
    .viewport = {0, 0, 0, 0},
    .depthTest = {
        .enabled = false,
        .writeEnabled = true,
        .near = 0.0f,
        .far  = 1.0f,
        .compareFunc = CompareFuncLess,
    },
    .stencilTest = {
        .enabled = false,
        .front = {
            .compareFunc = CompareFuncAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFF,
            .writeMask = 0xFFFFFFFF,
            .stencilFail = StencilOperationKeep,
            .depthFail   = StencilOperationKeep,
            .depthPass   = StencilOperationKeep,
        },
        .back = {
            .compareFunc = CompareFuncAlways,
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
        .rectangle = {0, 0, 0, 0},
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
        .invert = false,
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

static bool* getCapabilityStatePointer(Capability capability)
{
    switch (capability)
    {
    case CapabilityDepthTest:
        return &graphicsState.depthTest.enabled;
    case CapabilityStencilTest:
        return &graphicsState.stencilTest.enabled;
    case CapabilityScissorTest:
        return &graphicsState.scissorTest.enabled;
    case CapabilityBlend:
        return &graphicsState.blend.enabled;
    case CapabilityCullFace:
        return &graphicsState.cullFace.enabled;
    case CapabilityDither:
        return &graphicsState.dither.enabled;
    case CapabilityMultisample:
        return &graphicsState.multisample.enabled;
    case CapabilitySampleAlphaToCoverage:
        return &graphicsState.sampleAlphaToCoverage.enabled;
    case CapabilitySampleAlphaToOne:
        return &graphicsState.sampleAlphaToOne.enabled;
    case CapabilitySampleCoverage:
        return &graphicsState.sampleCoverage.enabled;
    case CapabilityDepthClamp:
        return &graphicsState.depthClamp.enabled;
    case CapabilityPolygonOffsetPoint:
        return &graphicsState.polygonOffset.pointEnabled;
    case CapabilityPolygonOffsetLine:
        return &graphicsState.polygonOffset.lineEnabled;
    case CapabilityPolygonOffsetFill:
        return &graphicsState.polygonOffset.fillEnabled;
    case CapabilityProgramPointSize:
        return &graphicsState.programPointSize.enabled;
    case CapabilityFramebufferSRGB:
        return &graphicsState.framebufferSRGB.enabled;
    case CapabilityPrimitiveRestart:
        return &graphicsState.primitiveRestart.enabled;
    default:
        return NULL;
    }
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

    glGetIntegerv(GL_SAMPLES, &graphicsState.multisample.samples);
    logInfo("GRAPHICS", "active MSAA sample count: %i", graphicsState.multisample.samples);

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

    glGetIntegerv(GL_MAX_SAMPLES, &graphicsState.hardwareCapability.maxSampleCount);
    logInfo("GRAPHICS", "max MSAA sample count: %i", graphicsState.hardwareCapability.maxSampleCount);

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
    
    glCheckErrors();

    return true;
}

void graphicsEnable(Capability capability)
{
    bool* capabilityStatePointer = getCapabilityStatePointer(capability);
    if (capabilityStatePointer == NULL)
    {
        logError("GRAPHICS", "cannot enable, capability is invalid");
        return;
    }

    bool capabilityIsEnabled = *capabilityStatePointer;
    if (!capabilityIsEnabled)
    {
        *capabilityStatePointer = true;
        glEnable(capabilityToNative(capability));
        glCheckErrors();
    }
}

void graphicsDisable(Capability capability)
{
    bool* capabilityStatePointer = getCapabilityStatePointer(capability);
    if (capabilityStatePointer == NULL)
    {
        logError("GRAPHICS", "cannot disable, capability is invalid");
        return;
    }

    bool capabilityIsEnabled = *capabilityStatePointer;
    if (capabilityIsEnabled)
    {
        *capabilityStatePointer = false;
        glDisable(capabilityToNative(capability));
        glCheckErrors();
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
        glCheckErrors();
    }
}

void graphicsDepthFunc(CompareFunc compareFunc)
{
    if (graphicsState.depthTest.compareFunc != compareFunc)
    {
        graphicsState.depthTest.compareFunc = compareFunc;
        glDepthFunc(compareFuncToNative(compareFunc));
        glCheckErrors();
    }
}

void graphicsDepthWriteEnable(bool writeEnabled)
{
    if (graphicsState.depthTest.writeEnabled != writeEnabled)
    {
        graphicsState.depthTest.writeEnabled = writeEnabled;
        glDepthMask(writeEnabled);
        glCheckErrors();
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
        glCheckErrors();
    }
}

void graphicsStencilFunc(Face face, CompareFunc compareFunc, int32_t reference, uint32_t testMask)
{
    bool dirty = false;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && (front->compareFunc != compareFunc || front->reference != reference || front->testMask != testMask))
    {
        front->compareFunc = compareFunc;
        front->reference   = reference;
        front->testMask    = testMask;
        dirty = true;
    }
    if ((face == FaceBack || face == FaceBoth) && (back->compareFunc != compareFunc || back->reference != reference || back->testMask != testMask))
    {
        back->compareFunc = compareFunc;
        back->reference   = reference;
        back->testMask    = testMask;
        dirty = true;
    }

    if (dirty)
    {
        glStencilFuncSeparate(faceToNative(face), compareFuncToNative(compareFunc), reference, testMask);
        glCheckErrors();
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
        glCheckErrors();
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
        glStencilOpSeparate(faceToNative(face), stencilOperationToNative(stencilFail), stencilOperationToNative(depthFail), stencilOperationToNative(depthPass));
        glCheckErrors();
    }
}

void graphicsScissor(int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (graphicsState.scissorTest.rectangle.x      != x     ||
        graphicsState.scissorTest.rectangle.y      != y     ||
        graphicsState.scissorTest.rectangle.width  != width ||
        graphicsState.scissorTest.rectangle.height != height)
    {
        graphicsState.scissorTest.rectangle.x      = x;
        graphicsState.scissorTest.rectangle.y      = y;
        graphicsState.scissorTest.rectangle.width  = width;
        graphicsState.scissorTest.rectangle.height = height;
        glScissor(x, y, width, height);
        glCheckErrors();
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
        glCheckErrors();
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
        glCheckErrors();
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
        glCheckErrors();
    }
}

void graphicsCullFace(Face face)
{
    if (graphicsState.cullFace.face != face)
    {
        graphicsState.cullFace.face = face;
        glCullFace(faceToNative(face));
        glCheckErrors();
    }
}

void graphicsFrontFace(FrontFace frontFace)
{
    if (graphicsState.cullFace.frontFace != frontFace)
    {
        graphicsState.cullFace.frontFace = frontFace;
        glFrontFace(frontFaceToNative(frontFace));
        glCheckErrors();
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
        glCheckErrors();
    }
}

void graphicsPolygonOffset(float factor, float units)
{
    if (graphicsState.polygonOffset.factor != factor ||
        graphicsState.polygonOffset.units != units)
    {
        graphicsState.polygonOffset.factor = factor;
        graphicsState.polygonOffset.units  = units;
        glPolygonOffset(factor, units);
        glCheckErrors();
    }
}

void graphicsPointSize(float size)
{
    if (graphicsState.programPointSize.size != size)
    {
        graphicsState.programPointSize.size = size;
        glPointSize(size);
        glCheckErrors();
    }
}

void graphicsPrimitiveRestartIndex(uint32_t restartIndex)
{
    if (graphicsState.primitiveRestart.restartIndex != restartIndex)
    {
        graphicsState.primitiveRestart.restartIndex = restartIndex;
        glPrimitiveRestartIndex(restartIndex);
        glCheckErrors();
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
        glCheckErrors();
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
        glCheckErrors();        
    }
}

void graphicsClearDepth(float depth)
{
    if (graphicsState.clear.depth != depth)
    {
        graphicsState.clear.depth = depth;
        glClearDepth(depth);
        glCheckErrors();
    }
}

void graphicsClearStencil(int32_t stencil)
{
    if (graphicsState.clear.stencil != stencil)
    {
        graphicsState.clear.stencil = stencil;
        glClearStencil(stencil);
        glCheckErrors();
    }
}

void graphicsClear(BufferBit bufferBits)
{
    glClear(bufferBitsToNative(bufferBits));
    glCheckErrors();
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
    glCheckErrors();
}

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits)
{
    glMemoryBarrier(memoryBarrierBitsToNative(memoryBarrierBits));
    glCheckErrors();
}

