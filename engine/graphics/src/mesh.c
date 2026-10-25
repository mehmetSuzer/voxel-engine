
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mesh.h"
#include "buffer.h"
#include "log/log.h"
#include "glad/glad.h"

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
    
    Mesh mesh = {0};
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(meshCreateInfo->vertexCount * meshCreateInfo->vertexSize, meshCreateInfo->vertices, BufferStorageBitNone);
    mesh.EBO = bufferCreate(meshCreateInfo->indexCount * sizeof(uint32_t), meshCreateInfo->indices, BufferStorageBitNone);

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

#ifndef NDEBUG
void meshSetLabel(MeshID meshID, const char* label)
{
    const Mesh* mesh = &meshArray.data[meshID];
   
    char* vaoLabel = NULL;
    char* vboLabel = NULL;
    char* eboLabel = NULL;
 
    if (label != NULL)
    {
        const size_t maxLabelLength = 256;

        vaoLabel = (char*)malloc(maxLabelLength * sizeof(char));
        snprintf(vaoLabel, maxLabelLength, "%s VAO", label);
        vboLabel = (char*)malloc(maxLabelLength * sizeof(char));
        snprintf(vboLabel, maxLabelLength, "%s VBO", label);
        eboLabel = (char*)malloc(maxLabelLength * sizeof(char));
        snprintf(eboLabel, maxLabelLength, "%s EBO", label);    
    }

    vertexArraySetLabel(mesh->VAO, vaoLabel);
    bufferSetLabel(mesh->VBO, vboLabel);
    bufferSetLabel(mesh->EBO, eboLabel);

    if (label != NULL)
    {
        free(vaoLabel);
        free(vboLabel);
        free(eboLabel);
    }
}
#endif

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

