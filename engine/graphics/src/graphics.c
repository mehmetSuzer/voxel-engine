
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/graphics.h"

typedef struct Rectangle
{
    int x;
    int y;
    int width;
    int height;
} Rectangle;

typedef struct DepthTestState
{
    int enabled;
    int writeEnabled;
    float near;
    float far;
    CompareFunc compareFunc;
} DepthTestState;

typedef struct StencilTestFaceState
{
    CompareFunc compareFunc;
    int reference;
    unsigned int testMask;
    unsigned int writeMask;
    StencilOperation stencilFail;
    StencilOperation depthFail;
    StencilOperation depthPass;
} StencilTestFaceState;

typedef struct StencilTestState
{
    int enabled;
    StencilTestFaceState front;
    StencilTestFaceState back;
} StencilTestState;

typedef struct ScissorTestState
{
    int enabled;
    Rectangle rectangle;
} ScissorTestState;

typedef struct BlendState
{
    int enabled;
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
    int enabled;
    Face face;
    FrontFace frontFace;
} CullFaceState;

typedef struct DitherState
{
    int enabled;
} DitherState;

typedef struct MultisampleState
{
    int enabled;
    int samples;
} MultisampleState;

typedef struct SampleAlphaToCoverageState
{
    int enabled;
} SampleAlphaToCoverageState;

typedef struct SampleAlphaToOneState
{
    int enabled;
} SampleAlphaToOneState;

typedef struct SampleCoverageState
{
    int enabled;
    float coverage;
    int invert;
} SampleCoverageState;

typedef struct DepthClampState
{
    int enabled;
} DepthClampState;

typedef struct PolygonOffsetState
{
    int pointEnabled;
    int lineEnabled;
    int fillEnabled;
    float factor;
    float units;
} PolygonOffsetState;

typedef struct ProgramPointSizeState
{
    int enabled;
    float size;
} ProgramPointSizeState;

typedef struct FramebufferSRGBState
{
    int enabled;
} FramebufferSRGBState;

typedef struct PrimitiveRestartState
{
    int enabled;
    unsigned int restartIndex;
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
    unsigned int stencil;
} ClearState;

typedef struct ComputeState
{
    ivec3 maxWorkGroupCount;
    ivec3 maxWorkGroupSize;
    int maxWorkGroupInvocationCount;
} ComputeState;

typedef struct GraphicsState
{
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
    ComputeState compute;
} GraphicsState;

static GraphicsState graphicsState = {
    .viewport = {0, 0, 0, 0},
    .depthTest = {
        .enabled = 0,
        .writeEnabled = 1,
        .near = 0.0f,
        .far  = 1.0f,
        .compareFunc = CompareFuncLess,
    },
    .stencilTest = {
        .enabled = 0,
        .front = {
            .compareFunc = CompareFuncAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFFu,
            .writeMask = 0xFFFFFFFFu,
            .stencilFail = StencilOperationKeep,
            .depthFail   = StencilOperationKeep,
            .depthPass   = StencilOperationKeep,
        },
        .back = {
            .compareFunc = CompareFuncAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFFu,
            .writeMask = 0xFFFFFFFFu,
            .stencilFail = StencilOperationKeep,
            .depthFail   = StencilOperationKeep,
            .depthPass   = StencilOperationKeep,
        },
    },
    .scissorTest = {
        .enabled = 0,
        .rectangle = {0, 0, 0, 0},
    },
    .blend = {
        .enabled = 0,
        .srcRGB   = BlendFactorOne,
        .dstRGB   = BlendFactorZero,
        .srcAlpha = BlendFactorOne,
        .dstAlpha = BlendFactorZero,
        .equationRGB   = BlendEquationAdd,
        .equationAlpha = BlendEquationAdd,
        .colour = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .cullFace = {
        .enabled = 0,
        .face = FaceBack,
        .frontFace = FrontFaceCCW,
    },
    .dither = {
        .enabled = 0,
    },
    .multisample = {
        .enabled = 1,
        .samples = 1,
    },
    .sampleAlphaToCoverage = {
        .enabled = 0,
    },
    .sampleAlphaToOne = {
        .enabled = 0,
    },
    .sampleCoverage = {
        .enabled = 0,
        .coverage = 1.0f,
        .invert = 0,
    },
    .depthClamp = {
        .enabled = 0,
    },
    .polygonOffset = {
        .pointEnabled = 0,
        .lineEnabled = 0,
        .fillEnabled = 0,
        .factor = 0.0f,
        .units = 0.0f,
    },
    .programPointSize = {
        .enabled = 0,
        .size = 1.0f,
    },
    .framebufferSRGB = {
        .enabled = 0,
    },
    .primitiveRestart = {
        .enabled = 0,
        .restartIndex = 0xFFFFFFFFu,
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
        .stencil = 0u,
    },
    .compute = {
        .maxWorkGroupCount = {0, 0, 0},
        .maxWorkGroupSize  = {0, 0, 0},
        .maxWorkGroupInvocationCount = 0,
    },
};

static int* getCapabilityStatePointer(Capability capability)
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

void graphicsInit(GraphicsFunctionLoader graphicsFunctionLoader)
{
    if (!gladLoadGLLoader(graphicsFunctionLoader))
    {
        logError("GRAPHICS", "failed to initialise");
        return;
    }
    logInfo("GRAPHICS", "initialised");

    logInfo("GRAPHICS", "physical device: %s", (const char*)glGetString(GL_RENDERER));
    logInfo("GRAPHICS", "renderer version: %s", (const char*)glGetString(GL_VERSION));
    logInfo("GRAPHICS", "GLSL version: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGetIntegerv(GL_SAMPLES, &graphicsState.multisample.samples);
    logInfo("GRAPHICS", "MSAA %i sample(s)", graphicsState.multisample.samples);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0u, &graphicsState.compute.maxWorkGroupCount[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1u, &graphicsState.compute.maxWorkGroupCount[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2u, &graphicsState.compute.maxWorkGroupCount[2]);
    logInfo("GRAPHICS", "max compute work group counts: (%i, %i, %i)", 
        graphicsState.compute.maxWorkGroupCount[0], graphicsState.compute.maxWorkGroupCount[1], graphicsState.compute.maxWorkGroupCount[2]);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0u, &graphicsState.compute.maxWorkGroupSize[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1u, &graphicsState.compute.maxWorkGroupSize[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2u, &graphicsState.compute.maxWorkGroupSize[2]);
    logInfo("GRAPHICS", "max compute work group sizes: (%i, %i, %i)", 
        graphicsState.compute.maxWorkGroupSize[0], graphicsState.compute.maxWorkGroupSize[1], graphicsState.compute.maxWorkGroupSize[2]);

    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &graphicsState.compute.maxWorkGroupInvocationCount);
    logInfo("GRAPHICS", "max compute work group invocation count: %i", graphicsState.compute.maxWorkGroupInvocationCount);
}

void graphicsEnable(Capability capability)
{
    int* capabilityStatePointer = getCapabilityStatePointer(capability);
    if (!(*capabilityStatePointer))
    {
        *capabilityStatePointer = 1;
        glEnable(capabilityToNative(capability));
        glCheckErrors();
    }
}

void graphicsDisable(Capability capability)
{
    int* capabilityStatePointer = getCapabilityStatePointer(capability);
    if (*capabilityStatePointer)
    {
        *capabilityStatePointer = 0;
        glDisable(capabilityToNative(capability));
        glCheckErrors();
    }
}

void graphicsViewport(int x, int y, int width, int height)
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

void graphicsDepthWriteEnable(int writeEnabled)
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

void graphicsStencilFunc(Face face, CompareFunc compareFunc, int reference, unsigned int testMask)
{
    int dirty = 0;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && (front->compareFunc != compareFunc || front->reference != reference || front->testMask != testMask))
    {
        front->compareFunc = compareFunc;
        front->reference   = reference;
        front->testMask    = testMask;
        dirty = 1;
    }
    if ((face == FaceBack || face == FaceBoth) && (back->compareFunc != compareFunc || back->reference != reference || back->testMask != testMask))
    {
        back->compareFunc = compareFunc;
        back->reference   = reference;
        back->testMask    = testMask;
        dirty = 1;
    }

    if (dirty)
    {
        glStencilFuncSeparate(faceToNative(face), compareFuncToNative(compareFunc), reference, testMask);
        glCheckErrors();
    }
}

void graphicsStencilWriteMask(Face face, unsigned int writeMask)
{
    int dirty = 0;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && front->writeMask != writeMask)
    {
        front->writeMask = writeMask;
        dirty = 1;
    }
    if ((face == FaceBack || face == FaceBoth) && back->writeMask != writeMask)
    {
        back->writeMask = writeMask;
        dirty = 1;
    }

    if (dirty)
    {
        glStencilMaskSeparate(faceToNative(face), writeMask);
        glCheckErrors();
    }
}

void graphicsStencilOperation(Face face, StencilOperation stencilFail, StencilOperation depthFail, StencilOperation depthPass)
{
    int dirty = 0;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && (front->stencilFail != stencilFail || front->depthFail != depthFail || front->depthPass != depthPass))
    {
        front->stencilFail = stencilFail;
        front->depthFail   = depthFail;
        front->depthPass   = depthPass;
        dirty = 1;
    }

    if ((face == FaceBack || face == FaceBoth) && (back->stencilFail != stencilFail || back->depthFail != depthFail || back->depthPass != depthPass))
    {
        back->stencilFail = stencilFail;
        back->depthFail   = depthFail;
        back->depthPass   = depthPass;
        dirty = 1;
    }

    if (dirty)
    {
        glStencilOpSeparate(faceToNative(face), stencilOperationToNative(stencilFail), stencilOperationToNative(depthFail), stencilOperationToNative(depthPass));
        glCheckErrors();
    }
}

void graphicsScissor(int x, int y, int width, int height)
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

void graphicsSampleCoverage(float coverage, int invert)
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

void graphicsPrimitiveRestartIndex(unsigned int restartIndex)
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
    int dirty = 0;
    if ((face == FaceFront || face == FaceBoth) && graphicsState.polygon.front.mode != polygonMode)
    {
        graphicsState.polygon.front.mode = polygonMode;
        dirty = 1;
    }
    if ((face == FaceBack || face == FaceBoth) && graphicsState.polygon.back.mode != polygonMode)
    {
        graphicsState.polygon.back.mode = polygonMode;
        dirty = 1;
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

void graphicsClearStencil(unsigned int stencil)
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

void graphicsDispatchCompute(int workGroupCountX, int workGroupCountY, int workGroupCountZ)
{
    if (workGroupCountX > graphicsState.compute.maxWorkGroupCount[0] ||
        workGroupCountY > graphicsState.compute.maxWorkGroupCount[1] ||
        workGroupCountZ > graphicsState.compute.maxWorkGroupCount[2])
    {
        logError("GRAPHICS", "work group counts (%i, %i, %i) exceed the limits (%i, %i, %i)", workGroupCountX, workGroupCountY, workGroupCountZ, 
            graphicsState.compute.maxWorkGroupCount[0], graphicsState.compute.maxWorkGroupCount[1], graphicsState.compute.maxWorkGroupCount[2]);
        return;
    }

    glDispatchCompute((GLuint)workGroupCountX, (GLuint)workGroupCountY, (GLuint)workGroupCountZ);
    glCheckErrors();
}

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits)
{
    glMemoryBarrier(memoryBarrierBitsToNative(memoryBarrierBits));
    glCheckErrors();
}

