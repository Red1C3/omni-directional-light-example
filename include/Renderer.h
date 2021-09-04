#pragma once
#include <GL/glew.h>
#include <assert.h>
#include <Mesh.h>
#include <Shader.h>
class Renderer
{
private:
    Renderer();
    GLuint depthTex[6];
    GLuint framebuffers[6];
    std::vector<Mesh> meshes;

public:
    static Renderer &instance();
    void init();
    void renderPass();
};