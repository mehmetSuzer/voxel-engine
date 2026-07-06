
#include <stddef.h>
#include <string.h>
#include "buffer.h"
#include "log/log.h"
#include "glad/glad.h"

BufferID bufferCreate(size_t size, const void* data, BufferStorageBit bufferStorageBits)
{
    GLuint bufferID;
    glCreateBuffers(1, &bufferID);
    glNamedBufferStorage(bufferID, (GLsizeiptr)size, data, bufferStorageBitsToNative(bufferStorageBits));

    logVerbose("BUFFER", "created: %u", bufferID);
    return bufferID;
}

void bufferDestroy(BufferID bufferID)
{
    glDeleteBuffers(1, &bufferID);
    logVerbose("BUFFER", "destroyed: %u", bufferID);
}

bool bufferIsActive(BufferID bufferID)
{
    return (glIsBuffer(bufferID) == GL_TRUE);
}

void bufferWrite(BufferID bufferID, const void* data)
{
    glNamedBufferSubData(bufferID, 0, (GLsizeiptr)bufferGetSize(bufferID), data);
}

void bufferWriteRange(BufferID bufferID, size_t offset, size_t size, const void* data)
{
    glNamedBufferSubData(bufferID, (GLintptr)offset, (GLsizeiptr)size, data);
}

void bufferRead(BufferID bufferID, void* dataOut)
{
    glGetNamedBufferSubData(bufferID, 0, bufferGetSize(bufferID), dataOut);
}

void bufferReadRange(BufferID bufferID, size_t offset, size_t size, void* dataOut)
{
    glGetNamedBufferSubData(bufferID, (GLintptr)offset, (GLsizeiptr)size, dataOut);
}

void bufferClear(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, const void* data)
{
    glClearNamedBufferData(bufferID, internalFormatToNative(internalFormat), externalFormatToNative(externalFormat), dataTypeToNative(dataType), data);
}

void bufferClearRange(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, size_t offset, size_t size, const void* data)
{
    glClearNamedBufferSubData(bufferID, internalFormatToNative(internalFormat), (GLintptr)offset, 
        (GLsizeiptr)size, externalFormatToNative(externalFormat), dataTypeToNative(dataType), data);
}

void bufferCopy(BufferID readBufferID, BufferID writeBufferID)
{
    glCopyNamedBufferSubData(readBufferID, writeBufferID, 0, 0, bufferGetSize(readBufferID));
}

void bufferCopyRange(BufferID readBufferID, BufferID writeBufferID, size_t readOffset, size_t writeOffset, size_t size)
{
    glCopyNamedBufferSubData(readBufferID, writeBufferID, (GLintptr)readOffset, (GLintptr)writeOffset, (GLsizeiptr)size);
}

void bufferBind(BufferID bufferID, BufferTarget bufferTarget, uint32_t bindingPoint)
{
    glBindBufferBase(bufferTargetToNative(bufferTarget), bindingPoint, bufferID);
}

void bufferBindRange(BufferID bufferID, BufferTarget bufferTarget, uint32_t bindingPoint, size_t offset, size_t size)
{
    glBindBufferRange(bufferTargetToNative(bufferTarget), bindingPoint, bufferID, (GLintptr)offset, (GLsizeiptr)size);
}

void* bufferMap(BufferID bufferID, AccessPolicy accessPolicy)
{
    return glMapNamedBuffer(bufferID, accessPolicyToNative(accessPolicy));
}

void* bufferMapRange(BufferID bufferID, size_t offset, size_t length, BufferMapBit bufferMapBits)
{
    return glMapNamedBufferRange(bufferID, (GLintptr)offset, (GLsizeiptr)length, bufferMapBitsToNative(bufferMapBits));
}

bool bufferUnmap(BufferID bufferID)
{
    return (glUnmapNamedBuffer(bufferID) == GL_TRUE);
}

void bufferFlushMappedRange(BufferID bufferID, size_t offset, size_t length)
{
    glFlushMappedNamedBufferRange(bufferID, (GLintptr)offset, (GLsizeiptr)length);
}

bool bufferIsMapped(BufferID bufferID)
{
    GLint mapped = 0;
    glGetNamedBufferParameteriv(bufferID, GL_BUFFER_MAPPED, &mapped);
    return (mapped == GL_TRUE);
}

int64_t bufferGetSize(BufferID bufferID)
{
    GLint64 size = 0;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_SIZE, &size);
    return size;
}

int64_t bufferGetMapOffset(BufferID bufferID)
{
    GLint64 offset = 0;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_MAP_OFFSET, &offset);
    return offset;
}

int64_t bufferGetMapLength(BufferID bufferID)
{
    GLint64 length = 0;
    glGetNamedBufferParameteri64v(bufferID, GL_BUFFER_MAP_LENGTH, &length);
    return length;
}

void* bufferGetMapPointer(BufferID bufferID)
{
    void* pointer = NULL;
    glGetNamedBufferPointerv(bufferID, GL_BUFFER_MAP_POINTER, &pointer);
    return pointer;
}

