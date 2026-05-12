
#include "vertex.h"
#include "glad/glad.h"

void vertexPBRLinkAttributes()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPBR), (void*)offsetof(VertexPBR, position));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPBR), (void*)offsetof(VertexPBR, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPBR), (void*)offsetof(VertexPBR, tangent));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPBR), (void*)offsetof(VertexPBR, texCoord));
}

void vertexVoxelLinkAttributes()
{
    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(VertexVoxel), (void*)0);
}

