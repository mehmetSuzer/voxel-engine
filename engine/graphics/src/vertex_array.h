
#pragma once

#include "buffer.h"

typedef uint32_t VertexArrayID;

VertexArrayID vertexArrayCreate(void);

void vertexArrayDestroy(VertexArrayID vertexArrayID);

bool vertexArrayIsActive(VertexArrayID vertexArrayID);

void vertexArrayBind(VertexArrayID vertexArrayID);

void vertexArraySetVertexBuffer(VertexArrayID vertexArrayID, uint32_t bindingIndex, BufferID vertexBufferID, uint32_t offset, uint32_t stride);
void vertexArraySetElementBuffer(VertexArrayID vertexArrayID, BufferID elementBufferID);

// float, vec2, vec3, vec4
void vertexArrayLinkAttributeFloat(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t floatCount, uint32_t relativeOffset);
// int, ivec2, ivec3, ivec4
void vertexArrayLinkAttributeInt(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t intCount, uint32_t relativeOffset);
// uint, uvec2, uvec3, uvec4
void vertexArrayLinkAttributeUint(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t uintCount, uint32_t relativeOffset);
// double, dvec2, dvec3, dvec4
void vertexArrayLinkAttributeDouble(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t doubleCount, uint32_t relativeOffset);

