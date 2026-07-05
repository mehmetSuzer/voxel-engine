
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"
#include "vertex_array.h"

VertexArrayID vertexArrayCreate(void)
{
    GLuint vertexArrayID;
    glCreateVertexArrays(1, &vertexArrayID);
    glCheckErrors();
    logVerbose("V_ARRAY", "created: %u", vertexArrayID);
    return vertexArrayID;
}

void vertexArrayDestroy(VertexArrayID vertexArrayID)
{
    glDeleteVertexArrays(1, &vertexArrayID);
    glCheckErrors();
    logVerbose("V_ARRAY", "destroyed: %u", vertexArrayID);
}

bool vertexArrayIsActive(VertexArrayID vertexArrayID)
{
    return (glIsVertexArray(vertexArrayID) == GL_TRUE);
}

void vertexArrayBind(VertexArrayID vertexArrayID)
{
    glBindVertexArray(vertexArrayID);
    glCheckErrors();
    logVerbose("V_ARRAY", "binded: %u", vertexArrayID);
}

void vertexArraySetVertexBuffer(VertexArrayID vertexArrayID, uint32_t bindingIndex, BufferID vertexBufferID, uint32_t offset, uint32_t stride)
{
    glVertexArrayVertexBuffer(vertexArrayID, bindingIndex, vertexBufferID, offset, stride);
    glCheckErrors();
    logVerbose("V_ARRAY", "set vertex buffer %u for %u", vertexBufferID, vertexArrayID);
}

void vertexArraySetElementBuffer(VertexArrayID vertexArrayID, BufferID elementBufferID)
{
    glVertexArrayElementBuffer(vertexArrayID, elementBufferID);
    glCheckErrors();
    logVerbose("V_ARRAY", "set element buffer %u for %u", elementBufferID, vertexArrayID);
}

void vertexArrayLinkAttributeFloat(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t floatCount, uint32_t relativeOffset)
{
    glEnableVertexArrayAttrib(vertexArrayID, attributeIndex);
    glVertexArrayAttribFormat(vertexArrayID, attributeIndex, floatCount, GL_FLOAT, GL_FALSE, relativeOffset);
    glVertexArrayAttribBinding(vertexArrayID, attributeIndex, bindingIndex);
}

void vertexArrayLinkAttributeInt(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t intCount, uint32_t relativeOffset)
{
    glEnableVertexArrayAttrib(vertexArrayID, attributeIndex);
    glVertexArrayAttribIFormat(vertexArrayID, attributeIndex, intCount, GL_INT, relativeOffset);
    glVertexArrayAttribBinding(vertexArrayID, attributeIndex, bindingIndex);
}

void vertexArrayLinkAttributeUint(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t uintCount, uint32_t relativeOffset)
{
    glEnableVertexArrayAttrib(vertexArrayID, attributeIndex);
    glVertexArrayAttribIFormat(vertexArrayID, attributeIndex, uintCount, GL_UNSIGNED_INT, relativeOffset);
    glVertexArrayAttribBinding(vertexArrayID, attributeIndex, bindingIndex);
}

void vertexArrayLinkAttributeDouble(VertexArrayID vertexArrayID, uint32_t bindingIndex, uint32_t attributeIndex, uint32_t doubleCount, uint32_t relativeOffset)
{
    glEnableVertexArrayAttrib(vertexArrayID, attributeIndex);
    glVertexArrayAttribLFormat(vertexArrayID, attributeIndex, doubleCount, GL_DOUBLE, relativeOffset);
    glVertexArrayAttribBinding(vertexArrayID, attributeIndex, bindingIndex);
}

