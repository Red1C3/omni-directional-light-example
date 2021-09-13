#include <Renderer.h>
using namespace glm;
using namespace std;
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
    glGenTextures(1, &cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
    for (unsigned i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH24_STENCIL8,
                     SHADOWMAP, SHADOWMAP, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glGenFramebuffers(1, &framebuffers[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubeMap, 0);
        assert(glGetError() == 0);
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
    mainShader = Shader("./Assets/main.vert", "./Assets/main.frag");
    glUseProgram(mainShader.id);
    mainShader.registerUniform("model");
    mainShader.registerUniform("view");
    mainShader.registerUniform("persp");
    mainShader.updateUniform("persp", perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f));
    mainShader.updateUniform("view", lookAt(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0)));
    Mesh cubeA("./Assets/Cube.glb", vec3(-5, 0, 0));
    Mesh verticalPlane("./Assets/Vertical Plane.glb", vec3(-7, 0, 0));
    meshes.push_back(cubeA);
    meshes.push_back(verticalPlane);
    assert("Failed to init" && glGetError() == 0);
}
void Renderer::renderPass()
{
    glViewport(0, 0, SHADOWMAP, SHADOWMAP);
    for (unsigned i = 0; i < 6; ++i)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(lightShader.id);
        lightShader.updateUniform("view", lookAt(vec3(0, 0, 0), axis[i], vec3(0, 1, 0)));
        for (unsigned j = 0; j < meshes.size(); ++j)
        {
            lightShader.updateUniform("model", meshes[j].model);
            meshes[j].draw();
        }
    }
    glViewport(0, 0, 1280, 720);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(mainShader.id);
    for (unsigned i = 0; i < meshes.size(); ++i)
    {
        mainShader.updateUniform("model", meshes[i].model);
        meshes[i].draw();
    }
    assert("Error in renderPass" && glGetError() == 0);
}