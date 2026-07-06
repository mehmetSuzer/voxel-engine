
#include <string.h>
#include "mesh.h"
#include "buffer.h"
#include "log/log.h"
#include "glad/glad.h"
#include "vertex_array.h"

typedef struct Mesh
{
    VertexArrayID VAO;
    BufferID VBO;
    BufferID EBO;
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

MeshID meshCreatePBR(const VertexPBR* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    Mesh mesh;
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(vertexCount * sizeof(VertexPBR), vertices, (BufferStorageBit)0);
    mesh.EBO = bufferCreate(indexCount * sizeof(uint32_t), indices, (BufferStorageBit)0);

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, sizeof(VertexPBR));
    vertexArraySetElementBuffer(mesh.VAO, mesh.EBO);

    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 0, 3, offsetof(VertexPBR, position));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 1, 3, offsetof(VertexPBR, normal));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 2, 3, offsetof(VertexPBR, tangent));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 3, 2, offsetof(VertexPBR, texCoord));

    mesh.drawMode = drawModeToNative(drawMode);
    mesh.indexCount = indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

MeshID meshCreateVoxel(const VertexVoxel* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    Mesh mesh;
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(vertexCount * sizeof(VertexVoxel), vertices, (BufferStorageBit)0);
    mesh.EBO = bufferCreate(indexCount * sizeof(uint32_t), indices, (BufferStorageBit)0);

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, sizeof(VertexVoxel));
    vertexArraySetElementBuffer(mesh.VBO, mesh.EBO);

    vertexArrayLinkAttributeUint(mesh.VAO, 0, 0, 1, 0);

    mesh.drawMode = drawModeToNative(drawMode);
    mesh.indexCount = indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

void meshDestroy(MeshID meshID)
{
    Mesh* mesh = &meshArray.data[meshID];
    vertexArrayDestroy(mesh->VAO);
    bufferDestroy(mesh->VBO);
    bufferDestroy(mesh->EBO);
    *mesh = (Mesh){0};
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
    const Mesh* mesh = &meshArray.data[meshID];
    vertexArrayBind(mesh->VAO);
    glDrawElements(mesh->drawMode, mesh->indexCount, GL_UNSIGNED_INT, NULL);
    logVerbose("MESH", "drawn: %u", meshID);
}

