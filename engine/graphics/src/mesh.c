
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

MeshID meshCreateStatic(const VertexStatic* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    assert(vertices != NULL && vertexCount != 0);
    assert(indices != NULL && indexCount != 0);

    Mesh mesh = {0};
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(vertexCount * sizeof(VertexStatic), vertices, BufferStorageBitNone);
    mesh.EBO = bufferCreate(indexCount * sizeof(uint32_t), indices, BufferStorageBitNone);

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, sizeof(VertexStatic));
    vertexArraySetElementBuffer(mesh.VAO, mesh.EBO);

    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 0, 3, offsetof(VertexStatic, position));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 1, 3, offsetof(VertexStatic, normal));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 2, 3, offsetof(VertexStatic, tangent));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 3, 2, offsetof(VertexStatic, texture));

    mesh.drawMode = drawModeToNative(drawMode);
    mesh.vertexCount = vertexCount;
    mesh.indexCount = indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

MeshID meshCreateStaticPacked(const VertexStaticPacked* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    assert(vertices != NULL && vertexCount != 0);
    assert(indices != NULL && indexCount != 0);

    Mesh mesh = {0};
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(vertexCount * sizeof(VertexStaticPacked), vertices, BufferStorageBitNone);
    mesh.EBO = bufferCreate(indexCount * sizeof(uint32_t), indices, BufferStorageBitNone);

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, sizeof(VertexStaticPacked));
    vertexArraySetElementBuffer(mesh.VAO, mesh.EBO);

    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 0, 3, offsetof(VertexStaticPacked, positionXYZ));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 1, 2, offsetof(VertexStaticPacked, normalXY));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 2, 2, offsetof(VertexStaticPacked, tangentXY));
    vertexArrayLinkAttributeFloat(mesh.VAO, 0, 3, 2, offsetof(VertexStaticPacked, textureUV));

    mesh.drawMode = drawModeToNative(drawMode);
    mesh.vertexCount = vertexCount;
    mesh.indexCount = indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

MeshID meshCreateVoxel(const VertexVoxel* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    assert(vertices != NULL && vertexCount != 0);
    assert(indices != NULL && indexCount != 0);

    Mesh mesh = {0};
    mesh.VAO = vertexArrayCreate();
    mesh.VBO = bufferCreate(vertexCount * sizeof(VertexVoxel), vertices, BufferStorageBitNone);
    mesh.EBO = bufferCreate(indexCount * sizeof(uint32_t), indices, BufferStorageBitNone);

    vertexArraySetVertexBuffer(mesh.VAO, 0, mesh.VBO, 0, sizeof(VertexVoxel));
    vertexArraySetElementBuffer(mesh.VBO, mesh.EBO);

    vertexArrayLinkAttributeUint(mesh.VAO, 0, 0, 1, 0);

    mesh.drawMode = drawModeToNative(drawMode);
    mesh.vertexCount = vertexCount;
    mesh.indexCount = indexCount;
    mesh.active = true;

    const MeshID meshID = meshArrayPush(&mesh);
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
    logVerbose("MESH", "drawn: %u", meshID);
}

