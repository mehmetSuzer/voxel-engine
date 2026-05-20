
#include <assert.h>
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/enums.h"

unsigned int capabilityToCode(Capability capability)
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

unsigned int bufferBitsToCode(BufferBit bufferBits)
{
    unsigned int code = 0u;
    if (bufferBits | BufferBitColour  != 0) { code |= GL_COLOR_BUFFER_BIT;   }
    if (bufferBits | BufferBitDepth   != 0) { code |= GL_DEPTH_BUFFER_BIT;   }
    if (bufferBits | BufferBitStencil != 0) { code |= GL_STENCIL_BUFFER_BIT; }

    if (code == 0u)
    {
        logError("ENUMS", "invalid buffer bits");
        assert(0);

        return GL_COLOR_BUFFER_BIT;
    }
    
    return code;
}

unsigned int wrapToCode(Wrap wrap)
{
    switch (wrap)
    {
        case WrapRepeat:            return GL_REPEAT;
        case WrapMirroredRepeat:    return GL_MIRRORED_REPEAT;
        case WrapClampToEdge:       return GL_CLAMP_TO_EDGE;
        case WrapClampToBorder:     return GL_CLAMP_TO_BORDER;
        case WrapMirrorClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
    }

    logError("ENUMS", "invalid wrap");
    assert(0);

    return GL_REPEAT;
}

unsigned int minFilterToCode(MinFilter minFilter)
{
    switch (minFilter)
    {
        case MinFilterNearest:              return GL_NEAREST;
        case MinFilterLinear:               return GL_LINEAR;
        case MinFilterNearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
        case MinFilterLinearMipmapNearest:  return GL_LINEAR_MIPMAP_NEAREST;
        case MinFilterNearestMipmapLinear:  return GL_NEAREST_MIPMAP_LINEAR;
        case MinFilterLinearMipmapLinear:   return GL_LINEAR_MIPMAP_LINEAR;
    }

    logError("ENUMS", "invalid min filter");
    assert(0);

    return GL_NEAREST;
}

unsigned int magFilterToCode(MagFilter magFilter)
{
    switch (magFilter)
    {
        case MagFilterNearest:  return GL_NEAREST;
        case MagFilterLinear:   return GL_LINEAR;
    }

    logWarning("ENUMS", "invalid mag filter");
    assert(0);

    return GL_NEAREST;
}

unsigned int compareModeToCode(CompareMode compareMode)
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

unsigned int compareFuncToCode(CompareFunc compareFunc)
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

unsigned int stencilOperationToCode(StencilOperation stencilOperation)
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

unsigned int faceToCode(Face face)
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

unsigned int frontFaceToCode(FrontFace frontFace)
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

unsigned int blendFactorToCode(BlendFactor blendFactor)
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

unsigned int blendEquationToCode(BlendEquation blendEquation)
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

unsigned int polygonModeToCode(PolygonMode polygonMode)
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

unsigned int drawModeToCode(DrawMode drawMode)
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

unsigned int bufferUsageToCode(BufferUsage bufferUsage)
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

