
#include <assert.h>
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/enums.h"

unsigned int capabilityToNative(Capability capability)
{
    switch (capability)
    {
        case CapabilityDepthTest:             return GL_DEPTH_TEST;
        case CapabilityStencilTest:           return GL_STENCIL_TEST;
        case CapabilityScissorTest:           return GL_SCISSOR_TEST;
        case CapabilityBlend:                 return GL_BLEND;
        case CapabilityCullFace:              return GL_CULL_FACE;
        case CapabilityDither:                return GL_DITHER;
        case CapabilityMultisample:           return GL_MULTISAMPLE;
        case CapabilitySampleAlphaToCoverage: return GL_SAMPLE_ALPHA_TO_COVERAGE;
        case CapabilitySampleAlphaToOne:      return GL_SAMPLE_ALPHA_TO_ONE;
        case CapabilitySampleCoverage:        return GL_SAMPLE_COVERAGE;
        case CapabilityDepthClamp:            return GL_DEPTH_CLAMP;
        case CapabilityPolygonOffsetPoint:    return GL_POLYGON_OFFSET_POINT;
        case CapabilityPolygonOffsetLine:     return GL_POLYGON_OFFSET_LINE;
        case CapabilityPolygonOffsetFill:     return GL_POLYGON_OFFSET_FILL;
        case CapabilityProgramPointSize:      return GL_PROGRAM_POINT_SIZE;
        case CapabilityFramebufferSRGB:       return GL_FRAMEBUFFER_SRGB;
        case CapabilityPrimitiveRestart:      return GL_PRIMITIVE_RESTART;
    }

    logError("ENUMS", "invalid capability");
    assert(0);

    return GL_DEPTH_TEST;
}

unsigned int bufferBitsToNative(BufferBit bufferBits)
{
    unsigned int native = 0u;
    if (bufferBits & BufferBitColour  != 0) { native |= GL_COLOR_BUFFER_BIT;   }
    if (bufferBits & BufferBitDepth   != 0) { native |= GL_DEPTH_BUFFER_BIT;   }
    if (bufferBits & BufferBitStencil != 0) { native |= GL_STENCIL_BUFFER_BIT; }

    if (native == 0u)
    {
        logError("ENUMS", "invalid buffer bits");
        assert(0);

        return GL_COLOR_BUFFER_BIT;
    }
    
    return native;
}

unsigned int textureWrapToNative(TextureWrap textureWrap)
{
    switch (textureWrap)
    {
        case TextureWrapRepeat:            return GL_REPEAT;
        case TextureWrapMirroredRepeat:    return GL_MIRRORED_REPEAT;
        case TextureWrapClampToEdge:       return GL_CLAMP_TO_EDGE;
        case TextureWrapClampToBorder:     return GL_CLAMP_TO_BORDER;
        case TextureWrapMirrorClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
    }

    logError("ENUMS", "invalid texture wrap");
    assert(0);

    return GL_REPEAT;
}

unsigned int textureMinFilterToNative(TextureMinFilter textureMinFilter)
{
    switch (textureMinFilter)
    {
        case TextureMinFilterNearest:              return GL_NEAREST;
        case TextureMinFilterLinear:               return GL_LINEAR;
        case TextureMinFilterNearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
        case TextureMinFilterLinearMipmapNearest:  return GL_LINEAR_MIPMAP_NEAREST;
        case TextureMinFilterNearestMipmapLinear:  return GL_NEAREST_MIPMAP_LINEAR;
        case TextureMinFilterLinearMipmapLinear:   return GL_LINEAR_MIPMAP_LINEAR;
    }

    logError("ENUMS", "invalid texture min filter");
    assert(0);

    return GL_NEAREST;
}

unsigned int textureMagFilterToNative(TextureMagFilter textureMagFilter)
{
    switch (textureMagFilter)
    {
        case TextureMagFilterNearest:  return GL_NEAREST;
        case TextureMagFilterLinear:   return GL_LINEAR;
    }

    logWarning("ENUMS", "invalid texture mag filter");
    assert(0);

    return GL_NEAREST;
}

unsigned int textureAccessToNative(TextureAccess textureAccess)
{
    switch (textureAccess)
    {
        case TextureAccessReadOnly:  return GL_READ_ONLY; 
        case TextureAccessWriteOnly: return GL_WRITE_ONLY; 
        case TextureAccessReadWrite: return GL_READ_WRITE; 
    }

    logError("ENUMS", "invalid texture access");
    assert(0);

    return GL_READ_ONLY;
}

unsigned int compareModeToNative(CompareMode compareMode)
{
    switch (compareMode)
    {
        case CompareModeNone:               return GL_NONE;
        case CompareModeReferenceToTexture: return GL_COMPARE_REF_TO_TEXTURE;
    }

    logError("ENUMS", "invalid compare mode");
    assert(0);

    return GL_NONE;
}

unsigned int compareFuncToNative(CompareFunc compareFunc)
{
    switch (compareFunc)
    {
        case CompareFuncNever:        return GL_NEVER;
        case CompareFuncEqual:        return GL_EQUAL;
        case CompareFuncLess:         return GL_LESS;
        case CompareFuncLessEqual:    return GL_LEQUAL;
        case CompareFuncGreater:      return GL_GREATER;
        case CompareFuncGreaterEqual: return GL_GEQUAL;
        case CompareFuncNotEqual:     return GL_NOTEQUAL;
        case CompareFuncAlways:       return GL_ALWAYS;
    }

    logError("ENUMS", "invalid compare func");
    assert(0);

    return GL_NEVER;
}

unsigned int stencilOperationToNative(StencilOperation stencilOperation)
{
    switch (stencilOperation)
    {
        case StencilOperationKeep:          return GL_KEEP;
        case StencilOperationZero:          return GL_ZERO;
        case StencilOperationReplace:       return GL_REPLACE;
        case StencilOperationIncrement:     return GL_INCR;
        case StencilOperationIncrementWrap: return GL_INCR_WRAP;
        case StencilOperationDecrement:     return GL_DECR;
        case StencilOperationDecrementWrap: return GL_DECR_WRAP;
        case StencilOperationInvert:        return GL_INVERT;
    }

    logError("ENUMS", "invalid stencil operation");
    assert(0);

    return GL_KEEP;
}

unsigned int faceToNative(Face face)
{
    switch (face)
    {
        case FaceFront: return GL_FRONT;
        case FaceBack:  return GL_BACK;
        case FaceBoth:  return GL_FRONT_AND_BACK;
    }

    logError("ENUMS", "invalid face");
    assert(0);

    return GL_FRONT;
}

unsigned int frontFaceToNative(FrontFace frontFace)
{
    switch (frontFace)
    {
        case FrontFaceCW:  return GL_CW;
        case FrontFaceCCW: return GL_CCW;
    }

    logError("ENUMS", "invalid front face");
    assert(0);

    return GL_CW;
}

unsigned int blendFactorToNative(BlendFactor blendFactor)
{
    switch (blendFactor)
    {
        case BlendFactorZero:                   return GL_ZERO;
        case BlendFactorOne:                    return GL_ONE;
        case BlendFactorSrcColour:              return GL_SRC_COLOR;
        case BlendFactorOneMinusSrcColour:      return GL_ONE_MINUS_SRC_COLOR;
        case BlendFactorDstColour:              return GL_DST_COLOR;
        case BlendFactorOneMinusDstColour:      return GL_ONE_MINUS_DST_COLOR;
        case BlendFactorSrcAlpha:               return GL_SRC_ALPHA;
        case BlendFactorOneMinusSrcAlpha:       return GL_ONE_MINUS_SRC_ALPHA;
        case BlendFactorDstAlpha:               return GL_DST_ALPHA;
        case BlendFactorOneMinusDstAlpha:       return GL_ONE_MINUS_DST_ALPHA;
        case BlendFactorConstantColour:         return GL_CONSTANT_COLOR;
        case BlendFactorOneMinusConstantColour: return GL_ONE_MINUS_CONSTANT_COLOR;
        case BlendFactorConstantAlpha:          return GL_CONSTANT_ALPHA;
        case BlendFactorOneMinusConstantAlpha:  return GL_ONE_MINUS_CONSTANT_ALPHA;
        case BlendFactorSrcAlphaSaturate:       return GL_SRC_ALPHA_SATURATE;
    }

    logError("ENUMS", "invalid blend factor");
    assert(0);

    return GL_ZERO;
}

unsigned int blendEquationToNative(BlendEquation blendEquation)
{
    switch (blendEquation)
    {
        case BlendEquationAdd:             return GL_FUNC_ADD;
        case BlendEquationSubtract:        return GL_FUNC_SUBTRACT;
        case BlendEquationReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
        case BlendEquationMin:             return GL_MIN;
        case BlendEquationMax:             return GL_MAX;        
    }

    logError("ENUMS", "invalid blend equation");
    assert(0);

    return GL_FUNC_ADD;
}

unsigned int polygonModeToNative(PolygonMode polygonMode)
{
    switch (polygonMode)
    {
        case PolygonModePoint: return GL_POINT;
        case PolygonModeLine:  return GL_LINE;
        case PolygonModeFill:  return GL_FILL;
    }

    logError("ENUMS", "invalid polygon mode");
    assert(0);

    return GL_POINT;
}

unsigned int drawModeToNative(DrawMode drawMode)
{
    switch (drawMode)
    {
        case DrawModePoints:        return GL_POINTS;
        case DrawModeLines:         return GL_LINES;
        case DrawModeLineStrip:     return GL_LINE_STRIP;
        case DrawModeLineLoop:      return GL_LINE_LOOP;
        case DrawModeTriangles:     return GL_TRIANGLES;
        case DrawModeTriangleStrip: return GL_TRIANGLE_STRIP;
        case DrawModeTriangleFan:   return GL_TRIANGLE_FAN;
    }

    logError("ENUMS", "invalid draw mode");
    assert(0);

    return GL_POINTS;
}

unsigned int memoryBarrierBitsToNative(MemoryBarrierBit memoryBarrierBits)
{
    unsigned int native = 0u;
    if (memoryBarrierBits & MemoryBarrierBitVertexAttributeArray != 0) { native |= GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;  } 
    if (memoryBarrierBits & MemoryBarrierBitElementArray         != 0) { native |= GL_ELEMENT_ARRAY_BARRIER_BIT;        }       
    if (memoryBarrierBits & MemoryBarrierBitUniform              != 0) { native |= GL_UNIFORM_BARRIER_BIT;              }
    if (memoryBarrierBits & MemoryBarrierBitTextureFetch         != 0) { native |= GL_TEXTURE_FETCH_BARRIER_BIT;        }
    if (memoryBarrierBits & MemoryBarrierBitShaderImageAccess    != 0) { native |= GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;  }
    if (memoryBarrierBits & MemoryBarrierBitCommand              != 0) { native |= GL_COMMAND_BARRIER_BIT;              }
    if (memoryBarrierBits & MemoryBarrierBitPixelBuffer          != 0) { native |= GL_PIXEL_BUFFER_BARRIER_BIT;         }
    if (memoryBarrierBits & MemoryBarrierBitTextureUpdate        != 0) { native |= GL_TEXTURE_UPDATE_BARRIER_BIT;       }
    if (memoryBarrierBits & MemoryBarrierBitBufferUpdate         != 0) { native |= GL_BUFFER_UPDATE_BARRIER_BIT;        }
    if (memoryBarrierBits & MemoryBarrierBitFramebuffer          != 0) { native |= GL_FRAMEBUFFER_BARRIER_BIT;          }
    if (memoryBarrierBits & MemoryBarrierBitTransformFeedback    != 0) { native |= GL_TRANSFORM_FEEDBACK_BARRIER_BIT;   }
    if (memoryBarrierBits & MemoryBarrierBitAtomicCounter        != 0) { native |= GL_ATOMIC_COUNTER_BARRIER_BIT;       }
    if (memoryBarrierBits & MemoryBarrierBitShaderStorage        != 0) { native |= GL_SHADER_STORAGE_BARRIER_BIT;       }
    if (memoryBarrierBits & MemoryBarrierBitClientMappedBuffer   != 0) { native |= GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT; }
    if (memoryBarrierBits & MemoryBarrierBitQueryBuffer          != 0) { native |= GL_QUERY_BUFFER_BARRIER_BIT;         }

    if (native == 0u)
    {
        logError("ENUMS", "invalid memory barrier bits");
        assert(0);

        return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;
    }
    
    return native;
}

unsigned int bufferUsageToNative(BufferUsage bufferUsage)
{
    switch (bufferUsage)
    {
        case BufferUsageStaticDraw:  return GL_STATIC_DRAW;
        case BufferUsageDynamicDraw: return GL_DYNAMIC_DRAW;
        case BufferUsageStreamDraw:  return GL_STREAM_DRAW;
        case BufferUsageStaticRead:  return GL_STATIC_READ;
        case BufferUsageDynamicRead: return GL_DYNAMIC_READ;
        case BufferUsageStreamRead:  return GL_STREAM_READ;
        case BufferUsageStaticCopy:  return GL_STATIC_COPY;
        case BufferUsageDynamicCopy: return GL_DYNAMIC_COPY;
        case BufferUsageStreamCopy:  return GL_STREAM_COPY;
    }

    logError("ENUMS", "invalid bufer usage");
    assert(0);

    return GL_STATIC_DRAW;
}

unsigned int bufferStorageBitsToNative(BufferStorageBit bufferStorageBits)
{
    unsigned int native = 0u;
    if (bufferStorageBits & BufferStorageBitMapRead        != 0) { native |= GL_MAP_READ_BIT;        }
    if (bufferStorageBits & BufferStorageBitMapWrite       != 0) { native |= GL_MAP_WRITE_BIT;       }
    if (bufferStorageBits & BufferStorageBitMapPersistent  != 0) { native |= GL_MAP_PERSISTENT_BIT;  }
    if (bufferStorageBits & BufferStorageBitMapCoherent    != 0) { native |= GL_MAP_COHERENT_BIT;    }
    if (bufferStorageBits & BufferStorageBitDynamicStorage != 0) { native |= GL_DYNAMIC_STORAGE_BIT; }
    if (bufferStorageBits & BufferStorageBitClientStorage  != 0) { native |= GL_CLIENT_STORAGE_BIT;  }

    if (native == 0u)
    {
        logError("ENUMS", "invalid buffer storage bits");
        assert(0);

        return GL_MAP_READ_BIT;
    }

    return native;
}

unsigned int bufferMapBitsToNative(BufferMapBit bufferMapBits)
{
    unsigned int native = 0u;
    if (bufferMapBits & BufferMapBitRead             != 0) { native |= GL_MAP_READ_BIT;              }
    if (bufferMapBits & BufferMapBitWrite            != 0) { native |= GL_MAP_WRITE_BIT;             }
    if (bufferMapBits & BufferMapBitInvalidateRange  != 0) { native |= GL_MAP_INVALIDATE_RANGE_BIT;  }
    if (bufferMapBits & BufferMapBitInvalidateBuffer != 0) { native |= GL_MAP_INVALIDATE_BUFFER_BIT; }
    if (bufferMapBits & BufferMapBitFlushExplicit    != 0) { native |= GL_MAP_FLUSH_EXPLICIT_BIT;    }
    if (bufferMapBits & BufferMapBitUnsynchronised   != 0) { native |= GL_MAP_UNSYNCHRONIZED_BIT;    }
    if (bufferMapBits & BufferMapBitPersistent       != 0) { native |= GL_MAP_PERSISTENT_BIT;        }
    if (bufferMapBits & BufferMapBitCoherent         != 0) { native |= GL_MAP_COHERENT_BIT;          }

    if (native == 0u)
    {
        logError("ENUMS", "invalid buffer map bits");
        assert(0);

        return GL_MAP_READ_BIT;
    }

    return native;
}

unsigned int bufferTargetToNative(BufferTarget bufferTarget)
{
    switch (bufferTarget)
    {
        case BufferTargetVertexArray:           return GL_ARRAY_BUFFER;
        case BufferTargetElementArray:          return GL_ELEMENT_ARRAY_BUFFER;
        case BufferTargetShaderStorage:         return GL_SHADER_STORAGE_BUFFER;
        case BufferTargetUniform:               return GL_UNIFORM_BUFFER;
        case BufferTargetAtomicCounter:         return GL_ATOMIC_COUNTER_BUFFER;
        case BufferTargetDispatchIndirect:      return GL_DISPATCH_INDIRECT_BUFFER;
        case BufferTargetDrawIndirect:          return GL_DRAW_INDIRECT_BUFFER;
        case BufferTargetPixelPack:             return GL_PIXEL_PACK_BUFFER;
        case BufferTargetPixelUnpack:           return GL_PIXEL_UNPACK_BUFFER;
        case BufferTargetTexture:               return GL_TEXTURE_BUFFER;
        case BufferTargetTransformFeedback:     return GL_TRANSFORM_FEEDBACK_BUFFER;
        case BufferTargetQuery:                 return GL_QUERY_BUFFER;
        case BufferTargetCopyRead:              return GL_COPY_READ_BUFFER;
        case BufferTargetCopyWrite:             return GL_COPY_WRITE_BUFFER;
    }

    logError("ENUMS", "invalid buffer target");
    assert(0);

    return GL_ARRAY_BUFFER;
}

