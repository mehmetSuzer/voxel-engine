
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

// TODO: Check out these capabilities
typedef enum Capability
{
    CapabilityDepthClamp             = GL_DEPTH_CLAMP,              // Prevents geometry from being clipped by near/far planes
    CapabilityMultisample            = GL_MULTISAMPLE,              // Enables MSAA anti-aliasing
    CapabilitySampleAlphaToCoverage  = GL_SAMPLE_ALPHA_TO_COVERAGE, // Helps with transparent edges
    CapabilityFramebufferSRGB        = GL_FRAMEBUFFER_SRGB,         // Enables sRGB correction
    CapabilityProgramPointSize       = GL_PROGRAM_POINT_SIZE,       // Allows shaders to control point size
    CapabilityLineSmooth             = GL_LINE_SMOOTH,              // Smooth lines (mostly deprecated)
    CapabilityPolygonOffsetFill      = GL_POLYGON_OFFSET_FILL,      // Prevents z-fighting
    CapabilityDebugOutput            = GL_DEBUG_OUTPUT,             // Enables OpenGL debug messages
    CapabilityDebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS  // Makes debug output synchronous
} Capability;

typedef enum TestFunc
{
    TestFuncNever        = GL_NEVER,
    TestFuncEqual        = GL_EQUAL,
    TestFuncLess         = GL_LESS,
    TestFuncLessEqual    = GL_LEQUAL,
    TestFuncGreater      = GL_GREATER,
    TestFuncGreaterEqual = GL_GEQUAL,
    TestFuncNotEqual     = GL_NOTEQUAL,
    TestFuncAlways       = GL_ALWAYS,
} TestFunc;

typedef enum StencilOp
{
    StencilOpKeep          = GL_KEEP,
    StencilOpZero          = GL_ZERO,
    StencilOpReplace       = GL_REPLACE,
    StencilOpIncrement     = GL_INCR,
    StencilOpIncrementWrap = GL_INCR_WRAP,
    StencilOpDecrement     = GL_DECR,
    StencilOpDecrementWrap = GL_DECR_WRAP,
    StencilOpInvert        = GL_INVERT,
} StencilOp;

typedef enum Face
{
    FaceFront = GL_FRONT,
    FaceBack  = GL_BACK,
    FaceBoth  = GL_FRONT_AND_BACK,
} Face;

typedef enum FrontFace
{
    FrontFaceCW  = GL_CW,
    FrontFaceCCW = GL_CCW,
} FrontFace;

typedef enum BlendFactor
{
    BlendFactorZero                   = GL_ZERO,
    BlendFactorOne                    = GL_ONE,
    BlendFactorSrcColour              = GL_SRC_COLOR,
    BlendFactorOneMinusSrcColour      = GL_ONE_MINUS_SRC_COLOR,
    BlendFactorDstColor               = GL_DST_COLOR,
    BlendFactorOneMinusDstColour      = GL_ONE_MINUS_DST_COLOR,
    BlendFactorSrcAlpha               = GL_SRC_ALPHA,
    BlendFactorOneMinusSrcAlpha       = GL_ONE_MINUS_SRC_ALPHA,
    BlendFactorDstAlpha               = GL_DST_ALPHA,
    BlendFactorOneMinusDstAlpha       = GL_ONE_MINUS_DST_ALPHA,
    BlendFactorConstantColour         = GL_CONSTANT_COLOR,
    BlendFactorOneMinusConstantColour = GL_ONE_MINUS_CONSTANT_COLOR,
    BlendFactorConstantAlpha          = GL_CONSTANT_ALPHA,
    BlendFactorOneMinusConstantAlpha  = GL_ONE_MINUS_CONSTANT_ALPHA,
    BlendFactorSrcAlphaSaturate       = GL_SRC_ALPHA_SATURATE,
} BlendFactor;

typedef enum BlendEquation
{
    BlendEquationAdd             = GL_FUNC_ADD,
    BlendEquationSubtract        = GL_FUNC_SUBTRACT,
    BlendEquationReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
    BlendEquationMin             = GL_MIN,
    BlendEquationMax             = GL_MAX,
} BlendEquation;

typedef enum PolygonDrawMode
{
    PolygonDrawModePoint = GL_POINT,
    PolygonDrawModeLine  = GL_LINE,
    PolygonDrawModeFill  = GL_FILL,
} PolygonDrawMode;

typedef enum BufferBit
{
    BufferBitColour  = GL_COLOR_BUFFER_BIT,
    BufferBitDepth   = GL_DEPTH_BUFFER_BIT,
    BufferBitStencil = GL_STENCIL_BUFFER_BIT,
} BufferBit;

typedef struct Rectangle
{
    int x;
    int y;
    int width;
    int height;
} Rectangle;

typedef struct DepthTest
{
    int enabled;
    int writeEnabled;
    TestFunc func;
} DepthTest; 

typedef struct StencilTest
{
    int enabled;
    TestFunc func;
    int reference;
    unsigned int mask;
    StencilOp stencilFail;
    StencilOp depthFail;
    StencilOp depthPass;
} StencilTest;

typedef struct ScissorTest
{
    int enabled;
    Rectangle rect;
} ScissorTest;

typedef struct ColourBlend
{
    int enabled;
    BlendFactor srcFactor;
    BlendFactor dstFactor;
    BlendEquation equation;
} ColourBlend;

typedef struct FaceCull
{
    int enabled;
    Face cullFace;
    FrontFace frontFace;
} FaceCull;

typedef struct PolygonMode
{
    Face face;
    PolygonDrawMode mode;
} PolygonMode;

typedef struct ClearState
{
    vec4 colour;
    float depth;
    unsigned int stencil;
} ClearState;

#define DEPTH_NEAREST  0.0f
#define DEPTH_FURTHEST 1.0f

typedef struct GraphicsState
{
    Rectangle viewport;
    DepthTest depthTest;
    StencilTest stencilTest;
    ScissorTest scissorTest;
    ColourBlend colourBlend;
    FaceCull faceCull;
    PolygonMode polygonMode;
    ClearState clearState;
} GraphicsState;

void GraphicsInit(GLADloadproc loader);

void GraphicsSetViewport(Rectangle viewport);
void GraphicsSetDepthTest(DepthTest depthTest);
void GraphicsSetStencilTest(StencilTest stencilTest);
void GraphicsSetScissorTest(ScissorTest scissorTest);
void GraphicsSetColourBlend(ColourBlend colourBlend);
void GraphicsSetFaceCull(FaceCull faceCull);
void GraphicsSetPolygonMode(PolygonMode polygonMode);

void GraphicsSetClearColour(vec4 colour);
void GraphicsSetClearDepth(float depth);
void GraphicsSetClearStencil(unsigned int stencil);

void GraphicsClear(BufferBit bits);


