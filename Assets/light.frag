#version 330
in vec4 pos_world;
void main(){
  //calculate depth by distance
  vec3 lightPos=vec3(0,0,0);
  float farPlane=100.0f;
  float dist=length(pos_world.xyz-lightPos);
  dist/=farPlane;
  gl_FragDepth=dist;
}