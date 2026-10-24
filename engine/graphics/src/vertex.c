
#include "vertex.h"

void vertexStaticLinkAttributes(VertexArrayID VAO)
{
    vertexArrayLinkAttributeFloat(VAO, 0, 0, 3, offsetof(VertexStatic, position));
    vertexArrayLinkAttributeFloat(VAO, 0, 1, 3, offsetof(VertexStatic, normal));
    vertexArrayLinkAttributeFloat(VAO, 0, 2, 3, offsetof(VertexStatic, tangent));
    vertexArrayLinkAttributeFloat(VAO, 0, 3, 2, offsetof(VertexStatic, texCoords));
}

void vertexUILinkAttributes(VertexArrayID VAO)
{
    vertexArrayLinkAttributeFloat(VAO, 0, 0, 2, offsetof(VertexUI, position));
    vertexArrayLinkAttributeFloat(VAO, 0, 1, 2, offsetof(VertexUI, texCoords));
}

void vertexSkinnedLinkAttributes(VertexArrayID VAO)
{
    vertexArrayLinkAttributeFloat(VAO, 0, 0, 3, offsetof(VertexSkinned, position));
    vertexArrayLinkAttributeFloat(VAO, 0, 1, 3, offsetof(VertexSkinned, normal));
    vertexArrayLinkAttributeFloat(VAO, 0, 2, 3, offsetof(VertexSkinned, tangent));
    vertexArrayLinkAttributeFloat(VAO, 0, 3, 2, offsetof(VertexSkinned, texCoords));
    vertexArrayLinkAttributeUint(VAO, 0, 4, 4, offsetof(VertexSkinned, boneIDs));
    vertexArrayLinkAttributeFloat(VAO, 0, 5, 4, offsetof(VertexSkinned, weights));
}

void vertexVoxelLinkAttributes(VertexArrayID VAO)
{
    vertexArrayLinkAttributeUint(VAO, 0, 0, 1, 0);
}

