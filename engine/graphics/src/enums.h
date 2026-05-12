
#pragma once

typedef enum Capability
{
    CapabilityDepthTest             =  0,
    CapabilityStencilTest           =  1,
    CapabilityScissorTest           =  2,
    CapabilityBlend                 =  3,
    CapabilityCullFace              =  4,
    CapabilityDither                =  5,
    CapabilityMultisample           =  6,
    CapabilitySampleAlphaToCoverage =  7,
    CapabilitySampleAlphaToOne      =  8,
    CapabilitySampleCoverage        =  9,
    CapabilityDepthClamp            = 10,
    CapabilityPolygonOffsetPoint    = 11,
    CapabilityPolygonOffsetLine     = 12,
    CapabilityPolygonOffsetFill     = 13,
    CapabilityProgramPointSize      = 14,
    CapabilityFramebufferSRGB       = 15,
    CapabilityPrimitiveRestart      = 16,
    CapabilityCount,
} Capability;

unsigned int capabilityToCode(Capability capability);

typedef enum BufferBit
{
    BufferBitColour  = 0,
    BufferBitDepth   = 1,
    BufferBitStencil = 2,
    BufferBitCount,
} BufferBit;

unsigned int bufferBitToCode(BufferBit bufferBit);

typedef enum Wrap
{
    WrapRepeat            = 0,
    WrapMirroredRepeat    = 1,
    WrapClampToEdge       = 2,
    WrapClampToBorder     = 3,
    WrapMirrorClampToEdge = 4,
    WrapCount,
} Wrap;

unsigned int wrapToCode(Wrap wrap);

typedef enum MinFilter
{
    MinFilterNearest              = 0,
    MinFilterLinear               = 1,
    MinFilterNearestMipmapNearest = 2,
    MinFilterLinearMipmapNearest  = 3,
    MinFilterNearestMipmapLinear  = 4,
    MinFilterLinearMipmapLinear   = 5,
    MinFilterCount,
} MinFilter;

unsigned int minFilterToCode(MinFilter minFilter);

typedef enum MagFilter
{
    MagFilterNearest = 0,
    MagFilterLinear  = 1,
    MagFilterCount,
} MagFilter;

unsigned int magFilterToCode(MagFilter magFilter);

typedef enum CompareMode
{
    CompareModeNone               = 0,
    CompareModeReferenceToTexture = 1,
    CompareModeCount,
} CompareMode;

unsigned int compareModeToCode(CompareMode compareMode);

typedef enum CompareFunc
{
    CompareFuncNever        = 0,
    CompareFuncEqual        = 1,
    CompareFuncLess         = 2,
    CompareFuncLessEqual    = 3,
    CompareFuncGreater      = 4,
    CompareFuncGreaterEqual = 5,
    CompareFuncNotEqual     = 6,
    CompareFuncAlways       = 7,
    CompareFuncCount,
} CompareFunc;

unsigned int compareFuncToCode(CompareFunc compareFunc);

typedef enum StencilOperation
{
    StencilOperationKeep          = 0,
    StencilOperationZero          = 1,
    StencilOperationReplace       = 2,
    StencilOperationIncrement     = 3,
    StencilOperationIncrementWrap = 4,
    StencilOperationDecrement     = 5,
    StencilOperationDecrementWrap = 6,
    StencilOperationInvert        = 7,
    StencilOperationCount,
} StencilOperation;

unsigned int stencilOperationToCode(StencilOperation stencilOperation);

typedef enum Face
{
    FaceFront = 0,
    FaceBack  = 1,
    FaceBoth  = 2,
    FaceCount,
} Face;

unsigned int faceToCode(Face face);

typedef enum FrontFace
{
    FrontFaceCW  = 0,
    FrontFaceCCW = 1,
    FrontFaceCount,
} FrontFace;

unsigned int frontFaceToCode(FrontFace frontFace);

typedef enum BlendFactor
{
    BlendFactorZero                   =  0,
    BlendFactorOne                    =  1,
    BlendFactorSrcColour              =  2,
    BlendFactorOneMinusSrcColour      =  3,
    BlendFactorDstColour              =  4,
    BlendFactorOneMinusDstColour      =  5,
    BlendFactorSrcAlpha               =  6,
    BlendFactorOneMinusSrcAlpha       =  7,
    BlendFactorDstAlpha               =  8,
    BlendFactorOneMinusDstAlpha       =  9,
    BlendFactorConstantColour         = 10,
    BlendFactorOneMinusConstantColour = 11,
    BlendFactorConstantAlpha          = 12,
    BlendFactorOneMinusConstantAlpha  = 13,
    BlendFactorSrcAlphaSaturate       = 14,
    BlendFactorCount,
} BlendFactor;

unsigned int blendFactorToCode(BlendFactor blendFactor);

typedef enum BlendEquation
{
    BlendEquationAdd             = 0,
    BlendEquationSubtract        = 1,
    BlendEquationReverseSubtract = 2,
    BlendEquationMin             = 3,
    BlendEquationMax             = 4,
    BlendEquationCount,
} BlendEquation;

unsigned int blendEquationToCode(BlendEquation blendEquation);

typedef enum PolygonMode
{
    PolygonModePoint = 0,
    PolygonModeLine  = 1,
    PolygonModeFill  = 2,
    PolygonModeCount,
} PolygonMode;

unsigned int polygonModeToCode(PolygonMode polygonMode);

typedef enum DrawMode
{
    DrawModePoints        = 0,
    DrawModeLines         = 1,
    DrawModeLineStrip     = 2,
    DrawModeLineLoop      = 3,
    DrawModeTriangles     = 4,
    DrawModeTriangleStrip = 5,
    DrawModeTriangleFan   = 6,
} DrawMode;

unsigned int drawModeToCode(DrawMode drawMode);

typedef enum BufferUsage
{
    BufferUsageStaticDraw  = 0, // CPU uploads once, GPU uses many times
    BufferUsageDynamicDraw = 1, // CPU updates occasionally
    BufferUsageStreamDraw  = 2, // CPU updates constantly
    BufferUsageStaticRead  = 3, // GPU writes once, CPU reads many times
    BufferUsageDynamicRead = 4, // GPU writes occasionally, CPU reads
    BufferUsageStreamRead  = 5, // GPU writes frequently, CPU reads
    BufferUsageStaticCopy  = 6, // GPU-to-GPU copy, mostly static
    BufferUsageDynamicCopy = 7, // GPU-to-GPU copy, occasionally updated
    BufferUsageStreamCopy  = 8, // GPU-to-GPU copy, frequently updated
} BufferUsage;

unsigned int bufferUsageToCode(BufferUsage bufferUsage);
