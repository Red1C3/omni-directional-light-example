#include <Renderer.h>
using namespace glm;
#define SHADOWMAP 1024
Renderer::Renderer()
{
}
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
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex[i], 0);
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }
    axis.push_back(vec3(1, 0, 0));
    axis.push_back(vec3(-1, 0, 0));
    axis.push_back(vec3(0, 1, 0));
    axis.push_back(vec3(0, -1, 0));
    axis.push_back(vec3(0, 0, 1));
    axis.push_back(vec3(0, 0, -1));
    lightShader = Shader("./Assets/light.vert", "./Assets/light.frag");
    glUseProgram(lightShader.id);
    lightShader.registerUniform("model");
    lightShader.registerUniform("view");
    lightShader.registerUniform("persp");
    lightShader.updateUniform("persp", perspective(45.0f, 1.0f, 0.1f, 100.0f));
    Mesh cubeA("./Assets/Cube.glb", vec3(3, 0, 0));
    Mesh verticalPlane("./Assets/Vertical Plane.glb", vec3(5, 0, 0));
    meshes.push_back(cubeA);
    meshes.push_back(verticalPlane);
    assert("Failed to init" && glGetError() == 0);
}
void Renderer::renderPass()
{
    for (unsigned i = 0; i < 6; ++i)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(lightShader.id);
        lightShader.updateUniform("view", lookAt(vec3(0, 0, 0), axis[i], vec3(0, 1, 0)));
        for (unsigned j = 0; j < meshes.size();++j){
            lightShader.updateUniform("model", meshes[j].model);
            meshes[j].draw();
        }
    }
    assert("Error in renderPass" && glGetError() == 0);
}