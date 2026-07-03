
#pragma once

#include <stdbool.h>
#include "graphics/enums.h"

typedef uint32_t BufferID;

#define BUFFER_NULL ((BufferID)0)

BufferID bufferCreate(size_t size, const void* data, BufferStorageBit bufferStorageBits);

void bufferDestroy(BufferID bufferID);

bool bufferIsActive(BufferID bufferID);

// Writes the whole buffer and requires BufferStorageBitDynamicStorage.
void bufferWrite(BufferID bufferID, const void* data);
// Writes a specific range of the buffer and requires BufferStorageBitDynamicStorage.
void bufferWriteRange(BufferID bufferID, size_t offset, size_t size, const void* data);

// Read the whole buffer to the CPU memory.
void bufferRead(BufferID bufferID, void* dataOut);
// Reads a specific range of the buffer to CPU memory.
void bufferReadRange(BufferID bufferID, size_t offset, size_t size, void* dataOut);

// Clears the whole buffer to a specific value/colour on the GPU.
void bufferClear(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, const void* data);
// Clears a specific range of the buffer to a specific value/colour on the GPU.
void bufferClearRange(BufferID bufferID, InternalFormat internalFormat, 
    ExternalFormat externalFormat, DataType dataType, size_t offset, size_t size, const void* data);

// Copies the whole read-buffer to the write-buffer.
void bufferCopy(BufferID readBufferID, BufferID writeBufferID);
// Copies a specific range of the read-buffer to a specific range of the write-buffer.
void bufferCopyRange(BufferID readBufferID, BufferID writeBufferID, size_t readOffset, size_t writeOffset, size_t size);

// Binds the whole buffer to a shader binding point.
void bufferBind(BufferID bufferID, BufferTarget bufferTarget, uint32_t bindingPoint);
// Binds a specific range of the buffer to a shader binding point.
void bufferBindRange(BufferID bufferID, BufferTarget bufferTarget, uint32_t bindingPoint, size_t offset, size_t size);

// Maps the whole buffer into CPU address space and returns a direct pointer.
void* bufferMap(BufferID bufferID, AccessPolicy accessPolicy);
// Maps a specific range of the buffer into CPU address space and returns a direct pointer.
void* bufferMapRange(BufferID bufferID, size_t offset, size_t length, BufferMapBit bufferMapBits);

// Tells that the pointer obtained while mapping is no longer needed and invalidates the pointer.
bool bufferUnmap(BufferID bufferID);

// Tells the graphics driver exactly which region of the mapped buffer is modified so that it can uplad only that specific range to the GPU, saving bandwidth.
// Can be used only if the buffer is mapped with BufferMapBitFlushExplicit. Otherwise, it is assumed that the entire buffer is modified.
void bufferFlushMappedRange(BufferID bufferID, size_t offset, size_t length);

bool bufferIsMapped(BufferID bufferID);
int64_t bufferGetSize(BufferID bufferID);
int64_t bufferGetMapOffset(BufferID bufferID);
int64_t bufferGetMapLength(BufferID bufferID);
void* bufferGetMapPointer(BufferID bufferID);

