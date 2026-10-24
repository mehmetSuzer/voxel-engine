
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mesh.h"
#include "buffer.h"
#include "log/log.h"
#include "glad/glad.h"
#include "graphics/graphics.h"

typedef struct Mesh
{
    VertexArrayID VAO;
    BufferID VBO;
    BufferID EBO;
    uint32_t vertexCount;
    uint32_t indexCount;
    GLenum drawMode;
    bool active;
} Mesh;

typedef struct MeshArray
{
    Mesh* data;
    uint32_t size;
    uint32_t capacity;
} MeshArray;

static MeshArray meshArray = {0};

static MeshID meshArrayPush(const Mesh* mesh)
{
    assert(mesh != NULL);

    MeshID meshID = 0;
    while (meshID < meshArray.size && meshArray.data[meshID].active) 
    { 
        meshID++;
    }

    if (meshID < meshArray.size)
    {
        memcpy(&meshArray.data[meshID], mesh, sizeof(Mesh));
        return meshID;
    }

    if (meshID < meshArray.capacity)
    {
        memcpy(&meshArray.data[meshID], mesh, sizeof(Mesh));
        meshArray.size++;
        return meshID;
    }

    const uint32_t newCapacity = (meshArray.capacity != 0) ? 2 * meshArray.capacity : 8;
    meshArray.data = (Mesh*)realloc(meshArray.data, newCapacity * sizeof(Mesh));
    meshArray.capacity = newCapacity;

    memcpy(&meshArray.data[meshID], mesh, sizeof(Mesh));
    meshArray.size++;
    return meshID;
}

MeshID meshCreate(const MeshCreateInfo* meshCreateInfo)
{
    assert(meshCreateInfo->vertexLinkAttributeFunction != NULL);
    assert(meshCreateInfo->vertices != NULL);
    assert(meshCreateInfo->indices != NULL);
    assert(meshCreateInfo->vertexCount != 0);
    assert(meshCreateInfo->indexCount != 0);
    assert(meshCreateInfo->vertexSize != 0);
    
#ifndef NDEBUG
    char* vaoLabel = NULL;
    char* vboLabel = NULL;
    char* eboLabel = NULL;

    if (meshCreateInfo->label != NULL)
    {
        const size_t maxDebugLabelLength = (size_t)graphicsGetMaxDebugLabelLength();
    
        vaoLabel = (char*)malloc(maxDebugLabelLength * sizeof(char));
        snprintf(vaoLabel, maxDebugLabelLength, "%s VAO", meshCreateInfo->label);
 
        vboLabel = (char*)malloc(maxDebugLabelLength * sizeof(char));
        snprintf(vboLabel, maxDebugLabelLength, "%s VBO", meshCreateInfo->label);

        eboLabel = (char*)malloc(maxDebugLabelLength * sizeof(char));
        snprintf(eboLabel, maxDebugLabelLength, "%s EBO", meshCreateInfo->label);
    }
#endif

    BufferCreateInfo vboCreateInfo = {0};
#ifndef NDEBUG
    vboCreateInfo.label = vboLabel;
#endif
    vboCreateInfo.data = meshCreateInfo->vertices;
    vboCreateInfo.size = meshCreateInfo->vertexCount * meshCreateInfo->vertexSize;
    vboCreateInfo.bufferStorageBits = BufferStorageBitNone;

    BufferCreateInfo eboCreateInfo = {0};
#ifndef NDEBUG
    eboCreateInfo.label = eboLabel;
#endif
    eboCreateInfo.data = meshCreateInfo->indices;
    eboCreateInfo.size = meshCreateInfo->indexCount * sizeof(uint32_t);
    eboCreateInfo.bufferStorageBits = BufferStorageBitNone;

    Mesh mesh = {0};
#ifndef NDEBUG
    mesh.VAO = vertexArrayCreate(vaoLabel);
#else
    mesh.VAO = vertexArrayCreate();
#endif
    mesh.VBO = bufferCreate(&vboCreateInfo);
    mesh.EBO = bufferCreate(&eboCreateInfo);

#ifndef NDEBUG
    free(vaoLabel);
    free(vboLabel);
    free(eboLabel);
#endif

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, meshCreateInfo->vertexSize);
    vertexArraySetElementBuffer(mesh.VAO, mesh.EBO);
    meshCreateInfo->vertexLinkAttributeFunction(mesh.VAO);

    mesh.drawMode = drawModeToNative(meshCreateInfo->drawMode);
    mesh.vertexCount = meshCreateInfo->vertexCount;
    mesh.indexCount = meshCreateInfo->indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
    logVerbose("MESH", "created: %i", meshID);

    return meshID;
}

void meshDestroy(MeshID meshID)
{
    assert(meshID < meshArray.size);
    Mesh* mesh = &meshArray.data[meshID];
    if (mesh->active)
    {
        vertexArrayDestroy(mesh->VAO);
        bufferDestroy(mesh->VBO);
        bufferDestroy(mesh->EBO);
        *mesh = (Mesh){0};
    }
}

void meshDestroyAll()
{
    for (uint32_t i = 0; i < meshArray.size; ++i)
    {
        const Mesh* mesh = &meshArray.data[i];
        if (mesh->active)
        {
            vertexArrayDestroy(mesh->VAO);
            bufferDestroy(mesh->VBO);
            bufferDestroy(mesh->EBO);
        }
    }

    free(meshArray.data);
    meshArray.size = 0;
    meshArray.capacity = 0;
}

bool meshIsActive(MeshID meshID)
{
    return (meshID < meshArray.size && meshArray.data[meshID].active);
}

void meshDraw(MeshID meshID)
{
    assert(meshID < meshArray.size);
    const Mesh* mesh = &meshArray.data[meshID];
    vertexArrayBind(mesh->VAO);
    glDrawElements(mesh->drawMode, mesh->indexCount, GL_UNSIGNED_INT, NULL);
}

