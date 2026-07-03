
#include <stddef.h>
#include <string.h>
#include "error.h"
#include "buffer.h"
#include "glad/glad.h"

BufferID bufferCreate(unsigned int size, const void* data, BufferStorageBit bufferStorageBits)
{
    GLuint bufferID;
    glCreateBuffers(1, &bufferID);
    glNamedBufferStorage(bufferID, size, data, bufferStorageBitsToNative(bufferStorageBits));
    glCheckErrors();
    return bufferID;
}

void bufferDestroy(BufferID bufferID)
{
    glDeleteBuffers(1, &bufferID);
    glCheckErrors();
}

int bufferIsActive(BufferID bufferID)
{
    return (glIsBuffer(bufferID) == GL_TRUE);
}

void bufferWrite(BufferID bufferID, const void* data)
{
    glNamedBufferSubData(bufferID, 0, bufferGetSize(bufferID), data);
    glCheckErrors();
}

void bufferWriteRange(BufferID bufferID, unsigned int offset, unsigned int size, const void* data)
{
    glNamedBufferSubData(bufferID, offset, size, data);
    glCheckErrors();
}

void bufferRead(BufferID bufferID, void* dataOut)
{
    glGetNamedBufferSubData(bufferID, 0, bufferGetSize(bufferID), dataOut);
    glCheckErrors();
}

void bufferReadRange(BufferID bufferID, unsigned int offset, unsigned int size, void* dataOut)
{
    glGetNamedBufferSubData(bufferID, offset, size, dataOut);
    glCheckErrors();
}

void bufferClear(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, const void* data)
{
    glClearNamedBufferData(bufferID, internalFormatToNative(internalFormat), externalFormatToNative(externalFormat), dataTypeToNative(dataType), data);
    glCheckErrors();
}

void bufferClearRange(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, unsigned int offset, unsigned int size, const void* data)
{
    glClearNamedBufferSubData(bufferID, internalFormatToNative(internalFormat), offset, size, externalFormatToNative(externalFormat), dataTypeToNative(dataType), data);
    glCheckErrors();
}

void bufferCopy(BufferID readBufferID, BufferID writeBufferID)
{
    glCopyNamedBufferSubData(readBufferID, writeBufferID, 0, 0, bufferGetSize(readBufferID));
    glCheckErrors();
}

void bufferCopyRange(BufferID readBufferID, BufferID writeBufferID, unsigned int readOffset, unsigned int writeOffset, unsigned int size)
{
    glCopyNamedBufferSubData(readBufferID, writeBufferID, readOffset, writeOffset, size);
    glCheckErrors();
}

void bufferBind(BufferID bufferID, BufferTarget bufferTarget, unsigned int bindingPoint)
{
    glBindBufferBase(bufferTargetToNative(bufferTarget), bindingPoint, bufferID);
    glCheckErrors();
}

void bufferBindRange(BufferID bufferID, BufferTarget bufferTarget, unsigned int bindingPoint, unsigned int offset, unsigned int size)
{
    glBindBufferRange(bufferTargetToNative(bufferTarget), bindingPoint, bufferID, offset, size);
    glCheckErrors();
}

void* bufferMap(BufferID bufferID, AccessPolicy accessPolicy)
{
    void* pointer = glMapNamedBuffer(bufferID, accessPolicyToNative(accessPolicy));
    glCheckErrors();
    return pointer;
}

void* bufferMapRange(BufferID bufferID, unsigned int offset, unsigned int length, BufferMapBit bufferMapBits)
{
    void* pointer = glMapNamedBufferRange(bufferID, offset, length, bufferMapBitsToNative(bufferMapBits));
    glCheckErrors();
    return pointer;
}

int bufferUnmap(BufferID bufferID)
{
    return (glUnmapNamedBuffer(bufferID) == GL_TRUE);
}

void bufferFlushMappedRange(BufferID bufferID, unsigned int offset, unsigned int length)
{
    glFlushMappedNamedBufferRange(bufferID, offset, length);
    glCheckErrors();
}

int bufferIsMapped(BufferID bufferID)
{
    GLint mapped = 0;
    glGetNamedBufferParameteriv(bufferID, GL_BUFFER_MAPPED, &mapped);
    glCheckErrors();
    return mapped;
}

long bufferGetSize(BufferID bufferID)
{
    GLint64 size = 0l;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_SIZE, &size);
    glCheckErrors();
    return size;
}

long bufferGetMapOffset(BufferID bufferID)
{
    GLint64 offset = 0l;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_MAP_OFFSET, &offset);
    glCheckErrors();
    return offset;
}

long bufferGetMapLength(BufferID bufferID)
{
    GLint64 length = 0l;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_MAP_LENGTH, &length);
    glCheckErrors();
    return length;
}

void* bufferGetMapPointer(BufferID bufferID)
{
    void* pointer = NULL;
    glGetNamedBufferPointerv(bufferID, GL_BUFFER_MAP_POINTER, &pointer);
    glCheckErrors();
    return pointer;
}

