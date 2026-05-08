
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
} Mesh;

static Mesh* meshes = NULL;
static unsigned int meshCount = 0u;

MeshID meshCreate(const Vertex* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int indexCount, DrawMode drawMode)
{
    Mesh mesh;
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vertexLinkAttributes();
    glBindVertexArray(0);

    const MeshID meshID = meshCount;
    const unsigned int newMeshCount = meshCount + 1u;
    meshes = (Mesh*)realloc(meshes, newMeshCount * sizeof(Mesh));
    meshes[meshCount] = mesh;
    meshCount = newMeshCount;

    return meshID;
}

void meshDestroy(MeshID meshID)
{
    const unsigned int newMeshCount = meshCount - 1u;
    if (newMeshCount == 0u)
    {
        free(meshes);
        meshes = NULL;
        meshCount = 0u;
    }
    else
    {
        Mesh* mesh = &meshes[meshID];
        glDeleteVertexArrays(1, &mesh->VAO);
        glDeleteBuffers(1, &mesh->VBO);
        glDeleteBuffers(1, &mesh->EBO);
        *mesh = meshes[meshCount];

        meshes = (Mesh*)realloc(meshes, newMeshCount * sizeof(Mesh));
        meshCount = newMeshCount;
    }
}

void meshDraw(MeshID meshID)
{
    const Mesh* mesh = &meshes[meshID];
    glBindVertexArray(mesh->VAO);
    glDrawElements(mesh->drawMode, mesh->indexCount, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

