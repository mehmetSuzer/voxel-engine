
#include <string.h>
#include "mesh.h"
#include "error.h"
#include "log/log.h"
#include "glad/glad.h"

typedef struct Mesh
{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei indexCount;
    DrawMode drawMode;
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
    mesh.active = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VertexPBR), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    vertexPBRLinkAttributes();
    glBindVertexArray(0);
    glCheckErrors();

    mesh.drawMode = drawMode;
    mesh.indexCount = indexCount;
    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

MeshID meshCreateVoxel(const VertexVoxel* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount, DrawMode drawMode)
{
    Mesh mesh;
    mesh.active = true;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VertexVoxel), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    vertexVoxelLinkAttributes();
    glBindVertexArray(0);
    glCheckErrors();

    mesh.drawMode = drawMode;
    mesh.indexCount = indexCount;
    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

void meshDestroy(MeshID meshID)
{
    Mesh* mesh = &meshArray.data[meshID];
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    glCheckErrors();
    *mesh = (Mesh){0};
}

void meshDestroyAll()
{
    for (uint32_t i = 0; i < meshArray.size; ++i)
    {
        const Mesh* mesh = &meshArray.data[i];
        if (mesh->active)
        {
            glDeleteVertexArrays(1, &mesh->VAO);
            glDeleteBuffers(1, &mesh->VBO);
            glDeleteBuffers(1, &mesh->EBO);
            glCheckErrors();
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
    glBindVertexArray(mesh->VAO);
    glDrawElements(drawModeToNative(mesh->drawMode), mesh->indexCount, GL_UNSIGNED_INT, NULL);
    logVerbose("MESH", "drawn: %u", meshID);
    glCheckErrors();
}

