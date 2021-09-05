#version 330
layout(location=0) in vec3 pos_model;
layout(location=1) in vec3 nor_model;
uniform mat4 model;
uniform mat4 view;
uniform mat4 persp;
void main(){
  gl_Position=persp*view*model*vec4(pos_model,1);
}