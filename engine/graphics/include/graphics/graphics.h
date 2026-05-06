
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

void graphicsInit(GLADloadproc loader);

void graphicsEnable(Capability capability);
void graphicsDisable(Capability capability);

void graphicsViewport(int x, int y, int width, int height);

void graphicsDepthFunc(TestFunc func);
void graphicsDepthWriteEnable(int writeEnabled);
void graphicsDepthRange(float near, float far);

// (reference & testMask)  func  (stencil & testMask)
void graphicsStencilFunc(Face face, TestFunc func, int reference, unsigned int testMask);
// newStencil = (writtenValue & writeMask) | (oldStencil & ~writeMask)
void graphicsStencilWriteMask(Face face, unsigned int writeMask);
void graphicsStencilOp(Face face, StencilOp stencilFail, StencilOp depthFail, StencilOp depthPass);

void graphicsScissor(int x, int y, int width, int height);

void graphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
void graphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha);
void graphicsBlendColour(vec4 colour);

void graphicsCullFace(Face face);
void graphicsFrontFace(FrontFace front);

void graphicsSampleCoverage(float coverage, int invert);

void graphicsPolygonOffset(float factor, float units);

void graphicsPointSize(float size);

void graphicsPrimitiveRestartIndex(unsigned int index);

void graphicsPolygonMode(Face face, PolygonMode mode);

void graphicsClearColour(vec4 colour);
void graphicsClearDepth(float depth);
void graphicsClearStencil(unsigned int stencil);
void graphicsClear(BufferBit bits);

