
#pragma once

#include "graphics/enums.h"

typedef unsigned int BufferID;

#define BUFFER_NULL ((BufferID)0)

BufferID bufferCreate(unsigned int size, const void* data, BufferStorageBit bufferStorageBits);

void bufferDestroy(BufferID bufferID);

int bufferIsActive(BufferID bufferID);

// Writes the whole buffer and requires BufferStorageBitDynamicStorage.
void bufferWrite(BufferID bufferID, const void* data);
// Writes a specific range of the buffer and requires BufferStorageBitDynamicStorage.
void bufferWriteRange(BufferID bufferID, unsigned int offset, unsigned int size, const void* data);

// Read the whole buffer to the CPU memory.
void bufferRead(BufferID bufferID, void* dataOut);
// Reads a specific range of the buffer to CPU memory.
void bufferReadRange(BufferID bufferID, unsigned int offset, unsigned int size, void* dataOut);

// Clears the whole buffer to a specific value/colour on the GPU.
void bufferClear(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, const void* data);
// Clears a specific range of the buffer to a specific value/colour on the GPU.
void bufferClearRange(BufferID bufferID, InternalFormat internalFormat, ExternalFormat externalFormat, DataType dataType, unsigned int offset, unsigned int size, const void* data);

// Copies the whole read-buffer to the write-buffer.
void bufferCopy(BufferID readBufferID, BufferID writeBufferID);
// Copies a specific range of the read-buffer to a specific range of the write-buffer.
void bufferCopyRange(BufferID readBufferID, BufferID writeBufferID, unsigned int readOffset, unsigned int writeOffset, unsigned int size);

// Binds the whole buffer to a shader binding point.
void bufferBind(BufferID bufferID, BufferTarget bufferTarget, unsigned int bindingPoint);
// Binds a specific range of the buffer to a shader binding point.
void bufferBindRange(BufferID bufferID, BufferTarget bufferTarget, unsigned int bindingPoint, unsigned int offset, unsigned int size);

// Maps the whole buffer into CPU address space and returns a direct pointer.
void* bufferMap(BufferID bufferID, AccessPolicy accessPolicy);
// Maps a specific range of the buffer into CPU address space and returns a direct pointer.
void* bufferMapRange(BufferID bufferID, unsigned int offset, unsigned int length, BufferMapBit bufferMapBits);

// Tells that the pointer obtained while mapping is no longer needed and invalidates the pointer.
int bufferUnmap(BufferID bufferID);

// Tells the graphics driver exactly which region of the mapped buffer is modified so that it can uplad only that specific range to the GPU, saving bandwidth.
// Can be used only if the buffer is mapped with BufferMapBitFlushExplicit. Otherwise, it is assumed that the entire buffer is modified.
void bufferFlushMappedRange(BufferID bufferID, unsigned int offset, unsigned int length);

int bufferIsMapped(BufferID bufferID);
long bufferGetSize(BufferID bufferID);
long bufferGetMapOffset(BufferID bufferID);
long bufferGetMapLength(BufferID bufferID);
void* bufferGetMapPointer(BufferID bufferID);

