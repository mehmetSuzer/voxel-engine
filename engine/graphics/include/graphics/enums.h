
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
    CapabilitySampleAlphaToOne      =  8, // Forces the alpha component of a fragment to 1.0 after utilizing it for alpha-to-coverage.
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
    TextureWrapClampToBorder     = 3, // Fills any coordinates outside the [0, 1] range with a user-specified, solid background border colour.
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

typedef enum TextureAccess
{
    TextureAccessReadOnly  = 0, // The shader can read pixel data from the texture, but it is strictly forbidden from modifying it.
    TextureAccessWriteOnly = 1, // The shader can write new data to the texture, but it cannot read what was previously there.
    TextureAccessReadWrite = 2, // The shader can both read from and write to the exact same texture during the same pass.
} TextureAccess;

unsigned int textureAccessToNative(TextureAccess textureAccess);

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
    BlendEquationReverseSubtract = 2, // Subtracts the scaled source colour from the scaled destination color (D - S), useful for casting shadows or creating inverted colour variations.
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
} BufferUsage;

unsigned int bufferUsageToNative(BufferUsage bufferUsage);

typedef enum BufferStorageBit
{
    BufferStorageBitMapRead        = 0x00000001, // Allows the CPU to map this buffer using glMapBufferRange.
    BufferStorageBitMapWrite       = 0x00000002, // Allows the CPU to write to this buffer using glMapBufferRange.
    BufferStorageBitMapPersistent  = 0x00000004, // Allows the buffer pointer to remain mapped permanently, even during GPU execution.
    BufferStorageBitMapCoherent    = 0x00000008, // Automatically synchronises CPU/GPU memory caches for persistent mapping.
    BufferStorageBitDynamicStorage = 0x00000010, // Allows updating the buffer contents via glBufferSubData / glCopyBufferSubData.
    BufferStorageBitClientStorage  = 0x00000020, // Hints that the driver should store this buffer in client (system) memory.
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
    BufferTargetVertexArray,        // Vertex attribute data (positions, normals, texcoords, colors).
    BufferTargetElementArray,       // Vertex indices for indexed drawing
    BufferTargetShaderStorage,      // (SSBO) High-capacity, read-and-write structured memory arrays inside shaders.
    BufferTargetUniform,            // (UBO) High-speed read-only constants for uniform blocks across multiple shaders.
    BufferTargetAtomicCounter,      // High-performance storage specifically reserved for synchronized atomic counters shared across shaders.
    BufferTargetDispatchIndirect,   // Arguments for compute shader dispatches (glDispatchComputeIndirect).
    BufferTargetDrawIndirect,       // Arguments for structured draw calls (glDrawArraysIndirect, glDrawElementsIndirect).
    BufferTargetPixelPack,          // Destination target for reading pixel data out of OpenGL (e.g., taking a screenshot with glReadPixels).
    BufferTargetPixelUnpack,        // Source target for streaming pixel data into textures (e.g., glTexImage2D decompression/loading).
    BufferTargetTexture,            // Backing data target used when wrapping a buffer object as a massive 1D texture wrapper ("Buffer Textures").
    BufferTargetTransformFeedback,  // Captures vertex data emitted from the Geometry or Vertex shader stages before it rasterizes.
    BufferTargetQuery,              // Destination target where asynchronous query results (like occlusion tests or timer benchmarks) are directly written.
    BufferTargetCopyRead,           // A generic staging target used as the source when copying data from one buffer to another without breaking existing bindings.
    BufferTargetCopyWrite,          // A generic staging target used as the destination when copying data between buffers.
} BufferTarget;

unsigned int bufferTargetToNative(BufferTarget bufferTarget);

