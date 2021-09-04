#include <Renderer.h>
using namespace glm;
#define SHADOWMAP 1024
Renderer::Renderer() {}
Renderer &Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}
void Renderer::init()
{
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        assert("Failed to init glew" && 0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    for (unsigned i = 0; i < 6; ++i)
    {
        glGenTextures(1, &depthTex[i]);
        glBindTexture(GL_TEXTURE_2D, depthTex[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, SHADOWMAP, SHADOWMAP, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glGenFramebuffers(1, &framebuffers[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthTex[i],0);
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }
    Mesh cubeA("./Assets/Cube.glb", vec3(0, 0, 0));
    meshes.push_back(cubeA);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));
    assert("Failed to init" && glGetError() == 0);
    //TODO shaders
}
void Renderer::renderPass(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assert("Error in renderPass" && glGetError() == 0);
}