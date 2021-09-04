#pragma once
#include<GL/glew.h>
#include<assert.h>
class Renderer
{
private:
    Renderer();

public:
    static Renderer &instance();
    void init();
};