#version 330
out vec4 color;
in vec4 pos_world;
uniform samplerCube depthMap;
void main(){
  vec3 lightPos=vec3(0,0,0);
  float farPlane=100.0f;
  vec3 lightDir=pos_world.xyz-lightPos;
  float closestDepth=texture(depthMap,lightDir).r;
  float currentDepth=length(lightDir)/farPlane;
  if(closestDepth<currentDepth-0.0002){
    color=vec4(0,0,0,1);
  }else{
    color=vec4(1,1,1,1);
  }
}