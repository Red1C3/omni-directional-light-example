/*
MIT License

Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <Shader.h>
using namespace std;
using namespace glm;
Shader::Shader(){}
Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    auto vertexShaderCode = readBin(vertexShaderPath);
    auto fragmentShaderCode = readBin(fragmentShaderPath);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto data = vertexShaderCode.data();
    GLint size = vertexShaderCode.size();
    int result;
    glShaderSource(vertexShader, 1, &data, &size);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    assert(result != GL_FALSE);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    data = fragmentShaderCode.data();
    size = fragmentShaderCode.size();
    glShaderSource(fragmentShader, 1, &data, &size);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    assert(result != GL_FALSE);
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    assert(result != GL_FALSE);
    glDetachShader(id, vertexShader);
    glDetachShader(id, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    assert("Failed to compile shader" && glGetError() == 0);
}
void Shader::registerUniform(const char *uniform)
{
    GLint address = glGetUniformLocation(id, uniform);
    uniforms.insert({string(uniform), address});
    assert("Failed to register uniform" && glGetError() == 0);
}
void Shader::updateUniform(const char *uniform, mat4 matrix)
{
    glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, &matrix[0][0]);
    assert("Failed to update uniform" && glGetError() == 0);
}