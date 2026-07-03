
#pragma once

#include <cglm/cglm.h>
#include "enums.h"

#define DEPTH_NEAREST  0.0f
#define DEPTH_FURTHEST 1.0f

typedef void*(*GraphicsFunctionLoader)(const char*);

void graphicsInit(GraphicsFunctionLoader graphicsFunctionLoader);

void graphicsEnable(Capability capability);
void graphicsDisable(Capability capability);

void graphicsViewport(int x, int y, int width, int height);

void graphicsDepthFunc(CompareFunc compareFunc);
void graphicsDepthWriteEnable(int writeEnabled);
void graphicsDepthRange(float near, float far);

// (reference & testMask)  compareFunc  (stencil & testMask)
void graphicsStencilFunc(Face face, CompareFunc compareFunc, int reference, unsigned int testMask);
// newStencil = (writtenValue & writeMask) | (oldStencil & ~writeMask)
void graphicsStencilWriteMask(Face face, unsigned int writeMask);
void graphicsStencilOperation(Face face, StencilOperation stencilFail, StencilOperation depthFail, StencilOperation depthPass);

void graphicsScissor(int x, int y, int width, int height);

void graphicsBlendFactor(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
void graphicsBlendEquation(BlendEquation equationRGB, BlendEquation equationAlpha);
void graphicsBlendColour(vec4 colour);

void graphicsCullFace(Face face);
void graphicsFrontFace(FrontFace frontFace);

void graphicsSampleCoverage(float coverage, int invert);

void graphicsPolygonOffset(float factor, float units);

void graphicsPointSize(float size);

void graphicsPrimitiveRestartIndex(unsigned int restartIndex);

void graphicsPolygonMode(Face face, PolygonMode polygonMode);

void graphicsClearColour(vec4 colour);
void graphicsClearDepth(float depth);
void graphicsClearStencil(unsigned int stencil);
void graphicsClear(BufferBit bufferBits);

void graphicsDispatchCompute(int workGroupCountX, int workGroupCountY, int workGroupCountZ);

void graphicsMemoryBarrier(MemoryBarrierBit memoryBarrierBits);

