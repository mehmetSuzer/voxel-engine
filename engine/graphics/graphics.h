
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

typedef enum Capability
{
    CapabilityDepthTest             = GL_DEPTH_TEST,
    CapabilityStencilTest           = GL_STENCIL_TEST,
    CapabilityScissorTest           = GL_SCISSOR_TEST,
    CapabilityBlend                 = GL_BLEND,
    CapabilityCullFace              = GL_CULL_FACE,
    CapabilityDither                = GL_DITHER,
    CapabilityMultisample           = GL_MULTISAMPLE,
    CapabilitySampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
    CapabilitySampleAlphaToOne      = GL_SAMPLE_ALPHA_TO_ONE,
    CapabilitySampleCoverage        = GL_SAMPLE_COVERAGE,
    CapabilityDepthClamp            = GL_DEPTH_CLAMP,
    CapabilityPolygonOffsetPoint    = GL_POLYGON_OFFSET_POINT,
    CapabilityPolygonOffsetLine     = GL_POLYGON_OFFSET_LINE,
    CapabilityPolygonOffsetFill     = GL_POLYGON_OFFSET_FILL,
    CapabilityProgramPointSize      = GL_PROGRAM_POINT_SIZE,
    CapabilityFramebufferSRGB       = GL_FRAMEBUFFER_SRGB,
    CapabilityPrimitiveRestart      = GL_PRIMITIVE_RESTART,
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
    BlendFactorDstColour              = GL_DST_COLOR,
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

typedef enum PolygonMode
{
    PolygonModePoint = GL_POINT,
    PolygonModeLine  = GL_LINE,
    PolygonModeFill  = GL_FILL,
} PolygonMode;

typedef enum BufferBit
{
    BufferBitColour  = GL_COLOR_BUFFER_BIT,
    BufferBitDepth   = GL_DEPTH_BUFFER_BIT,
    BufferBitStencil = GL_STENCIL_BUFFER_BIT,
} BufferBit;

#define DEPTH_NEAREST  0.0f
#define DEPTH_FURTHEST 1.0f

void GraphicsInit(GLADloadproc loader);

void GraphicsEnable(Capability capability);
void GraphicsDisable(Capability capability);

void GraphicsViewport(int x, int y, int width, int height);

void GraphicsDepthFunc(TestFunc func);
void GraphicsDepthWriteEnable(int writeEnabled);
void GraphicsDepthRange(float near, float far);

// (reference & testMask)  func  (stencil & testMask)
void GraphicsStencilFunc(Face face, TestFunc func, int reference, unsigned int testMask);
// newStencil = (writtenValue & writeMask) | (oldStencil & ~writeMask)
void GraphicsStencilWriteMask(Face face, unsigned int writeMask);
void GraphicsStencilOp(Face face, StencilOp stencilFail, StencilOp depthFail, StencilOp depthPass);

void GraphicsScissor(int x, int y, int width, int height);

void GraphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
void GraphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha);
void GraphicsBlendColour(vec4 colour);

void GraphicsCullFace(Face face);
void GraphicsFrontFace(FrontFace front);

void GraphicsSampleCoverage(float coverage, int invert);

void GraphicsPolygonOffset(float factor, float units);

void GraphicsPointSize(float size);

void GraphicsPrimitiveRestartIndex(unsigned int index);

void GraphicsPolygonMode(Face face, PolygonMode mode);

void GraphicsClearColour(vec4 colour);
void GraphicsClearDepth(float depth);
void GraphicsClearStencil(unsigned int stencil);
void GraphicsClear(BufferBit bits);

