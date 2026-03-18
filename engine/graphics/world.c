
#include <stb_image.h>
#include "world.h"

#define CHUNK_SIZE 32

#define WORLD_SIZE_X 16
#define WORLD_SIZE_Y 1
#define WORLD_SIZE_Z 16

typedef struct Chunk
{
    Voxel voxels[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
} Chunk;

typedef struct World
{
    Chunk chunks[WORLD_SIZE_Z][WORLD_SIZE_Y][WORLD_SIZE_X];         // [Z][Y][X]
    GLuint VAOs[WORLD_SIZE_Z][WORLD_SIZE_Y][WORLD_SIZE_X];          // [Z][Y][X]
    GLuint VBOs[WORLD_SIZE_Z][WORLD_SIZE_Y][WORLD_SIZE_X];          // [Z][Y][X]
    GLsizei numVertices[WORLD_SIZE_Z][WORLD_SIZE_Y][WORLD_SIZE_X];  // [Z][Y][X]
    int isDirties[WORLD_SIZE_Z][WORLD_SIZE_Y][WORLD_SIZE_X];        // [Z][Y][X]
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
    return chunk->voxels[voxelIndex] == VoxelAir;
}

static void GenerateChunks()
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pixels = stbi_load("textures/perlin.png", &width, &height, &channels, 0);

    if (pixels == NULL)
    {
        printf("Failed to load the perlin noise.\n");
        exit(EXIT_FAILURE);
    }

    if (channels < 1 || channels > 4)
    {
        stbi_image_free(pixels);
        printf("Unsupported channel count %i for the perlin noise.\n", channels);
        exit(EXIT_FAILURE);
    } 

    const float maxHeight = 30.0f;

    for (int worldZ = 0; worldZ < WORLD_SIZE_Z; ++worldZ)
    for (int worldX = 0; worldX < WORLD_SIZE_X; ++worldX)
    {
        for (int chunkZ = 0; chunkZ < CHUNK_SIZE; ++chunkZ)
        for (int chunkX = 0; chunkX < CHUNK_SIZE; ++chunkX)
        {
            const int u = ((worldX * CHUNK_SIZE + chunkX) % width + width) % width;
            const int v = ((worldZ * CHUNK_SIZE + chunkZ) % height + height) % height;
            const float noise = pixels[(width * v + u) * channels] / 255.0f;
            const int height = (int)(noise * maxHeight);

            for (int worldY = 0; worldY < WORLD_SIZE_Y; ++worldY)
            {
                Chunk* chunk = &world.chunks[worldZ][worldY][worldX];
                for (int chunkY = 0; chunkY < CHUNK_SIZE; ++chunkY)
                {
                    const int y = worldY * CHUNK_SIZE + chunkY;
                    const Voxel voxel =
                        (y > height)   ? VoxelAir   :
                        (y == height)  ? VoxelGrass :
                        (y > height-3) ? VoxelDirt  : VoxelStone;

                    const int voxelIndex = GetVoxelIndex(chunkX, chunkY, chunkZ);
                    chunk->voxels[voxelIndex] = voxel;
                }
            }
        }
    }
    stbi_image_free(pixels);
}

static void GenerateMeshes()
{
    const GLsizei numChunks = WORLD_SIZE_Z * WORLD_SIZE_Y * WORLD_SIZE_X;
    glGenVertexArrays(numChunks, (GLuint*)world.VAOs);
    glGenBuffers(numChunks, (GLuint*)world.VBOs);

    for (int worldZ = 0; worldZ < WORLD_SIZE_Z; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE_Y; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE_X; ++worldX)
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

    for (int worldZ = 0; worldZ < WORLD_SIZE_Z; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE_Y; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE_X; ++worldX)
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

            if (voxel == VoxelAir) { continue; }

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
    const GLsizei numChunks = WORLD_SIZE_Z * WORLD_SIZE_Y * WORLD_SIZE_X;
    glDeleteVertexArrays(numChunks, (GLuint*)world.VAOs);
    glDeleteBuffers(numChunks, (GLuint*)world.VBOs);
}

void WorldDraw(ShaderProgram shaderProgram)
{
    for (int worldZ = 0; worldZ < WORLD_SIZE_Z; ++worldZ)
    for (int worldY = 0; worldY < WORLD_SIZE_Y; ++worldY)
    for (int worldX = 0; worldX < WORLD_SIZE_X; ++worldX)
    {
        vec3 chunkPosition = {worldX, worldY, worldZ};
        glm_vec3_scale(chunkPosition, CHUNK_SIZE, chunkPosition);
        ShaderProgramSetUniform3f(shaderProgram, "chunkPosition", chunkPosition);

        glBindVertexArray(world.VAOs[worldZ][worldY][worldX]);
        glDrawArrays(GL_TRIANGLES, 0, world.numVertices[worldZ][worldY][worldX]);
    }
}

