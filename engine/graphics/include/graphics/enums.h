
#pragma once

typedef enum Capability
{
    CapabilityDepthTest             =  0, // Compares the depth of incoming fragments with the depth buffer to discard hidden pixels.
    CapabilityStencilTest           =  1, // Discards fragments based on a custom bitmask test, useful for masking, mirrors, or shadows.
    CapabilityScissorTest           =  2, // Restricts all rendering to a strict rectangular portion of the screen, discarding fragments outside it.
    CapabilityBlend                 =  3, // Combines the incoming colour with the existing colour in the framebuffer based on transparency or alpha values.
    CapabilityCullFace              =  4, // Automatically discards geometry that faces away from the camera to boost rendering performance.
    CapabilityDither                =  5, // Mixes adjacent pixel colours slightly to prevent colour banding on low bit-depth displays.
    CapabilityMultisample           =  6, // Activates multi-sample anti-aliasing (MSAA) to smooth out jagged geometric edges.
    CapabilitySampleAlphaToCoverage =  7, // Uses the alpha value of a fragment to determine MSAA coverage masks, perfect for dense foliage.
    CapabilitySampleAlphaToOne      =  8, // Forces the alpha component of a fragment to 1.0 after utilising it for alpha-to-coverage.
    CapabilitySampleCoverage        =  9, // Modifies the final fragment coverage values by applying an additional logical mask or inversion.
    CapabilityDepthClamp            = 10, // Clamps fragments that fall outside the near or far clipping planes instead of discarding them.
    CapabilityPolygonOffsetPoint    = 11, // Adds a small depth offset when rendering polygons in point/vertex mode to prevent z-fighting.
    CapabilityPolygonOffsetLine     = 12, // Adds a small depth offset when rendering polygons in wireframe/line mode to cleanly overlay outlines.
    CapabilityPolygonOffsetFill     = 13, // Adds a small depth offset when rendering solid polygons to prevent z-fighting with layered surfaces.
    CapabilityProgramPointSize      = 14, // Allows vertex shaders to dynamically set custom pixel sizes for points.
    CapabilityFramebufferSRGB       = 15, // Automatically applies gamma correction (sRGB encoding) when writing colours to the framebuffer.
    CapabilityPrimitiveRestart      = 16, // Uses a special index value (like 0xFFFF) to break up and start new primitive strips or fans in a single draw call.
    CapabilityCount,
} Capability;

unsigned int capabilityToNative(Capability capability);

typedef enum BufferBit
{
    BufferBitColour  = 0x00000001, // Represents the colour buffer, which stores the final RGBA pixel colours intended for display on the screen.
    BufferBitDepth   = 0x00000002, // Represents the depth buffer (Z-buffer), which stores distance values for each pixel to handle 3D occlusion and hidden-surface removal.
    BufferBitStencil = 0x00000004, // Represents the stencil buffer, which stores integer masks used to restrict or allow rendering on a per-pixel basis.
} BufferBit;

unsigned int bufferBitsToNative(BufferBit bufferBits);

typedef enum TextureWrap
{
    TextureWrapRepeat            = 0, // Repeats the texture image like a grid pattern when coordinates go beyond the boundary.
    TextureWrapMirroredRepeat    = 1, // Repeats the texture image but mirrors it with every iteration to create a seamless tiling effect.
    TextureWrapClampToEdge       = 2, // Clamps out-of-bounds coordinates to the edge pixels, stretching the final border pixels infinitely.
    TextureWrapClampToBorder     = 3, // Fills any coordinates outside the [0, 1] range with a user-specified, solid background border colour. Check sampler.borderColour.
    TextureWrapMirrorClampToEdge = 4, // Mirrors the texture once across zero, then clamps any coordinates beyond that directly to the outermost edge pixels.
    TextureWrapCount,
} TextureWrap;

unsigned int textureWrapToNative(TextureWrap textureWrap);

typedef enum TextureMinFilter
{
    TextureMinFilterNearest              = 0, // Selects the single closest pixel (texel) to the coordinates, resulting in a sharp but highly pixelated look.
    TextureMinFilterLinear               = 1, // Blends the four closest pixels together (bilinear filtering), producing a smoother but slightly blurry result.
    TextureMinFilterNearestMipmapNearest = 2, // Chooses the closest matching mipmap level and samples its single nearest pixel without any blending.
    TextureMinFilterLinearMipmapNearest  = 3, // Chooses the closest matching mipmap level and performs a smooth bilinear blend of its neighboring pixels.
    TextureMinFilterNearestMipmapLinear  = 4, // Linearly blends between the two closest mipmap levels, sampling the single nearest pixel from each.
    TextureMinFilterLinearMipmapLinear   = 5, // Linearly blends between the two closest mipmap levels using bilinearly filtered samples from both (trilinear filtering).
    TextureMinFilterCount,
} TextureMinFilter;

unsigned int textureMinFilterToNative(TextureMinFilter textureMinFilter);

typedef enum TextureMagFilter
{
    TextureMagFilterNearest = 0, // Selects the single closest pixel (texel) to the coordinates, preserving exact pixel boundaries for a crisp, retro blocky look.
    TextureMagFilterLinear  = 1, // Blends the four closest pixels together (bilinear filtering), smoothing out sharp edges to prevent visible pixelation.
    TextureMagFilterCount,
} TextureMagFilter;

unsigned int textureMagFilterToNative(TextureMagFilter textureMagFilter);

typedef enum CompareMode
{
    CompareModeNone               = 0, // Disables depth comparison, allowing the shader to sample the raw depth/shadow map values directly as regular grayscale texture data.
    CompareModeReferenceToTexture = 1, // Compares an incoming depth reference value against the sampled depth value, returning a 0.0 or 1.0 mask for shadow calculations.
    CompareModeCount,
} CompareMode;

unsigned int compareModeToNative(CompareMode compareMode);

typedef enum CompareFunc
{
    CompareFuncNever        = 0, // Automatically fails the comparison, preventing any incoming fragments from passing the test.
    CompareFuncEqual        = 1, // Passes the test only when the incoming value is exactly equal to the existing reference or buffer value.
    CompareFuncLess         = 2, // Passes the test when the incoming value is less than the existing reference or buffer value.
    CompareFuncLessEqual    = 3, // Passes the test when the incoming value is less than or equal to the existing reference or buffer value.
    CompareFuncGreater      = 4, // Passes the test when the incoming value is greater than the existing reference or buffer value.
    CompareFuncGreaterEqual = 5, // Passes the test when the incoming value is greater than or equal to the existing reference or buffer value.
    CompareFuncNotEqual     = 6, // Passes the test whenever the incoming value does not equal the existing reference or buffer value.
    CompareFuncAlways       = 7, // Automatically passes the comparison, allowing all incoming fragments to clear the test condition.
    CompareFuncCount,
} CompareFunc;

unsigned int compareFuncToNative(CompareFunc compareFunc);

typedef enum StencilOperation
{
    StencilOperationKeep          = 0, // Leaves the current stencil buffer value completely unchanged.
    StencilOperationZero          = 1, // Sets the stencil buffer value to zero.
    StencilOperationReplace       = 2, // Overwrites the stencil buffer value with the user-defined stencil reference value.
    StencilOperationIncrement     = 3, // Increases the current stencil value by one, clamping it to the maximum possible value if it overflows.
    StencilOperationIncrementWrap = 4, // Increases the current stencil value by one, wrapping it back around to zero if it overflows the maximum value.
    StencilOperationDecrement     = 5, // Decreases the current stencil value by one, clamping it to zero if it underflows.
    StencilOperationDecrementWrap = 6, // Decreases the current stencil value by one, wrapping it around to the maximum possible value if it underflows below zero.
    StencilOperationInvert        = 7, // Performs a bitwise NOT operation, flipping all the bits of the current stencil value.
    StencilOperationCount,
} StencilOperation;

unsigned int stencilOperationToNative(StencilOperation stencilOperation);

typedef enum Face
{
    FaceFront = 0, // Targets only the front-facing polygons, which are typically defined by vertices ordered in a counter-clockwise direction.
    FaceBack  = 1, // Targets only the back-facing polygons, which represent the hidden, inward surfaces of closed 3D meshes.
    FaceBoth  = 2, // Targets both the front-facing and back-facing surfaces simultaneously to apply operations uniformly across all geometry.
    FaceCount,
} Face;

unsigned int faceToNative(Face face);

typedef enum FrontFace
{
    FrontFaceCW  = 0, // Defines a polygon as front-facing when its vertices are ordered in a clockwise direction on screen.
    FrontFaceCCW = 1, // Defines a polygon as front-facing when its vertices are ordered in a counter-clockwise direction on screen.
    FrontFaceCount,
} FrontFace;

unsigned int frontFaceToNative(FrontFace frontFace);

typedef enum BlendFactor
{
    BlendFactorZero                   =  0, // Multiplies the colour components by a vector of all zeros (0, 0, 0, 0), effectively removing its contribution.
    BlendFactorOne                    =  1, // Multiplies the colour components by a vector of all ones (1, 1, 1, 1), preserving its original intensity completely.
    BlendFactorSrcColour              =  2, // Multiplies the colour components by the incoming fragment's RGB/A colour channels.
    BlendFactorOneMinusSrcColour      =  3, // Multiplies the colour components by the inverted values of the incoming fragment's RGB/A colour channels.
    BlendFactorDstColour              =  4, // Multiplies the colour components by the RGB/A colour channels currently resting in the framebuffer.
    BlendFactorOneMinusDstColour      =  5, // Multiplies the colour components by the inverted values of the RGB/A colour channels currently in the framebuffer.
    BlendFactorSrcAlpha               =  6, // Multiplies the colour components by the alpha (transparency) value of the incoming fragment.
    BlendFactorOneMinusSrcAlpha       =  7, // Multiplies the colour components by the inverted alpha value of the incoming fragment (the standard mode for typical transparency).
    BlendFactorDstAlpha               =  8, // Multiplies the colour components by the alpha value currently resting in the framebuffer.
    BlendFactorOneMinusDstAlpha       =  9, // Multiplies the colour components by the inverted alpha value currently in the framebuffer.
    BlendFactorConstantColour         = 10, // Multiplies the colour components by a fixed, user-defined colour vector.
    BlendFactorOneMinusConstantColour = 11, // Multiplies the colour components by the inverted values of a fixed, user-defined colour vector.
    BlendFactorConstantAlpha          = 12, // Multiplies the colour components by the fixed alpha value of a user-defined colour vector.
    BlendFactorOneMinusConstantAlpha  = 13, // Multiplies the colour components by the inverted fixed alpha value of a user-defined colour vector.
    BlendFactorSrcAlphaSaturate       = 14, // Multiplies RGB components by the minimum value between source alpha and inverted destination alpha, forcing the final combined alpha to clip at 1.0.
    BlendFactorCount,
} BlendFactor;

unsigned int blendFactorToNative(BlendFactor blendFactor);

typedef enum BlendEquation
{
    BlendEquationAdd             = 0, // Adds the scaled source colour to the scaled destination colour (S + D) to create standard alpha transparency or additive lighting effects.
    BlendEquationSubtract        = 1, // Subtracts the scaled destination colour from the scaled source colour (S - D), typically used for advanced masking or darkening logic.
    BlendEquationReverseSubtract = 2, // Subtracts the scaled source colour from the scaled destination colour (D - S), useful for casting shadows or creating inverted colour variations.
    BlendEquationMin             = 3, // Compares the source and destination components and selects the smaller value for each colour channel (min(S, D)), ignoring the blend factors.
    BlendEquationMax             = 4, // Compares the source and destination components and selects the larger value for each colour channel (max(S, D)), ignoring the blend factors.
    BlendEquationCount,
} BlendEquation;

unsigned int blendEquationToNative(BlendEquation blendEquation);

typedef enum PolygonMode
{
    PolygonModePoint = 0, // Draws only a single pixel point at each vertex, skipping the lines and filled areas entirely.
    PolygonModeLine  = 1, /// Draws only the outlines connecting the vertices, displaying the geometry as a classic wireframe mesh.
    PolygonModeFill  = 2, // Draws the entire polygon as a solid, filled surface, which is the standard mode for rendering 3D objects.
    PolygonModeCount,
} PolygonMode;

unsigned int polygonModeToNative(PolygonMode polygonMode);

typedef enum DrawMode
{
    DrawModePoints        = 0, // Treats each individual vertex as an isolated, standalone point in space.
    DrawModeLines         = 1, // Groups every pair of vertices into separate, independent line segments.
    DrawModeLineStrip     = 2, // Connects the vertices sequentially in a single continuous line from the first vertex to the last.
    DrawModeLineLoop      = 3, // Connects the vertices sequentially in a single continuous line, automatically drawing a final line from the last vertex back to the first to close the shape.
    DrawModeTriangles     = 4, // Groups every triplet of vertices into separate, independent triangles.
    DrawModeTriangleStrip = 5, // Creates a connected ribbon of triangles where each new triangle shares its first two vertices with the preceding one.
    DrawModeTriangleFan   = 6, // Creates a fan-like structure of connected triangles where all triangles share a single, central starting vertex.
    DrawModeCount,
} DrawMode;

unsigned int drawModeToNative(DrawMode drawMode);

typedef enum MemoryBarrierBit
{
    MemoryBarrierBitVertexAttributeArray = 0x00000001, // Ensures updates to vertex buffer objects (VBOs) are visible when the data is consumed by vertex attributes.
    MemoryBarrierBitElementArray         = 0x00000002, // Ensures updates to element buffer objects (EBOs) are visible before the next indexed drawing command.
    MemoryBarrierBitUniform              = 0x00000004, // Ensures updates to uniform buffer objects (UBOs) or standard uniforms are visible to subsequent shader reads.
    MemoryBarrierBitTextureFetch         = 0x00000008, // Ensures that texture fetches via samplers (texture(), etc.) will see updates made to the underlying texture data.
    MemoryBarrierBitShaderImageAccess    = 0x00000010, // Ensures image loads/stores (image2D(), etc.) via shaders will see previous writes.
    MemoryBarrierBitCommand              = 0x00000020, // Ensures writes to buffers used for indirect drawing commands (GL_DRAW_INDIRECT_BUFFER, GL_DISPATCH_INDIRECT_BUFFER, etc.) are complete before the draw/dispatch happens.
    MemoryBarrierBitPixelBuffer          = 0x00000040, // Ensures data written to pixel pack/unpack buffers is visible before a pixel transfer operation (glTexSubImage2D, glReadPixels, etc.).
    MemoryBarrierBitTextureUpdate        = 0x00000080, // Ensures that direct updates to texture data (glTexSubImage2D, glCopyTexSubImage2D, glClearTexImage, etc.) are complete before subsequent commands read or write that texture.
    MemoryBarrierBitBufferUpdate         = 0x00000100, // Ensures that direct writes to buffer object data stores (glBufferSubData, glCopyBufferSubData, glClearBufferSubData, etc.) are complete before subsequent commands read or write that buffer data.
    MemoryBarrierBitFramebuffer          = 0x00000200, // Ensures reads and writes via framebuffer attachments (colour, depth, stencil) are synchronised. This is crucial if you are reading from a texture that you just finished rendering to.
    MemoryBarrierBitTransformFeedback    = 0x00000400, // Ensures writes into transform feedback buffers are visible to subsequent reads (or vice versa).
    MemoryBarrierBitAtomicCounter        = 0x00000800, // Ensures operations on atomic counters in shaders are synchronised.
    MemoryBarrierBitShaderStorage        = 0x00001000, // Ensures accesses to shader storage buffer objects (SSBOs) will reflect previous writes.
    MemoryBarrierBitClientMappedBuffer   = 0x00002000, // Ensures that writes made by the host CPU into a persistently mapped buffer (created without GL_MAP_COHERENT_BIT) are flushed and made visible to the GPU server.
    MemoryBarrierBitQueryBuffer          = 0x00004000, // Ensures writes to query result buffers are visible before the results are read back.
} MemoryBarrierBit;

unsigned int memoryBarrierBitsToNative(MemoryBarrierBit memoryBarrierBits);

typedef enum AccessPolicy
{
    AccessPolicyReadOnly  = 0, // Indicates that the mapped buffer or the texture image can only be read.
    AccessPolicyWriteOnly = 1, // Indicates that the mapped buffer or the texture image can only be written.
    AccessPolicyReadWrite = 2, // Indicates that the mapped buffer or the texture image can be both read and written.
    AccessPolicyCount,
} AccessPolicy;

unsigned int accessPolicyToNative(AccessPolicy accessPolicy);

typedef enum BufferUsage
{
    BufferUsageStaticDraw  = 0, // Tailored for vertex data uploaded once by the CPU and rendered frequently by the GPU (e.g., standard static 3D meshes).
    BufferUsageDynamicDraw = 1, // Optimised for data modified occasionally by the CPU and rendered frequently by the GPU (e.g., dynamic UI elements or moving objects).
    BufferUsageStreamDraw  = 2, // Designed for ephemeral data overwritten by the CPU on almost every frame and rendered immediately by the GPU (e.g., particle systems).
    BufferUsageStaticRead  = 3, // Configured for data written once by the GPU and pulled back repeatedly by the CPU for analysis or storage.
    BufferUsageDynamicRead = 4, // Formatted for data written occasionally by the GPU and downloaded by the CPU to inspect specific rendering results.
    BufferUsageStreamRead  = 5, // Scheduled for data written continuously by the GPU and immediately read back by the CPU (e.g., real-time video capture frames).
    BufferUsageStaticCopy  = 6, // Reserved for persistent data populated by the GPU to be used exclusively as input for other GPU pipelines without CPU involvement.
    BufferUsageDynamicCopy = 7, // Adjusted for internal GPU-to-GPU data transfers that are modified occasionally by rendering side-effects (e.g., transform feedback loops).
    BufferUsageStreamCopy  = 8, // Tuned for high-frequency, internal GPU-to-GPU memory copies executed on almost every frame (e.g., physics computations fed right into render passes).
    BufferUsageCount,
} BufferUsage;

unsigned int bufferUsageToNative(BufferUsage bufferUsage);

typedef enum BufferStorageBit
{
    BufferStorageBitMapRead        = 0x00000001, // Allows the CPU to map this buffer for reading using glMapNamedBuffer or glMapNamedBufferRange.
    BufferStorageBitMapWrite       = 0x00000002, // Allows the CPU to map this buffer for writing using glNamedBufferSubData.
    BufferStorageBitMapPersistent  = 0x00000004, // Allows the buffer pointer to remain mapped permanently, even during GPU execution. Otherwise, glUnmapBuffer must be called before a draw call.
    BufferStorageBitMapCoherent    = 0x00000008, // Automatically synchronises CPU/GPU memory caches for persistent mapping. Otherwise, manual synchronisation is needed with glMemoryBarrier or glFlushMappedBufferRange.
    BufferStorageBitDynamicStorage = 0x00000010, // Allows updating the buffer contents directly from the CPU using glNamedBufferSubData.
    BufferStorageBitClientStorage  = 0x00000020, // Hints that the driver should store this buffer in system RAM rather than local VRAM, if possible.
} BufferStorageBit;

unsigned int bufferStorageBitsToNative(BufferStorageBit bufferStorageBits);

typedef enum BufferMapBit
{
    BufferMapBitRead             = 0x00000001, // Allows the CPU to read from the returned pointer. Mutually exclusive with InvalidateBuffer/InvalidateRange unless Write is also set.
    BufferMapBitWrite            = 0x00000002, // Allows the CPU to write to the returned pointer to update buffer contents.
    BufferMapBitInvalidateRange  = 0x00000004, // Similar to InvalidateBuffer, but only discards the specific byte range being mapped. Leaves the rest of the buffer's data intact.
    BufferMapBitInvalidateBuffer = 0x00000008, // Tells the driver to discard the entire contents of the buffer. This allows the driver to return a brand-new memory pointer immediately, avoiding a pipeline stall if the GPU is still reading from the old data.
    BufferMapBitFlushExplicit    = 0x00000010, // Optimisation for writes: specifies that the CPU will only modify parts of the mapped range. You must manually call glFlushMappedBufferRange for any modified sub-ranges to make them visible to the GPU.
    BufferMapBitUnsynchronised   = 0x00000020, // Tells the driver not to check if the GPU is currently using the buffer. Prevents driver-side stalling, but forces you to handle CPU-GPU synchronisation manually using OpenGL sync fences (GLsync).
    BufferMapBitPersistent       = 0x00000040, // Keeps the returned pointer valid indefinitely, even while the GPU is executing commands that access the buffer. Requires Persistent to be set at buffer creation.
    BufferMapBitCoherent         = 0x00000080, // Guarantees that CPU writes are automatically visible to the GPU (and vice versa) without requiring manual flushing commands. Must be used with Persistent.
} BufferMapBit;

unsigned int bufferMapBitsToNative(BufferMapBit bufferMapBits);

typedef enum BufferTarget
{
    BufferTargetVertexArray       =  0, // Vertex attribute data (positions, normals, texcoords, colours).
    BufferTargetElementArray      =  1, // Vertex indices for indexed drawing
    BufferTargetShaderStorage     =  2, // (SSBO) High-capacity, read-and-write structured memory arrays inside shaders.
    BufferTargetUniform           =  3, // (UBO) High-speed read-only constants for uniform blocks across multiple shaders.
    BufferTargetAtomicCounter     =  4, // High-performance storage specifically reserved for synchronised atomic counters shared across shaders.
    BufferTargetDispatchIndirect  =  5, // Arguments for compute shader dispatches (glDispatchComputeIndirect).
    BufferTargetDrawIndirect      =  6, // Arguments for structured draw calls (glDrawArraysIndirect, glDrawElementsIndirect).
    BufferTargetPixelPack         =  7, // Destination target for reading pixel data out of OpenGL (e.g., taking a screenshot with glReadPixels).
    BufferTargetPixelUnpack       =  8, // Source target for streaming pixel data into textures (e.g., glTexImage2D decompression/loading).
    BufferTargetTexture           =  9, // Backing data target used when wrapping a buffer object as a massive 1D texture wrapper ("Buffer Textures").
    BufferTargetTransformFeedback = 10, // Captures vertex data emitted from the Geometry or Vertex shader stages before it rasterises.
    BufferTargetQuery             = 11, // Destination target where asynchronous query results (like occlusion tests or timer benchmarks) are directly written.
    BufferTargetCopyRead          = 12, // A generic staging target used as the source when copying data from one buffer to another without breaking existing bindings.
    BufferTargetCopyWrite         = 13, // A generic staging target used as the destination when copying data between buffers.
    BufferTargetCount,
} BufferTarget;

unsigned int bufferTargetToNative(BufferTarget bufferTarget);

typedef enum ExternalFormat
{
    // Standard Floating/Normalised Layouts

    ExternalFormatRed   = 0, // 1 channel,             later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    ExternalFormatRG    = 1, // 2 channels,            later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    ExternalFormatRGB   = 2, // 3 channels,            later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    ExternalFormatRGBA  = 3, // 4 channels,            later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R,   G,   B,   A)
    ExternalFormatBGR   = 4, // 3 channels (reversed), later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    ExternalFormatBGRA  = 5, // 4 channels (reversed), later normalised to [0.0, 1.0] for GPU, sampled via samplerND -> vec4(  R,   G,   B,   A)

    // Pure Integer Layouts

    ExternalFormatRedInteger   =  6, // 1 channel,             remains as integer, sampled via isamplerND -> ivec4(  R, 0.0, 0.0, 1.0)
    ExternalFormatRGInteger    =  7, // 2 channels,            remains as integer, sampled via isamplerND -> ivec4(  R,   G, 0.0, 1.0)
    ExternalFormatRGBInteger   =  8, // 3 channels,            remains as integer, sampled via isamplerND -> ivec4(  R,   G,   B, 1.0)
    ExternalFormatRGBAInteger  =  9, // 4 channels,            remains as integer, sampled via isamplerND -> ivec4(  R,   G,   B,   A)
    ExternalFormatBGRInteger   = 10, // 3 channels (reversed), remains as integer, sampled via isamplerND -> ivec4(  R,   G,   B, 1.0)
    ExternalFormatBGRAInteger  = 11, // 4 channels (reversed), remains as integer, sampled via isamplerND -> ivec4(  R,   G,   B,   A)

    // Depth & Stencil Layouts

    ExternalFormatDepth        = 12, // 1 channel,  normalised depth,                   sampled via  samplerND ->  vec4(  D, 0.0, 0.0, 1.0) or sampler2DShadow -> float
    ExternalFormatStencil      = 13, // 1 channel,  remains as integer stencil,         sampled via usamplerND -> uvec4(  S, 0.0, 0.0, 1.0)
    ExternalFormatDepthStencil = 14, // 2 channels, normalised depth + integer stencil, sampled via custom sampler configurations depending on hardware/view

    ExternalFormatCount,
} ExternalFormat;

unsigned int externalFormatToNative(ExternalFormat externalFormat);

typedef enum InternalFormat
{
    // 8-bit Normalised Formats (Standard Images / LDR)

    InternalFormatR8    = 0,  // 1 channel,  8 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG8   = 1,  // 2 channels, 8 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB8  = 2,  // 3 channels, 8 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA8 = 3,  // 4 channels, 8 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B,   A)
    
    // Signed Normalised Formats (Values mapped from [-1.0, 1.0])
    
    InternalFormatR8SignedNormalised    = 4,  // 1 channel,  8 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG8SignedNormalised   = 5,  // 2 channels, 8 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB8SignedNormalised  = 6,  // 3 channels, 8 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA8SignedNormalised = 7,  // 4 channels, 8 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B,   A)

    // 16-bit Normalised Formats (High-Precision LDR / UI / Heightmaps)
    
    InternalFormatR16    = 8,   // 1 channel,  16 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG16   = 9,   // 2 channels, 16 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB16  = 10,  // 3 channels, 16 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA16 = 11,  // 4 channels, 16 bits per channel, normalised to [0.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B,   A)
    
    InternalFormatR16SignedNormalised    = 12, // 1 channel,  16 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG16SignedNormalised   = 13, // 2 channels, 16 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB16SignedNormalised  = 14, // 3 channels, 16 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA16SignedNormalised = 15, // 4 channels, 16 bits per channel, normalised to [-1.0, 1.0] on sample, sampled via samplerND -> vec4(  R,   G,   B,   A)

    // 16-bit Floating Point Formats (HDR / Mid-Precision / Post-Processing)
    
    InternalFormatR16F    = 16, // 1 channel,  passes raw half-floats directly to GPU, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG16F   = 17, // 2 channels, passes raw half-floats directly to GPU, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB16F  = 18, // 3 channels, passes raw half-floats directly to GPU, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA16F = 19, // 4 channels, passes raw half-floats directly to GPU, sampled via samplerND -> vec4(  R,   G,   B,   A)

    // 32-bit Floating Point Formats (Extreme Precision / Compute / G-Buffer)
    
    InternalFormatR32F    = 20, // 1 channel,  passes raw single-floats directly to GPU, sampled via samplerND -> vec4(  R, 0.0, 0.0, 1.0)
    InternalFormatRG32F   = 21, // 2 channels, passes raw single-floats directly to GPU, sampled via samplerND -> vec4(  R,   G, 0.0, 1.0)
    InternalFormatRGB32F  = 22, // 3 channels, passes raw single-floats directly to GPU, sampled via samplerND -> vec4(  R,   G,   B, 1.0)
    InternalFormatRGBA32F = 23, // 4 channels, passes raw single-floats directly to GPU, sampled via samplerND -> vec4(  R,   G,   B,   A)

    // Pure Unsigned Integer Formats (IDs / Masks / Bitfields)
    
    InternalFormatR8UI    = 24, // 1 channel,  remains as unsigned 8-bit integer [0, 255], sampled via usamplerND -> uvec4(R, 0, 0, 1)
    InternalFormatRG8UI   = 25, // 2 channels, remains as unsigned 8-bit integer [0, 255], sampled via usamplerND -> uvec4(R, G, 0, 1)
    InternalFormatRGB8UI  = 26, // 3 channels, remains as unsigned 8-bit integer [0, 255], sampled via usamplerND -> uvec4(R, G, B, 1)
    InternalFormatRGBA8UI = 27, // 4 channels, remains as unsigned 8-bit integer [0, 255], sampled via usamplerND -> uvec4(R, G, B, A)
    
    InternalFormatR16UI    = 28, // 1 channel,  remains as unsigned 16-bit integer [0, 65535], sampled via usamplerND -> uvec4(R, 0, 0, 1)
    InternalFormatRG16UI   = 29, // 2 channels, remains as unsigned 16-bit integer [0, 65535], sampled via usamplerND -> uvec4(R, G, 0, 1)
    InternalFormatRGB16UI  = 30, // 3 channels, remains as unsigned 16-bit integer [0, 65535], sampled via usamplerND -> uvec4(R, G, B, 1)
    InternalFormatRGBA16UI = 31, // 4 channels, remains as unsigned 16-bit integer [0, 65535], sampled via usamplerND -> uvec4(R, G, B, A)
    
    InternalFormatR32UI    = 32, // 1 channel,  remains as unsigned 32-bit integer [0, 4294967295], sampled via usamplerND -> uvec4(R, 0, 0, 1)
    InternalFormatRG32UI   = 33, // 2 channels, remains as unsigned 32-bit integer [0, 4294967295], sampled via usamplerND -> uvec4(R, G, 0, 1)
    InternalFormatRGB32UI  = 34, // 3 channels, remains as unsigned 32-bit integer [0, 4294967295], sampled via usamplerND -> uvec4(R, G, B, 1)
    InternalFormatRGBA32UI = 35, // 4 channels, remains as unsigned 32-bit integer [0, 4294967295], sampled via usamplerND -> uvec4(R, G, B, A)

    // Pure Signed Integer Formats (Custom Math / Data Grids)
    
    InternalFormatR8I    = 36, // 1 channel,  remains as signed 8-bit integer [-128, 127], sampled via isamplerND -> ivec4(R, 0, 0, 1)
    InternalFormatRG8I   = 37, // 2 channels, remains as signed 8-bit integer [-128, 127], sampled via isamplerND -> ivec4(R, G, 0, 1)
    InternalFormatRGB8I  = 38, // 3 channels, remains as signed 8-bit integer [-128, 127], sampled via isamplerND -> ivec4(R, G, B, 1)
    InternalFormatRGBA8I = 39, // 4 channels, remains as signed 8-bit integer [-128, 127], sampled via isamplerND -> ivec4(R, G, B, A)
    
    InternalFormatR16I    = 40, // 1 channel,  remains as signed 16-bit integer [-32768, 32767], sampled via isamplerND -> ivec4(R, 0, 0, 1)
    InternalFormatRG16I   = 41, // 2 channels, remains as signed 16-bit integer [-32768, 32767], sampled via isamplerND -> ivec4(R, G, 0, 1)
    InternalFormatRGB16I  = 42, // 3 channels, remains as signed 16-bit integer [-32768, 32767], sampled via isamplerND -> ivec4(R, G, B, 1)
    InternalFormatRGBA16I = 43, // 4 channels, remains as signed 16-bit integer [-32768, 32767], sampled via isamplerND -> ivec4(R, G, B, A)
    
    InternalFormatR32I    = 44, // 1 channel,  remains as signed 32-bit integer [-2147483648, 2147483647], sampled via isamplerND -> ivec4(R, 0, 0, 1)
    InternalFormatRG32I   = 45, // 2 channels, remains as signed 32-bit integer [-2147483648, 2147483647], sampled via isamplerND -> ivec4(R, G, 0, 1)
    InternalFormatRGB32I  = 46, // 3 channels, remains as signed 32-bit integer [-2147483648, 2147483647], sampled via isamplerND -> ivec4(R, G, B, 1)
    InternalFormatRGBA32I = 47, // 4 channels, remains as signed 32-bit integer [-2147483648, 2147483647], sampled via isamplerND -> ivec4(R, G, B, A)

    // sRGB Formats (Gamma Corrected Colour Textures)
    
    InternalFormatSRGB8       = 48, // 3 channels, automatically linearised via pow(C, 2.2) on sample -> vec4(  R,   G,   B, 1.0)
    InternalFormatSRGB8Alpha8 = 49, // 4 channels, automatically linearises RGB channels    on sample -> vec4(  R,   G,   B,   A)

    // Depth and Stencil Formats
    
    InternalFormatDepth16          = 50, // 1 channel,  normalised fixed-depth, sampled via samplerND -> vec4(  D, 0.0, 0.0, 1.0) or samplerNDShadow -> float
    InternalFormatDepth24          = 51, // 1 channel,  normalised fixed-depth, sampled via samplerND -> vec4(  D, 0.0, 0.0, 1.0) or samplerNDShadow -> float
    InternalFormatDepth32F         = 52, // 1 channel,  passes raw depth float, sampled via samplerND -> vec4(  D, 0.0, 0.0, 1.0) or samplerNDShadow -> float
    InternalFormatDepth24Stencil8  = 53, // 2 channels, interleaved depth + stencil, sampled via custom texture views per-aspect
    InternalFormatDepth32FStencil8 = 54, // 2 channels, interleaved depth float + stencil with 24-bit hidden alignment padding

    InternalFormatCount,
} InternalFormat;

unsigned int internalFormatToNative(InternalFormat internalFormat);

typedef enum DataType
{
    // Standard Component Types

    DataTypeByte    = 0, // Signed 8-bit integer
    DataTypeUByte   = 1, // Unsigned 8-bit integer, the standard for basic PNG/JPG images
    DataTypeShort   = 2, // Signed 16-bit integer
    DataTypeUShort  = 3, // Unsigned 16-bit integer, used for high-precision UI masks or 16-bit heightmaps
    DataTypeInt     = 4, // Signed 32-bit integer
    DataTypeUInt    = 5, // Unsigned 32-bit integer
    DataTypeFloat16 = 6, // 16-bit floating-point number, common for medium-precision HDR buffers
    DataTypeFloat32 = 7, // Standard 32-bit float, used for high-precision vector fields, physics, and HDR calculations

    // 8-Bit Packed Types

    DataTypeR3G3B2 = 8, // [MSB] 3-bit R, 3-bit G, 2-bit B [LSB]
    DataTypeB2G3R3 = 9, // [MSB] 2-bit B, 3-bit G, 3-bit R [LSB]

    // 16-Bit Packed Types

    DataTypeR5G6B5   = 10, // [MSB] 5-bit R, 6-bit G, 5-bit B [LSB]
    DataTypeB5G6R5   = 11, // [MSB] 5-bit B, 6-bit G, 5-bit R [LSB]
    DataTypeR4G4B4A4 = 12, // [MSB] 4-bit R, 4-bit G, 4-bit B, 4-bit A [LSB]
    DataTypeA4B4G4R4 = 13, // [MSB] 4-bit A, 4-bit B, 4-bit G, 4-bit R [LSB]
    DataTypeR5G5B5A1 = 14, // [MSB] 5-bit R, 5-bit G, 5-bit B, 1-bit A [LSB]
    DataTypeA1B5G5R5 = 15, // [MSB] 1-bit A, 5-bit B, 5-bit G, 5-bit R [LSB]

    // 32-Bit Packed Types

    DataTypeR8G8B8A8    = 16, // [MSB]  8-bit R,  8-bit G,  8-bit B,  8-bit A [LSB]
    DataTypeA8B8G8R8    = 17, // [MSB]  8-bit A,  8-bit B,  8-bit G,  8-bit R [LSB]
    DataTypeR10G10B10A2 = 18, // [MSB] 10-bit R, 10-bit G, 10-bit B,  2-bit A [LSB]
    DataTypeA2B10G10R10 = 19, // [MSB]  2-bit A, 10-bit B, 10-bit G, 10-bit R [LSB]

    // Special Depth/Stencil Packed Types

    DataTypeDepth24Stencil8  = 20, // [MSB] 24-bit Depth, 8-bit Stencil [LSB]
    DataTypeDepth32FStencil8 = 21, // [MSB] 24-bit Padding, 8-bit Stencil, 32-bit Float Depth [LSB]

    DataTypeCount,
} DataType;

unsigned int dataTypeToNative(DataType dataType);

