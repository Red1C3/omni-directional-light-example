#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <vector>
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};
class Mesh
{

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    GLuint VAO, VBO, EBO;

public:
    Mesh(const char *path, glm::vec3 position);
    glm::mat4 model;
    void draw();
};