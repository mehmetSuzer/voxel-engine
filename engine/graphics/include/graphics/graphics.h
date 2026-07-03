
#pragma once

#include <cglm/cglm.h>
#include "enums.h"

#define DEPTH_NEAREST  0.0f
#define DEPTH_FURTHEST 1.0f

typedef void*(*GraphicsFunctionLoader)(const char*);

bool graphicsInit(GraphicsFunctionLoader graphicsFunctionLoader);

void graphicsEnable(Capability capability);
void graphicsDisable(Capability capability);

void graphicsViewport(int32_t x, int32_t y, int32_t width, int32_t height);

void graphicsDepthFunc(CompareFunc compareFunc);
void graphicsDepthWriteEnable(bool writeEnabled);
void graphicsDepthRange(float near, float far);

// (reference & testMask)  compareFunc  (stencil & testMask)
void graphicsStencilFunc(Face face, CompareFunc compareFunc, int32_t reference, uint32_t testMask);
// newStencil = (writtenValue & writeMask) | (oldStencil & ~writeMask)
void graphicsStencilWriteMask(Face face, uint32_t writeMask);
void graphicsStencilOperation(Face face, StencilOperation stencilFail, StencilOperation depthFail, StencilOperation depthPass);

void graphicsScissor(int32_t x, int32_t y, int32_t width, int32_t height);

void graphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
void graphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha);
void graphicsBlendColour(vec4 colour);

void graphicsCullFace(Face face);
void graphicsFrontFace(FrontFace frontFace);

void graphicsSampleCoverage(float coverage, bool invert);

void graphicsPolygonOffset(float factor, float units);

void graphicsPointSize(float size);

void graphicsPrimitiveRestartIndex(uint32_t restartIndex);

void graphicsPolygonMode(Face face, PolygonMode polygonMode);

void graphicsClearColour(vec4 colour);
void graphicsClearDepth(float depth);
void graphicsClearStencil(int32_t stencil);
void graphicsClear(BufferBit bufferBits);

void graphicsDispatchCompute(uint32_t workGroupCountX, uint32_t workGroupCountY, uint32_t workGroupCountZ);

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits);

