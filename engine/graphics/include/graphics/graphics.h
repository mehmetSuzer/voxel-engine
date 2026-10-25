
#pragma once

#include <cglm/cglm.h>
#include "enums.h"

#define DEPTH_NEAREST  0.0
#define DEPTH_FURTHEST 1.0

typedef void*(*GraphicsAPILoadFunction)(const char*);

bool graphicsInit(GraphicsAPILoadFunction graphicsAPILoadFunction);

void graphicsEnable(GraphicsCapability graphicsCapability);
void graphicsDisable(GraphicsCapability graphicsCapability);

void graphicsViewport(int32_t x, int32_t y, int32_t width, int32_t height);

void graphicsDepthFunction(CompareFunction compareFunction);
void graphicsDepthWriteEnable(bool writeEnabled);
void graphicsDepthRange(float near, float far);

// (reference & testMask)  compareFunction  (stencil & testMask)
void graphicsStencilFunction(Face face, CompareFunction compareFunction, int32_t reference, uint32_t testMask);
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
void graphicsClearDepth(double depth);
void graphicsClearStencil(int32_t stencil);
void graphicsClear(BufferBit bufferBits);

void graphicsDispatchCompute(uint32_t workGroupCountX, uint32_t workGroupCountY, uint32_t workGroupCountZ);

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits);

#ifndef NDEBUG
void graphicsInsertDebugMessage(DebugSource debugSource, DebugType debugType, DebugSeverity debugSeverity, const char* debugMessage);
#endif

