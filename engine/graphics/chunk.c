
#include "chunk.h"

typedef enum
{
    NormalRight = 0, // (+1.0,  0.0,  0.0)
    NormalLeft  = 1, // (-1.0,  0.0,  0.0)
    NormalUp    = 2, // ( 0.0, +1.0,  0.0)
    NormalDown  = 3, // ( 0.0, -1.0,  0.0)
    NormalBack  = 4, // ( 0.0,  0.0, +1.0)
    NormalFront = 5, // ( 0.0,  0.0, -1.0)
} Normal;

typedef enum
{
    UVBottomLeft  = 0, // (0.0, 0.0)
    UVBottomRight = 1, // (1.0, 0.0)
    UVTopRight    = 2, // (1.0, 1.0)
    UVTopLeft     = 3, // (0.0, 1.0)
} UV;

typedef struct 
{
    unsigned int x      : 6;
    unsigned int y      : 6;
    unsigned int z      : 6;
    unsigned int voxel  : 7;
    unsigned int normal : 3;
    unsigned int uv     : 2;
} Vertex;

static void AddRightFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x+1, y,   z+1, voxel, NormalRight, UVBottomLeft };
    v[1] = (Vertex){x+1, y,   z,   voxel, NormalRight, UVBottomRight};
    v[2] = (Vertex){x+1, y+1, z,   voxel, NormalRight, UVTopRight   };
    v[3] = (Vertex){x+1, y,   z+1, voxel, NormalRight, UVBottomLeft };
    v[4] = (Vertex){x+1, y+1, z,   voxel, NormalRight, UVTopRight   };
    v[5] = (Vertex){x+1, y+1, z+1, voxel, NormalRight, UVTopLeft    };
    *numVertices += 6;
}

static void AddLeftFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x,  y,   z,   voxel, NormalLeft, UVBottomLeft };
    v[1] = (Vertex){x,  y,   z+1, voxel, NormalLeft, UVBottomRight};
    v[2] = (Vertex){x,  y+1, z+1, voxel, NormalLeft, UVTopRight   };
    v[3] = (Vertex){x,  y,   z,   voxel, NormalLeft, UVBottomLeft };
    v[4] = (Vertex){x,  y+1, z+1, voxel, NormalLeft, UVTopRight   };
    v[5] = (Vertex){x,  y+1, z,   voxel, NormalLeft, UVTopLeft    };
    *numVertices += 6;
}

static void AddUpFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x,   y+1, z+1, voxel, NormalUp, UVBottomLeft };
    v[1] = (Vertex){x+1, y+1, z+1, voxel, NormalUp, UVBottomRight};
    v[2] = (Vertex){x+1, y+1, z,   voxel, NormalUp, UVTopRight   };
    v[3] = (Vertex){x,   y+1, z+1, voxel, NormalUp, UVBottomLeft };
    v[4] = (Vertex){x+1, y+1, z,   voxel, NormalUp, UVTopRight   };
    v[5] = (Vertex){x,   y+1, z,   voxel, NormalUp, UVTopLeft    };
    *numVertices += 6;
}

static void AddDownFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x,   y,  z,   voxel, NormalDown, UVBottomLeft };
    v[1] = (Vertex){x+1, y,  z,   voxel, NormalDown, UVBottomRight};
    v[2] = (Vertex){x+1, y,  z+1, voxel, NormalDown, UVTopRight   };
    v[3] = (Vertex){x,   y,  z,   voxel, NormalDown, UVBottomLeft };
    v[4] = (Vertex){x+1, y,  z+1, voxel, NormalDown, UVTopRight   };
    v[5] = (Vertex){x,   y,  z+1, voxel, NormalDown, UVTopLeft    };
    *numVertices += 6;
}

static void AddBackFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x,   y,   z+1, voxel, NormalBack, UVBottomLeft };
    v[1] = (Vertex){x+1, y,   z+1, voxel, NormalBack, UVBottomRight};
    v[2] = (Vertex){x+1, y+1, z+1, voxel, NormalBack, UVTopRight   };
    v[3] = (Vertex){x,   y,   z+1, voxel, NormalBack, UVBottomLeft };
    v[4] = (Vertex){x+1, y+1, z+1, voxel, NormalBack, UVTopRight   };
    v[5] = (Vertex){x,   y+1, z+1, voxel, NormalBack, UVTopLeft    };
    *numVertices += 6;
}

static void AddFrontFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (Vertex){x+1, y,   z, voxel, NormalFront, UVBottomLeft };
    v[1] = (Vertex){x,   y,   z, voxel, NormalFront, UVBottomRight};
    v[2] = (Vertex){x,   y+1, z, voxel, NormalFront, UVTopRight   };
    v[3] = (Vertex){x+1, y,   z, voxel, NormalFront, UVBottomLeft };
    v[4] = (Vertex){x,   y+1, z, voxel, NormalFront, UVTopRight   };
    v[5] = (Vertex){x+1, y+1, z, voxel, NormalFront, UVTopLeft    };
    *numVertices += 6;
}

static Voxel GenerateVoxel(unsigned int x, unsigned int y, unsigned int z)
{
    return VOXEL_CYAN;
}

void ChunkCreate(Chunk* chunkOut)
{
    const unsigned int voxelPerChunk = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    const unsigned int facePerVoxel = 6;
    const unsigned int vertexPerFace = 6;
    const unsigned int maxNumVertex = voxelPerChunk * facePerVoxel * vertexPerFace;

    Vertex vertices[maxNumVertex];
    GLsizei numVertices = 0;

    for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
    {
        for (unsigned int y = 0; y < CHUNK_SIZE; ++y)
        {
            for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
            {
                const Voxel voxel = GenerateVoxel(x, y, z);

                if (voxel == VOXEL_AIR)
                {
                    continue;
                }

                AddRightFace(vertices, &numVertices, voxel, x, y, z);
                AddLeftFace (vertices, &numVertices, voxel, x, y, z);
                AddUpFace   (vertices, &numVertices, voxel, x, y, z);
                AddDownFace (vertices, &numVertices, voxel, x, y, z);
                AddBackFace (vertices, &numVertices, voxel, x, y, z);
                AddFrontFace(vertices, &numVertices, voxel, x, y, z);
            }
        }
    }

    chunkOut->numVertices = numVertices;
    glGenVertexArrays(1, &chunkOut->VAO);
    glGenBuffers(1, &chunkOut->VBO);

    glBindVertexArray(chunkOut->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, chunkOut->VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)0);
}

void ChunkDelete(const Chunk* chunk)
{
    glDeleteVertexArrays(1, &chunk->VAO);
    glDeleteBuffers(1, &chunk->VBO);
}

void ChunkDraw(const Chunk* chunk)
{
    glBindVertexArray(chunk->VAO);
    glDrawArrays(GL_TRIANGLES, 0, chunk->numVertices);
}

