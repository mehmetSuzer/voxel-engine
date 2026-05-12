
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
    int active;
} Mesh;

typedef struct MeshArray
{
    Mesh* data;
    unsigned int size;
    unsigned int capacity;
} MeshArray;

static MeshArray meshArray = {0};

static MeshID meshArrayPush(const Mesh* mesh)
{
    MeshID meshID = 0u;
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

    const unsigned int newCapacity = (meshArray.capacity != 0u) ? 2u * meshArray.capacity : 8u;
    meshArray.data = (Mesh*)realloc(meshArray.data, newCapacity * sizeof(Mesh));
    meshArray.capacity = newCapacity;

    memcpy(&meshArray.data[meshID], mesh, sizeof(Mesh));
    meshArray.size++;
    return meshID;
}

MeshID meshCreatePBR(const VertexPBR* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode)
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vertexPBRLinkAttributes();
    glBindVertexArray(0);

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

MeshID meshCreateVoxel(const VertexVoxel* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode)
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vertexVoxelLinkAttributes();
    glBindVertexArray(0);

    const MeshID meshID = meshArrayPush(&mesh);
    return meshID;
}

void meshDestroy(MeshID meshID)
{
    Mesh* mesh = &meshArray.data[meshID];
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    *mesh = (Mesh){0};
}

void meshDestroyAll()
{
    for (unsigned int i = 0u; i < meshArray.size; ++i)
    {
        const Mesh* mesh = &meshArray.data[i];
        if (mesh->active)
        {
            glDeleteVertexArrays(1, &mesh->VAO);
            glDeleteBuffers(1, &mesh->VBO);
            glDeleteBuffers(1, &mesh->EBO);
        }
    }

    free(meshArray.data);
    meshArray.size = 0u;
    meshArray.capacity = 0u;
}

int meshIsActive(MeshID meshID)
{
    return (meshID < meshArray.size && meshArray.data[meshID].active);
}

void meshDraw(MeshID meshID)
{
    const Mesh* mesh = &meshArray.data[meshID];
    glBindVertexArray(mesh->VAO);
    glDrawElements(mesh->drawMode, mesh->indexCount, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

