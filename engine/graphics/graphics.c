
#include "log/log.h"
#include "error.h"
#include "graphics.h"

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
    TestFunc func;
} DepthTestState;

typedef struct StencilTestFaceState
{
    TestFunc func;
    int reference;
    unsigned int testMask;
    unsigned int writeMask;
    StencilOp stencilFail;
    StencilOp depthFail;
    StencilOp depthPass;
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
    FrontFace front;
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
    unsigned int index;
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
} GraphicsState;

static GraphicsState graphicsState = {
    .viewport = {0, 0, 0, 0},
    .depthTest = {
        .enabled = 0,
        .writeEnabled = 1,
        .near = 0.0f,
        .far  = 1.0f,
        .func = TestFuncLess,
    },
    .stencilTest = {
        .enabled = 0,
        .front = {
            .func = TestFuncAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFFu,
            .writeMask = 0xFFFFFFFFu,
            .stencilFail = StencilOpKeep,
            .depthFail   = StencilOpKeep,
            .depthPass   = StencilOpKeep,
        },
        .back = {
            .func = TestFuncAlways,
            .reference = 0,
            .testMask = 0xFFFFFFFFu,
            .writeMask = 0xFFFFFFFFu,
            .stencilFail = StencilOpKeep,
            .depthFail   = StencilOpKeep,
            .depthPass   = StencilOpKeep,
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
        .front = FrontFaceCCW,
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
        .index = 0xFFFFFFFFu,
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
    }
};

static int* GetCapabilityStatePointer(Capability capability)
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

void GraphicsInit(GLADloadproc loader)
{
    if (!gladLoadGLLoader(loader))
    {
        LogError("GRAPHICS", "failed to initialise");
        exit(EXIT_FAILURE);
    }

    glGetIntegerv(GL_SAMPLES, &graphicsState.multisample.samples);
    LogInfo("GRAPHICS", "MSAA %i sample(s)", graphicsState.multisample.samples);
}

void GraphicsEnable(Capability capability)
{
    int* statePtr = GetCapabilityStatePointer(capability);
    if (!(*statePtr))
    {
        *statePtr = 1;
        glEnable((GLenum)capability);
        glCheckErrors();
    }
}

void GraphicsDisable(Capability capability)
{
    int* statePtr = GetCapabilityStatePointer(capability);
    if (*statePtr)
    {
        *statePtr = 0;
        glDisable((GLenum)capability);
        glCheckErrors();
    }
}

void GraphicsViewport(int x, int y, int width, int height)
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

void GraphicsDepthFunc(TestFunc func)
{
    if (graphicsState.depthTest.func != func)
    {
        graphicsState.depthTest.func = func;
        glDepthFunc((GLenum)func);
        glCheckErrors();
    }
}

void GraphicsDepthWriteEnable(int writeEnabled)
{
    if (graphicsState.depthTest.writeEnabled != writeEnabled)
    {
        graphicsState.depthTest.writeEnabled = writeEnabled;
        glDepthMask((GLboolean)writeEnabled);
        glCheckErrors();
    }
}

void GraphicsDepthRange(float near, float far)
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

void GraphicsStencilFunc(Face face, TestFunc func, int reference, unsigned int testMask)
{
    int dirty = 0;
    StencilTestFaceState* front = &graphicsState.stencilTest.front;
    StencilTestFaceState* back  = &graphicsState.stencilTest.back;

    if ((face == FaceFront || face == FaceBoth) && (front->func != func || front->reference != reference || front->testMask != testMask))
    {
        front->func      = func;
        front->reference = reference;
        front->testMask  = testMask;
        dirty = 1;
    }
    if ((face == FaceBack || face == FaceBoth) && (back->func != func || back->reference != reference || back->testMask != testMask))
    {
        back->func      = func;
        back->reference = reference;
        back->testMask  = testMask;
        dirty = 1;
    }

    if (dirty)
    {
        glStencilFuncSeparate((GLenum)face, (GLenum)func, reference, testMask);
        glCheckErrors();
    }
}

void GraphicsStencilWriteMask(Face face, unsigned int writeMask)
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
        glStencilMaskSeparate((GLenum)face, writeMask);
        glCheckErrors();
    }
}

void GraphicsStencilOp(Face face, StencilOp stencilFail, StencilOp depthFail, StencilOp depthPass)
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
        glStencilOpSeparate((GLenum)face, (GLenum)stencilFail, (GLenum)depthFail, (GLenum)depthPass);
        glCheckErrors();
    }
}

void GraphicsScissor(int x, int y, int width, int height)
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

void GraphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
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
        glBlendFuncSeparate((GLenum)srcRGB, (GLenum)dstRGB, (GLenum)srcAlpha, (GLenum)dstAlpha);
        glCheckErrors();
    }
}

void GraphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha)
{
    if (graphicsState.blend.equationRGB   != equationRGB ||
        graphicsState.blend.equationAlpha != equationAlpha)
    {
        graphicsState.blend.equationRGB   = equationRGB;
        graphicsState.blend.equationAlpha = equationAlpha;
        glBlendEquationSeparate((GLenum)equationRGB, (GLenum)equationAlpha);
        glCheckErrors();
    }
}

void GraphicsBlendColour(vec4 colour)
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

void GraphicsCullFace(Face face)
{
    if (graphicsState.cullFace.face != face)
    {
        graphicsState.cullFace.face = face;
        glCullFace((GLenum)face);
        glCheckErrors();
    }
}

void GraphicsFrontFace(FrontFace front)
{
    if (graphicsState.cullFace.front != front)
    {
        graphicsState.cullFace.front = front;
        glFrontFace((GLenum)front);
        glCheckErrors();
    }
}

void GraphicsSampleCoverage(float coverage, int invert)
{
    if (graphicsState.sampleCoverage.coverage != coverage ||
        graphicsState.sampleCoverage.invert   != invert)
    {
        graphicsState.sampleCoverage.coverage = coverage;
        graphicsState.sampleCoverage.invert   = invert;
        glSampleCoverage(coverage, (GLboolean)invert);
        glCheckErrors();
    }
}

void GraphicsPolygonOffset(float factor, float units)
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

void GraphicsPointSize(float size)
{
    if (graphicsState.programPointSize.size != size)
    {
        graphicsState.programPointSize.size = size;
        glPointSize(size);
        glCheckErrors();
    }
}

void GraphicsPrimitiveRestartIndex(unsigned int index)
{
    if (graphicsState.primitiveRestart.index != index)
    {
        graphicsState.primitiveRestart.index = index;
        glPrimitiveRestartIndex(index);
        glCheckErrors();
    }
}

void GraphicsPolygonMode(Face face, PolygonMode mode)
{
    int dirty = 0;
    if ((face == FaceFront || face == FaceBoth) && graphicsState.polygon.front.mode != mode)
    {
        graphicsState.polygon.front.mode = mode;
        dirty = 1;
    }
    if ((face == FaceBack || face == FaceBoth) && graphicsState.polygon.back.mode != mode)
    {
        graphicsState.polygon.back.mode = mode;
        dirty = 1;
    }
    
    if (dirty)
    {
        glPolygonMode((GLenum)face, (GLenum)mode);
        glCheckErrors();
    }
}

void GraphicsClearColour(vec4 colour)
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

void GraphicsClearDepth(float depth)
{
    if (graphicsState.clear.depth != depth)
    {
        graphicsState.clear.depth = depth;
        glClearDepth(depth);
        glCheckErrors();
    }
}

void GraphicsClearStencil(unsigned int stencil)
{
    if (graphicsState.clear.stencil != stencil)
    {
        graphicsState.clear.stencil = stencil;
        glClearStencil((GLint)stencil);
        glCheckErrors();
    }
}

void GraphicsClear(BufferBit bits)
{
    glClear((GLbitfield)bits);
    glCheckErrors();
}

