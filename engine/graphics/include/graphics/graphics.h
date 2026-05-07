
#pragma once

#include <cglm/cglm.h>
#include "glad/glad.h"

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

