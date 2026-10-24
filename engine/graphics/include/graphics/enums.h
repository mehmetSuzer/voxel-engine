
#pragma once

#include <stdint.h>

typedef enum GraphicsCapability
{
    GraphicsCapabilityDepthTest             =  0, // Compares the depth of incoming fragments with the depth buffer to discard hidden pixels.
    GraphicsCapabilityStencilTest           =  1, // Discards fragments based on a custom bitmask test.
    GraphicsCapabilityScissorTest           =  2, // Restricts all rendering to a strict rectangular portion of the screen.
    GraphicsCapabilityBlend                 =  3, // Combines the incoming colour with the existing colour in the framebuffer.
    GraphicsCapabilityCullFace              =  4, // Automatically discards geometry that faces away from the camera.
    GraphicsCapabilityDither                =  5, // Mixes adjacent pixel colours to prevent colour banding on low bit-depth displays.
    GraphicsCapabilityMultisample           =  6, // Activates multi-sample anti-aliasing (MSAA) to smooth out jagged geometric edges.
    GraphicsCapabilitySampleAlphaToCoverage =  7, // Uses the alpha value of a fragment to determine MSAA coverage masks.
    GraphicsCapabilitySampleAlphaToOne      =  8, // Forces the alpha component of a fragment to 1.0 after utilising it for alpha-to-coverage.
    GraphicsCapabilitySampleCoverage        =  9, // Modifies the final fragment coverage values by applying an additional mask or inversion.
    GraphicsCapabilityDepthClamp            = 10, // Clamps fragments falling outside the near or far clip planes instead of discarding them.
    GraphicsCapabilityPolygonOffsetPoint    = 11, // Adds a depth offset when rendering polygons in point mode to prevent z-fighting.
    GraphicsCapabilityPolygonOffsetLine     = 12, // Adds a depth offset when rendering polygons in line mode to cleanly overlay outlines.
    GraphicsCapabilityPolygonOffsetFill     = 13, // Adds a depth offset when rendering polygons to prevent z-fighting with layered surfaces.
    GraphicsCapabilityProgramPointSize      = 14, // Allows vertex shaders to dynamically set custom pixel sizes for points.
    GraphicsCapabilityFramebufferSRGB       = 15, // Automatically applies gamma correction when writing colours to the framebuffer.
    GraphicsCapabilityPrimitiveRestart      = 16, // Uses a special index value to break up and start new primitive strips or fans.
} GraphicsCapability;

uint32_t graphicsCapabilityToNative(GraphicsCapability graphicsCapability);

typedef enum BufferBit
{
    BufferBitNone    = 0x00000000, // No buffers.
    BufferBitColour  = 0x00000001, // Represents the colour buffer, which stores the final RGBA pixel colours.
    BufferBitDepth   = 0x00000002, // Represents the depth buffer (Z-buffer), which stores distance values for each pixel.
    BufferBitStencil = 0x00000004, // Represents the stencil buffer, which stores integer masks used to restrict or allow rendering.
    BufferBitAll     = BufferBitColour | BufferBitDepth | BufferBitStencil, // Represents all buffers.
} BufferBit;

uint32_t bufferBitsToNative(BufferBit bufferBits);

typedef enum TextureWrap
{
    TextureWrapRepeat            = 0, // Repeats the texture image like a grid pattern when coordinates go beyond the boundary.
    TextureWrapMirroredRepeat    = 1, // Repeats the texture image but mirrors it with every iteration to create a seamless tiling effect.
    TextureWrapClampToEdge       = 2, // Clamps out-of-bounds coordinates to the edge pixels, stretching the final border pixels infinitely.
    TextureWrapClampToBorder     = 3, // Fills any coordinates outside [0.0, 1.0] with a user-specified, solid background border colour.
    TextureWrapMirrorClampToEdge = 4, // Mirrors the texture once across zero, then clamps any coordinates beyond that.
} TextureWrap;

int32_t textureWrapToNative(TextureWrap textureWrap);

typedef enum TextureMinFilter
{
    TextureMinFilterNearest              = 0, // Samples the single closest pixel.
    TextureMinFilterLinear               = 1, // Performs bilinear filtering on closest pixels.
    TextureMinFilterNearestMipmapNearest = 2, // Selects nearest mipmap level; samples single nearest pixel.
    TextureMinFilterLinearMipmapNearest  = 3, // Selects nearest mipmap level; performs bilinear filtering.
    TextureMinFilterNearestMipmapLinear  = 4, // Blends linearly between mipmap levels; samples single nearest pixel.
    TextureMinFilterLinearMipmapLinear   = 5, // Performs trilinear filtering across mipmap levels.
} TextureMinFilter;

int32_t textureMinFilterToNative(TextureMinFilter textureMinFilter);

typedef enum TextureMagFilter
{
    TextureMagFilterNearest = 0, // Selects the single closest pixel to the coordinates.
    TextureMagFilterLinear  = 1, // Blends the four closest pixels together (bilinear filtering).
} TextureMagFilter;

int32_t textureMagFilterToNative(TextureMagFilter textureMagFilter);

typedef enum CompareMode
{
    CompareModeNone               = 0, // No depth comparison; samples raw values.
    CompareModeReferenceToTexture = 1, // Compares reference value against sampled depth.
} CompareMode;

int32_t compareModeToNative(CompareMode compareMode);

typedef enum CompareFunction
{
    CompareFunctionNever        = 0, // Automatically fails the comparison, preventing any incoming fragments from passing the test.
    CompareFunctionEqual        = 1, // Passes the test when the incoming value is equal to the reference or buffer value.
    CompareFunctionLess         = 2, // Passes the test when the incoming value is less than the reference or buffer value.
    CompareFunctionLessEqual    = 3, // Passes the test when the incoming value is less than or equal to the reference or buffer value.
    CompareFunctionGreater      = 4, // Passes the test when the incoming value is greater than the reference or buffer value.
    CompareFunctionGreaterEqual = 5, // Passes the test when the incoming value is greater than or equal to the reference or buffer value.
    CompareFunctionNotEqual     = 6, // Passes the test when the incoming value is not equal to the reference or buffer value.
    CompareFunctionAlways       = 7, // Automatically passes the comparison, allowing all incoming fragments to clear the test condition.
} CompareFunction;

uint32_t compareFunctionToNative(CompareFunction compareFunction);

typedef enum StencilOperation
{
    StencilOperationKeep          = 0, // Leaves the current stencil buffer value completely unchanged.
    StencilOperationZero          = 1, // Sets the stencil buffer value to zero.
    StencilOperationReplace       = 2, // Overwrites the stencil buffer value with the user-defined stencil reference value.
    StencilOperationIncrement     = 3, // Increases the current stencil value by one, clamping it to the maximum value if it overflows.
    StencilOperationIncrementWrap = 4, // Increases the current stencil value by one, wrapping it back around to zero if it overflows.
    StencilOperationDecrement     = 5, // Decreases the current stencil value by one, clamping it to zero if it underflows.
    StencilOperationDecrementWrap = 6, // Decreases the current stencil value by one, wrapping it around to the maximum value if it underflows.
    StencilOperationInvert        = 7, // Performs a bitwise NOT operation, flipping all the bits of the current stencil value.
} StencilOperation;

uint32_t stencilOperationToNative(StencilOperation stencilOperation);

typedef enum Face
{
    FaceFront = 0, // Targets only the front-facing geometry.
    FaceBack  = 1, // Targets only the back-facing geometry.
    FaceBoth  = 2, // Targets both the front-facing and back-facing geometry.
} Face;

uint32_t faceToNative(Face face);

typedef enum FrontFace
{
    FrontFaceCW  = 0, // Defines a polygon as front-facing when its vertices are ordered in a clockwise direction on screen.
    FrontFaceCCW = 1, // Defines a polygon as front-facing when its vertices are ordered in a counter-clockwise direction on screen.
} FrontFace;

uint32_t frontFaceToNative(FrontFace frontFace);

typedef enum BlendFactor
{
    BlendFactorZero                   =  0, // Multiplies by (0, 0, 0, 0).
    BlendFactorOne                    =  1, // Multiplies by (1, 1, 1, 1).
    BlendFactorSrcColour              =  2, // Multiplies by source colour.
    BlendFactorOneMinusSrcColour      =  3, // Multiplies by (1 - source colour).
    BlendFactorDstColour              =  4, // Multiplies by destination colour.
    BlendFactorOneMinusDstColour      =  5, // Multiplies by (1 - destination colour).
    BlendFactorSrcAlpha               =  6, // Multiplies by source alpha.
    BlendFactorOneMinusSrcAlpha       =  7, // Multiplies by (1 - source alpha).
    BlendFactorDstAlpha               =  8, // Multiplies by destination alpha.
    BlendFactorOneMinusDstAlpha       =  9, // Multiplies by (1 - destination alpha).
    BlendFactorConstantColour         = 10, // Multiplies by user-defined constant colour.
    BlendFactorOneMinusConstantColour = 11, // Multiplies by (1 - user-defined constant colour).
    BlendFactorConstantAlpha          = 12, // Multiplies by alpha of user-defined constant colour.
    BlendFactorOneMinusConstantAlpha  = 13, // Multiplies by (1 - alpha of user-defined constant colour).
    BlendFactorSrcAlphaSaturate       = 14, // Multiplies by min(source alpha, 1 - destination alpha).
} BlendFactor;

uint32_t blendFactorToNative(BlendFactor blendFactor);

typedef enum BlendEquation
{
    BlendEquationAdd             = 0, // Adds source and destination (S + D).
    BlendEquationSubtract        = 1, // Subtracts destination from source (S - D).
    BlendEquationReverseSubtract = 2, // Subtracts source from destination (D - S).
    BlendEquationMin             = 3, // Selects minimum of source and destination (min(S, D)).
    BlendEquationMax             = 4, // Selects maximum of source and destination (max(S, D)).
} BlendEquation;

uint32_t blendEquationToNative(BlendEquation blendEquation);

typedef enum PolygonMode
{
    PolygonModePoint = 0, // Draws only a single pixel point at each vertex, skipping the lines and filled areas entirely.
    PolygonModeLine  = 1, // Draws only the outlines connecting the vertices, displaying the geometry as a classic wireframe mesh.
    PolygonModeFill  = 2, // Draws the entire polygon as a solid, filled surface, which is the standard mode for rendering 3D objects.
} PolygonMode;

uint32_t polygonModeToNative(PolygonMode polygonMode);

typedef enum DrawMode
{
    DrawModePoints        = 0, // Renders each vertex as an isolated point.
    DrawModeLines         = 1, // Connects vertex pairs into independent line segments.
    DrawModeLineStrip     = 2, // Connects vertices in a continuous sequence.
    DrawModeLineLoop      = 3, // Connects vertices in a continuous sequence, closing the shape back to the start.
    DrawModeTriangles     = 4, // Groups vertex triplets into independent triangles.
    DrawModeTriangleStrip = 5, // Connects vertices into a shared ribbon of triangles.
    DrawModeTriangleFan   = 6, // Connects vertices into a fan sharing a central starting vertex.
} DrawMode;

uint32_t drawModeToNative(DrawMode drawMode);

typedef enum MemoryBarrierBit
{
    MemoryBarrierBitNone                 = 0x00000000, // No memory barrier.
    MemoryBarrierBitVertexAttributeArray = 0x00000001, // Synchronises vertex buffer updates for attributes.
    MemoryBarrierBitElementArray         = 0x00000002, // Synchronises index buffer updates for drawing.
    MemoryBarrierBitUniform              = 0x00000004, // Synchronises uniform and UBO updates for shaders.
    MemoryBarrierBitTextureFetch         = 0x00000008, // Synchronises texture updates for samplers.
    MemoryBarrierBitShaderImageAccess    = 0x00000010, // Synchronises image load/store operations.
    MemoryBarrierBitCommand              = 0x00000020, // Synchronises indirect command buffers.
    MemoryBarrierBitPixelBuffer          = 0x00000040, // Synchronises pixel pack/unpack buffers.
    MemoryBarrierBitTextureUpdate        = 0x00000080, // Synchronises direct texture modifications.
    MemoryBarrierBitBufferUpdate         = 0x00000100, // Synchronises direct buffer modifications.
    MemoryBarrierBitFramebuffer          = 0x00000200, // Synchronises framebuffer attachment reads/writes.
    MemoryBarrierBitTransformFeedback    = 0x00000400, // Synchronises transform feedback buffers.
    MemoryBarrierBitAtomicCounter        = 0x00000800, // Synchronises shader atomic counters.
    MemoryBarrierBitShaderStorage        = 0x00001000, // Synchronises SSBO accesses.
    MemoryBarrierBitClientMappedBuffer   = 0x00002000, // Synchronises CPU-mapped buffer writes for GPU.
    MemoryBarrierBitQueryBuffer          = 0x00004000, // Synchronises query result buffers.
    MemoryBarrierBitAll                  = 0x7FFFFFFF, // Encompasses all memory barriers.
} MemoryBarrierBit;

uint32_t memoryBarrierBitsToNative(MemoryBarrierBit memoryBarrierBits);

typedef enum AccessPolicy
{
    AccessPolicyReadOnly  = 0, // Indicates that the mapped buffer or the texture image can only be read.
    AccessPolicyWriteOnly = 1, // Indicates that the mapped buffer or the texture image can only be written.
    AccessPolicyReadWrite = 2, // Indicates that the mapped buffer or the texture image can be both read and written.
} AccessPolicy;

uint32_t accessPolicyToNative(AccessPolicy accessPolicy);

typedef enum BufferUsage
{
    BufferUsageStaticDraw  = 0, // Uploads once from CPU to GPU; used frequently.
    BufferUsageDynamicDraw = 1, // Updates occasionally from CPU to GPU; used frequently.
    BufferUsageStreamDraw  = 2, // Streams every frame from CPU to GPU; used immediately.
    BufferUsageStaticRead  = 3, // Uploads once from GPU to CPU; reads repeatedly.
    BufferUsageDynamicRead = 4, // Downloads occasionally from GPU to CPU; reads periodically.
    BufferUsageStreamRead  = 5, // Streams continuously from GPU to CPU; reads immediately.
    BufferUsageStaticCopy  = 6, // Copies once internally on GPU; used exclusively as input.
    BufferUsageDynamicCopy = 7, // Modifies occasionally via internal GPU transfers.
    BufferUsageStreamCopy  = 8, // Copies every frame via internal GPU-to-GPU memory transfers.
} BufferUsage;

uint32_t bufferUsageToNative(BufferUsage bufferUsage);

typedef enum BufferStorageBit
{
    BufferStorageBitNone           = 0x00000000, // No storage flags.
    BufferStorageBitMapRead        = 0x00000001, // Enables CPU mapping for reading.
    BufferStorageBitMapWrite       = 0x00000002, // Enables CPU mapping for writing.
    BufferStorageBitMapPersistent  = 0x00000004, // Enables persistent mapping across GPU executions.
    BufferStorageBitMapCoherent    = 0x00000008, // Automatically synchronizes CPU/GPU memory caches.
    BufferStorageBitDynamicStorage = 0x00000010, // Enables direct updates by the CPU.
    BufferStorageBitClientStorage  = 0x00000020, // Hints driver to store buffer in system RAM.
} BufferStorageBit;

uint32_t bufferStorageBitsToNative(BufferStorageBit bufferStorageBits);

typedef enum BufferMapBit
{
    BufferMapBitNone             = 0x00000000, // No mapping flags.
    BufferMapBitRead             = 0x00000001, // Enables CPU reading from the mapped pointer.
    BufferMapBitWrite            = 0x00000002, // Enables CPU writing to the mapped pointer.
    BufferMapBitInvalidateRange  = 0x00000004, // Discards only the specified mapped byte range.
    BufferMapBitInvalidateBuffer = 0x00000008, // Discards entire buffer contents to avoid pipeline stalls.
    BufferMapBitFlushExplicit    = 0x00000010, // Requires explicit manual flushing of modified sub-ranges.
    BufferMapBitUnsynchronised   = 0x00000020, // Bypasses automatic driver synchronization, requiring manual fences.
    BufferMapBitPersistent       = 0x00000040, // Keeps the mapping pointer valid indefinitely.
    BufferMapBitCoherent         = 0x00000080, // Guarantees automatic visibility of CPU/GPU memory writes.
} BufferMapBit;

uint32_t bufferMapBitsToNative(BufferMapBit bufferMapBits);

typedef enum BufferTarget
{
    BufferTargetVertexArray       =  0, // Stores vertex attribute data.
    BufferTargetElementArray      =  1, // Stores vertex indices for indexed drawing.
    BufferTargetShaderStorage     =  2, // Provides read-write structured memory arrays for shaders (SSBO).
    BufferTargetUniform           =  3, // Stores read-only constant data for uniform blocks (UBO).
    BufferTargetAtomicCounter     =  4, // Stores synchronised atomic counters for shaders.
    BufferTargetDispatchIndirect  =  5, // Stores arguments for compute shader dispatches.
    BufferTargetDrawIndirect      =  6, // Stores arguments for structured draw calls.
    BufferTargetPixelPack         =  7, // Stores pixel data read out from the graphics API.
    BufferTargetPixelUnpack       =  8, // Supplies pixel data streams for loading textures.
    BufferTargetTexture           =  9, // Backs buffer objects used as 1D texture wrappers.
    BufferTargetTransformFeedback = 10, // Captures emitted vertex data before rasterization.
    BufferTargetQuery             = 11, // Stores asynchronous query results (e.g., occlusion or timers).
    BufferTargetCopyRead          = 12, // Acts as source staging target for buffer copies.
    BufferTargetCopyWrite         = 13, // Acts as destination staging target for buffer copies.
} BufferTarget;

uint32_t bufferTargetToNative(BufferTarget bufferTarget);

typedef enum ExternalFormat
{
    // Standard floating/normalised layouts

    ExternalFormatRed  = 0, // Single channel normalised to [0.0, 1.0]; sampled as vec4(R, 0, 0, 1).
    ExternalFormatRG   = 1, // Two channels normalised to [0.0, 1.0]; sampled as vec4(R, G, 0, 1).
    ExternalFormatRGB  = 2, // Three channels normalised to [0.0, 1.0]; sampled as vec4(R, G, B, 1).
    ExternalFormatRGBA = 3, // Four channels normalised to [0.0, 1.0]; sampled as vec4(R, G, B, A).
    ExternalFormatBGR  = 4, // Reversed three channels normalised to [0.0, 1.0]; sampled as vec4(R, G, B, 1).
    ExternalFormatBGRA = 5, // Reversed four channels normalised to [0.0, 1.0]; sampled as vec4(R, G, B, A).

    // Pure integer layouts

    ExternalFormatRedInteger  =  6, // Single integer channel; sampled as ivec4(R, 0, 0, 1).
    ExternalFormatRGInteger   =  7, // Two integer channels; sampled as ivec4(R, G, 0, 1).
    ExternalFormatRGBInteger  =  8, // Three integer channels; sampled as ivec4(R, G, B, 1).
    ExternalFormatRGBAInteger =  9, // Four integer channels; sampled as ivec4(R, G, B, A).
    ExternalFormatBGRInteger  = 10, // Reversed three integer channels; sampled as ivec4(R, G, B, 1).
    ExternalFormatBGRAInteger = 11, // Reversed four integer channels; sampled as ivec4(R, G, B, A).

    // Depth & stencil layouts

    ExternalFormatDepth        = 12, // Normalised depth channel; sampled as vec4(D, 0, 0, 1) or float.
    ExternalFormatStencil      = 13, // Integer stencil channel; sampled as uvec4(S, 0, 0, 1).
    ExternalFormatDepthStencil = 14, // Combined depth and stencil channels; sampled via custom configurations.
} ExternalFormat;

uint32_t externalFormatToNative(ExternalFormat externalFormat);

typedef enum InternalFormat
{
    // 8-bit normalised formats (standard images / LDR)

    InternalFormatR8    = 0, // Stores 8-bit single channel normalised to [0.0, 1.0].
    InternalFormatRG8   = 1, // Stores 8-bit two channels normalised to [0.0, 1.0].
    InternalFormatRGB8  = 2, // Stores 8-bit three channels normalised to [0.0, 1.0].
    InternalFormatRGBA8 = 3, // Stores 8-bit four channels normalised to [0.0, 1.0].
    
    // Signed normalised formats (values mapped from [-1.0, 1.0])
    
    InternalFormatR8SignedNormalised    = 4, // Stores 8-bit single channel signed normalised to [-1.0, 1.0].
    InternalFormatRG8SignedNormalised   = 5, // Stores 8-bit two channels signed normalised to [-1.0, 1.0].
    InternalFormatRGB8SignedNormalised  = 6, // Stores 8-bit three channels signed normalised to [-1.0, 1.0].
    InternalFormatRGBA8SignedNormalised = 7, // Stores 8-bit four channels signed normalised to [-1.0, 1.0].

    // 16-bit normalised formats (high-precision LDR / UI / heightmaps)
    
    InternalFormatR16    =  8, // Stores 16-bit single channel normalised to [0.0, 1.0].
    InternalFormatRG16   =  9, // Stores 16-bit two channels normalised to [0.0, 1.0].
    InternalFormatRGB16  = 10, // Stores 16-bit three channels normalised to [0.0, 1.0].
    InternalFormatRGBA16 = 11, // Stores 16-bit four channels normalised to [0.0, 1.0].
    
    InternalFormatR16SignedNormalised    = 12, // Stores 16-bit single channel signed normalised to [-1.0, 1.0].
    InternalFormatRG16SignedNormalised   = 13, // Stores 16-bit two channels signed normalised to [-1.0, 1.0].
    InternalFormatRGB16SignedNormalised  = 14, // Stores 16-bit three channels signed normalised to [-1.0, 1.0].
    InternalFormatRGBA16SignedNormalised = 15, // Stores 16-bit four channels signed normalised to [-1.0, 1.0].

    // 16-bit floating point formats (HDR / mid-precision / post-processing)
    
    InternalFormatR16F    = 16, // Stores 16-bit floating-point single channel.
    InternalFormatRG16F   = 17, // Stores 16-bit floating-point two channels.
    InternalFormatRGB16F  = 18, // Stores 16-bit floating-point three channels.
    InternalFormatRGBA16F = 19, // Stores 16-bit floating-point four channels.

    // 32-bit floating point formats (extreme precision / compute / G-buffer)
    
    InternalFormatR32F    = 20, // Stores 32-bit floating-point single channel.
    InternalFormatRG32F   = 21, // Stores 32-bit floating-point two channels.
    InternalFormatRGB32F  = 22, // Stores 32-bit floating-point three channels.
    InternalFormatRGBA32F = 23, // Stores 32-bit floating-point four channels.

    // Pure unsigned integer formats (IDs / masks / bitfields)
    
    InternalFormatR8UI    = 24, // Stores unsigned 8-bit single channel integer.
    InternalFormatRG8UI   = 25, // Stores unsigned 8-bit two channel integer.
    InternalFormatRGB8UI  = 26, // Stores unsigned 8-bit three channel integer.
    InternalFormatRGBA8UI = 27, // Stores unsigned 8-bit four channel integer.
    
    InternalFormatR16UI    = 28, // Stores unsigned 16-bit single channel integer.
    InternalFormatRG16UI   = 29, // Stores unsigned 16-bit two channel integer.
    InternalFormatRGB16UI  = 30, // Stores unsigned 16-bit three channel integer.
    InternalFormatRGBA16UI = 31, // Stores unsigned 16-bit four channel integer.
    
    InternalFormatR32UI    = 32, // Stores unsigned 32-bit single channel integer.
    InternalFormatRG32UI   = 33, // Stores unsigned 32-bit two channel integer.
    InternalFormatRGB32UI  = 34, // Stores unsigned 32-bit three channel integer.
    InternalFormatRGBA32UI = 35, // Stores unsigned 32-bit four channel integer.

    // Pure signed integer formats (custom math / data grids)
    
    InternalFormatR8I    = 36, // Stores signed 8-bit single channel integer.
    InternalFormatRG8I   = 37, // Stores signed 8-bit two channel integer.
    InternalFormatRGB8I  = 38, // Stores signed 8-bit three channel integer.
    InternalFormatRGBA8I = 39, // Stores signed 8-bit four channel integer.
    
    InternalFormatR16I    = 40, // Stores signed 16-bit single channel integer.
    InternalFormatRG16I   = 41, // Stores signed 16-bit two channel integer.
    InternalFormatRGB16I  = 42, // Stores signed 16-bit three channel integer.
    InternalFormatRGBA16I = 43, // Stores signed 16-bit four channel integer.
    
    InternalFormatR32I    = 44, // Stores signed 32-bit single channel integer.
    InternalFormatRG32I   = 45, // Stores signed 32-bit two channel integer.
    InternalFormatRGB32I  = 46, // Stores signed 32-bit three channel integer.
    InternalFormatRGBA32I = 47, // Stores signed 32-bit four channel integer.

    // sRGB formats (gamma corrected colour textures)
    
    InternalFormatSRGB8       = 48, // Stores sRGB 3-channel layout with automatic linearisation.
    InternalFormatSRGB8Alpha8 = 49, // Stores sRGB 4-channel layout with automatic linearisation.

    // Depth and Stencil Formats
    
    InternalFormatDepth16          = 50, // Stores 16-bit fixed-depth channel.
    InternalFormatDepth24          = 51, // Stores 24-bit fixed-depth channel.
    InternalFormatDepth32F         = 52, // Stores 32-bit floating-point depth channel.
    InternalFormatDepth24Stencil8  = 53, // Stores interleaved 24-bit depth and 8-bit stencil channels.
    InternalFormatDepth32FStencil8 = 54, // Stores interleaved 32-bit floating-point depth and 8-bit stencil.
} InternalFormat;

uint32_t internalFormatToNative(InternalFormat internalFormat);

typedef enum DataType
{
    // Standard component types

    DataTypeByte    = 0, // Stores signed 8-bit integer.
    DataTypeUByte   = 1, // Stores unsigned 8-bit integer.
    DataTypeShort   = 2, // Stores signed 16-bit integer.
    DataTypeUShort  = 3, // Stores unsigned 16-bit integer.
    DataTypeInt     = 4, // Stores signed 32-bit integer.
    DataTypeUInt    = 5, // Stores unsigned 32-bit integer.
    DataTypeFloat16 = 6, // Stores 16-bit floating-point value.
    DataTypeFloat32 = 7, // Stores 32-bit floating-point value.

    // 8-Bit packed types

    DataTypeR3G3B2 = 8, // Packs 3-bit R, 3-bit G, and 2-bit B.
    DataTypeB2G3R3 = 9, // Packs 2-bit B, 3-bit G, and 3-bit R.

    // 16-Bit packed types

    DataTypeR5G6B5   = 10, // Packs 5-bit R, 6-bit G, and 5-bit B.
    DataTypeB5G6R5   = 11, // Packs 5-bit B, 6-bit G, and 5-bit R.
    DataTypeR4G4B4A4 = 12, // Packs 4-bit R, 4-bit G, 4-bit B, and 4-bit A.
    DataTypeA4B4G4R4 = 13, // Packs 4-bit A, 4-bit B, 4-bit G, and 4-bit R.
    DataTypeR5G5B5A1 = 14, // Packs 5-bit R, 5-bit G, 5-bit B, and 1-bit A.
    DataTypeA1B5G5R5 = 15, // Packs 1-bit A, 5-bit B, 5-bit G, and 5-bit R.

    // 32-Bit packed types

    DataTypeR8G8B8A8    = 16, // Packs 8-bit R, 8-bit G, 8-bit B, and 8-bit A.
    DataTypeA8B8G8R8    = 17, // Packs 8-bit A, 8-bit B, 8-bit G, and 8-bit R.
    DataTypeR10G10B10A2 = 18, // Packs 10-bit R, 10-bit G, 10-bit B, and 2-bit A.
    DataTypeA2B10G10R10 = 19, // Packs 2-bit A, 10-bit B, 10-bit G, and 10-bit R.

    // Special depth/stencil packed types

    DataTypeDepth24Stencil8  = 20, // Packs 24-bit depth and 8-bit stencil.
    DataTypeDepth32FStencil8 = 21, // Packs 32-bit float depth and 8-bit stencil with padding.
} DataType;

uint32_t dataTypeToNative(DataType dataType);

#ifndef NDEBUG
typedef enum DebugSource
{
    DebugSourceAPI            = 0, // Messages generated directly by explicit graphics API calls.
    DebugSourceWindowSystem   = 1, // Messages originating from the underlying window-system graphics API.
    DebugSourceShaderCompiler = 2, // Messages produced by the shader compiler or linker.
    DebugSourceThirdParty     = 3, // Messages generated by third-party libraries or middleware utilising the graphics API.
    DebugSourceApplication    = 4, // Custom messages explicitly injected by your own application code.
    DebugSourceOther          = 5, // Messages from sources that do not fit into any other category.
} DebugSource;

uint32_t debugSourceToNative(DebugSource debugSource);

typedef enum DebugType
{
    DebugTypeError               = 0, // Flags invalid graphics API errors.
    DebugTypeDeprecatedBehaviour = 1, // Warns about deprecated feature usage.
    DebugTypeUndefinedBehaviour  = 2, // Triggers critical warnings for specification violations.
    DebugTypePortability         = 3, // Highlights cross-vendor or cross-platform differences.
    DebugTypePerformance         = 4, // Flags suboptimal usage for graphics hardware.
    DebugTypeMarker              = 5, // Annotates command stream milestones for debugging tools.
    DebugTypePushGroup           = 6, // Enters a nested debug group scope.
    DebugTypePopGroup            = 7, // Exits the current nested debug group scope.
    DebugTypeOther               = 8, // Represents miscellaneous unclassified events.
} DebugType;

uint32_t debugTypeToNative(DebugType debugType);

typedef enum DebugSeverity
{
    DebugSeverityVerbose = 0, // Used for low-priority, purely informational messages or vendor-specific hints.
    DebugSeverityInfo    = 1, // Used for non-critical details or non-urgent performance recommendations.
    DebugSeverityWarning = 2, // Used for moderate issues such as severe performance bottlenecks or deprecated behaviours.
    DebugSeverityError   = 3, // Used for critical errors, API abuses, or undefined behaviours.
} DebugSeverity;

uint32_t debugSeverityToNative(DebugSeverity debugSeverity);
#endif

