#version 330
layout(location=0) in vec3 pos_model;
layout(location=1) in vec3 nor_model;
out vec4 pos_world;
uniform mat4 model;
uniform mat4 view;
uniform mat4 persp;
void main(){
  pos_world=model*vec4(pos_model,1);
  gl_Position=persp*view*pos_world;
}