#include<Renderer.h>
Renderer::Renderer(){}
Renderer& Renderer::instance(){
    static Renderer renderer;
    return renderer;
}
void Renderer::init(){
    glewExperimental = true;
    if(glewInit()!=GLEW_OK)
        assert("Failed to init glew" && 0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    assert("Failed to init" && glGetError() == 0);
}