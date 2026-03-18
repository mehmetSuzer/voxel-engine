
#include "world.h"

#define CHUNK_SIZE 32
#define WORLD_SIZE  1

typedef struct Chunk
{
    Voxel voxels[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
} Chunk;

typedef struct World
{
    Chunk chunks[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];           // [Z][Y][X]
    GLuint VAOs[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];            // [Z][Y][X]
    GLuint VBOs[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];            // [Z][Y][X]
    GLsizei numVertices[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];    // [Z][Y][X]
    int isDirties[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];          // [Z][Y][X]
} World;
World world;

typedef enum Normal
{
    NormalRight = 0, // (+1.0,  0.0,  0.0)
    NormalLeft  = 1, // (-1.0,  0.0,  0.0)
    NormalUp    = 2, // ( 0.0, +1.0,  0.0)
    NormalDown  = 3, // ( 0.0, -1.0,  0.0)
    NormalBack  = 4, // ( 0.0,  0.0, +1.0)
    NormalFront = 5, // ( 0.0,  0.0, -1.0)
} Normal;

typedef enum UV
{
    UVLowerLeft  = 0, // (0.0, 0.0)
    UVLowerRight = 1, // (1.0, 0.0)
    UVUpperRight = 2, // (1.0, 1.0)
    UVUpperLeft  = 3, // (0.0, 1.0)
} UV;

// x      = [ 0: 5]
// y      = [ 6:11]
// z      = [12:17]
// voxel  = [18:24]
// normal = [25:27]
// uv     = [28:29]
typedef unsigned int Vertex;

static void AddRightFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (x+1) | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalRight << 25) | (UVLowerLeft  << 28);
    v[1] = (x+1) | ((y  ) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalRight << 25) | (UVLowerRight << 28);
    v[2] = (x+1) | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalRight << 25) | (UVUpperRight << 28);
    v[3] = (x+1) | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalRight << 25) | (UVLowerLeft  << 28);
    v[4] = (x+1) | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalRight << 25) | (UVUpperRight << 28);
    v[5] = (x+1) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalRight << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static void AddLeftFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = x | ((y  ) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVLowerLeft  << 28);
    v[1] = x | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVLowerRight << 28);
    v[2] = x | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVUpperRight << 28);
    v[3] = x | ((y  ) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVLowerLeft  << 28);
    v[4] = x | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVUpperRight << 28);
    v[5] = x | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalLeft << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static void AddUpFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (x  ) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalUp << 25) | (UVLowerLeft  << 28);
    v[1] = (x+1) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalUp << 25) | (UVLowerRight << 28);
    v[2] = (x+1) | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalUp << 25) | (UVUpperRight << 28);
    v[3] = (x  ) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalUp << 25) | (UVLowerLeft  << 28);
    v[4] = (x+1) | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalUp << 25) | (UVUpperRight << 28);
    v[5] = (x  ) | ((y+1) << 6) | ((z  ) << 12) | (voxel << 18) | (NormalUp << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static void AddDownFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (x  ) | (y << 6) | ((z  ) << 12) | (voxel << 18) | (NormalDown << 25) | (UVLowerLeft  << 28);
    v[1] = (x+1) | (y << 6) | ((z  ) << 12) | (voxel << 18) | (NormalDown << 25) | (UVLowerRight << 28);
    v[2] = (x+1) | (y << 6) | ((z+1) << 12) | (voxel << 18) | (NormalDown << 25) | (UVUpperRight << 28);
    v[3] = (x  ) | (y << 6) | ((z  ) << 12) | (voxel << 18) | (NormalDown << 25) | (UVLowerLeft  << 28);
    v[4] = (x+1) | (y << 6) | ((z+1) << 12) | (voxel << 18) | (NormalDown << 25) | (UVUpperRight << 28);
    v[5] = (x  ) | (y << 6) | ((z+1) << 12) | (voxel << 18) | (NormalDown << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static void AddBackFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (x  ) | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVLowerLeft  << 28);
    v[1] = (x+1) | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVLowerRight << 28);
    v[2] = (x+1) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVUpperRight << 28);
    v[3] = (x  ) | ((y  ) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVLowerLeft  << 28);
    v[4] = (x+1) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVUpperRight << 28);
    v[5] = (x  ) | ((y+1) << 6) | ((z+1) << 12) | (voxel << 18) | (NormalBack << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static void AddFrontFace(Vertex* vertices, GLsizei* numVertices, Voxel voxel, unsigned int x, unsigned int y, unsigned int z)
{
    Vertex* v = vertices + *numVertices;
    v[0] = (x+1) | ((y  ) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVLowerLeft  << 28);
    v[1] = (x  ) | ((y  ) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVLowerRight << 28);
    v[2] = (x  ) | ((y+1) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVUpperRight << 28);
    v[3] = (x+1) | ((y  ) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVLowerLeft  << 28);
    v[4] = (x  ) | ((y+1) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVUpperRight << 28);
    v[5] = (x+1) | ((y+1) << 6) | (z << 12) | (voxel << 18) | (NormalFront << 25) | (UVUpperLeft  << 28);
    *numVertices += 6;
}

static Voxel GenerateVoxel(int x, int y, int z)
{
    // TODO: implement terrain generation
    return VOXEL_CYAN;
}

static int GetVoxelIndex(int x, int y, int z)
{
    return CHUNK_SIZE * (CHUNK_SIZE * z + y) + x;
}

static int IsNeighbourAir(const Chunk* chunk, int x, int y, int z)
{
    // Treat out-of-bounds as air (or check neighbor chunks)
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE)
    {
        return 1;
    }
    const int voxelIndex = GetVoxelIndex(x, y, z);
    return chunk->voxels[voxelIndex] == VOXEL_AIR;
}

static void GenerateChunks()
{
    for (int worldZ = 0; worldZ < WORLD_SIZE; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE; ++worldX)
    {
        Chunk* chunk = &world.chunks[worldZ][worldY][worldX];

        for (int chunkZ = 0; chunkZ < CHUNK_SIZE; ++chunkZ)
        for (int chunkY = 0; chunkY < CHUNK_SIZE; ++chunkY)
        for (int chunkX = 0; chunkX < CHUNK_SIZE; ++chunkX)
        {
            const Voxel voxel = GenerateVoxel(chunkX, chunkY, chunkZ);
            const int voxelIndex = GetVoxelIndex(chunkX, chunkY, chunkZ);
            chunk->voxels[voxelIndex] = voxel;
        }
    }
}

static void GenerateMeshes()
{
    const GLsizei numChunks = WORLD_SIZE * WORLD_SIZE * WORLD_SIZE;
    glGenVertexArrays(numChunks, (GLuint*)world.VAOs);
    glGenBuffers(numChunks, (GLuint*)world.VBOs);

    for (int worldZ = 0; worldZ < WORLD_SIZE; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE; ++worldX)
    {
        glBindVertexArray(world.VAOs[worldZ][worldY][worldX]);
        glBindBuffer(GL_ARRAY_BUFFER, world.VBOs[worldZ][worldY][worldX]);

        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)0);

        world.isDirties[worldZ][worldY][worldX] = 1;
    }    
}

static void GenerateVertices()
{
    const int vertexPerFace = 6;
    const int facePerVoxel = 6;
    const int voxelPerChunk = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

    const int maxNumVertex = vertexPerFace * facePerVoxel * voxelPerChunk;
    Vertex vertices[maxNumVertex];

    for (int worldZ = 0; worldZ < WORLD_SIZE; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE; ++worldX)
    {
        if (world.isDirties[worldZ][worldY][worldX] == 0) { continue; }

        GLsizei numVertices = 0;
        const Chunk* chunk = &world.chunks[worldZ][worldY][worldX];

        for (int chunkZ = 0; chunkZ < CHUNK_SIZE; ++chunkZ)
        for (int chunkY = 0; chunkY < CHUNK_SIZE; ++chunkY)
        for (int chunkX = 0; chunkX < CHUNK_SIZE; ++chunkX)
        {
            const int voxelIndex = GetVoxelIndex(chunkX, chunkY, chunkZ);
            const Voxel voxel = chunk->voxels[voxelIndex];

            if (voxel == VOXEL_AIR) { continue; }

            if (IsNeighbourAir(chunk, chunkX+1, chunkY,   chunkZ  )) { AddRightFace(vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
            if (IsNeighbourAir(chunk, chunkX-1, chunkY,   chunkZ  )) { AddLeftFace (vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
            if (IsNeighbourAir(chunk, chunkX,   chunkY+1, chunkZ  )) { AddUpFace   (vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
            if (IsNeighbourAir(chunk, chunkX,   chunkY-1, chunkZ  )) { AddDownFace (vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
            if (IsNeighbourAir(chunk, chunkX,   chunkY,   chunkZ+1)) { AddBackFace (vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
            if (IsNeighbourAir(chunk, chunkX,   chunkY,   chunkZ-1)) { AddFrontFace(vertices, &numVertices, voxel, chunkX, chunkY, chunkZ); }
        }

        glBindBuffer(GL_ARRAY_BUFFER, world.VBOs[worldZ][worldY][worldX]);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        world.numVertices[worldZ][worldY][worldX] = numVertices;
        world.isDirties[worldZ][worldY][worldX] = 0;

        printf("Number of Vertices: %i\n", numVertices);
    }
}

void WorldCreate()
{
    GenerateChunks();
    GenerateMeshes();
    GenerateVertices();
}

void WorldDelete()
{
    const GLsizei numChunks = WORLD_SIZE * WORLD_SIZE * WORLD_SIZE;
    glDeleteVertexArrays(numChunks, (GLuint*)world.VAOs);
    glDeleteBuffers(numChunks, (GLuint*)world.VBOs);
}

void WorldDraw(ShaderProgram shaderProgram)
{
    for (int worldZ = 0; worldZ < WORLD_SIZE; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE; ++worldX)
    {
        vec3 chunkPosition = {worldX, worldY, worldZ};
        glm_vec3_scale(chunkPosition, CHUNK_SIZE, chunkPosition);
        ShaderProgramSetUniform3f(shaderProgram, "chunkPosition", chunkPosition);

        glBindVertexArray(world.VAOs[worldZ][worldY][worldX]);
        glDrawArrays(GL_TRIANGLES, 0, world.numVertices[worldZ][worldY][worldX]);
    }
}

