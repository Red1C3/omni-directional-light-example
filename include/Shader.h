#pragma once
#include <GL/glew.h>
#include <helpers.h>
#include<map>
#include<glm/glm.hpp>
class Shader
{
private:
    std::map<std::string, GLint> uniforms;

public:
    Shader();
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    GLuint id;
    void registerUniform(const char* uniform);
    void updateUniform(const char *uniform, glm::mat4 matrix);
};