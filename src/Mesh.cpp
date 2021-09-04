#include <Mesh.h>
using namespace glm;
using namespace std;
using namespace Assimp;
Mesh::Mesh(const char *path, vec3 position) : model(translate(mat4(1.0f), position))
{
    Importer importer;
    aiMesh *mesh = importer.ReadFile(path, aiProcess_Triangulate)->mMeshes[0];
    vertices.resize(mesh->mNumVertices);
    for (unsigned i = 0; i < vertices.size();++i){
        aiVector3D temp = mesh->mVertices[i];
        vertices[i].position = vec3(temp.x, temp.y, temp.z);
        temp = mesh->mNormals[i];
        vertices[i].normal = vec3(temp.x, temp.y, temp.z);
    }
    indices.resize(mesh->mNumFaces * 3);
    for (unsigned i = 0; i < indices.size();i+=3){
        indices[i + 0] = mesh->mFaces[i / 3].mIndices[0];
        indices[i + 1] = mesh->mFaces[i / 3].mIndices[1];
        indices[i + 2] = mesh->mFaces[i / 3].mIndices[2];
    }
    importer.FreeScene();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
    assert("Failed to generate buffers" && glGetError() == 0);
}
void Mesh::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}