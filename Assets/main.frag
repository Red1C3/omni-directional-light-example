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
#version 330
out vec4 color;
in vec4 pos_world;
uniform samplerCube depthMap;
void main(){
  vec3 lightPos=vec3(0,0,0);
  float farPlane=100.0f;
  vec3 lightDir=pos_world.xyz-lightPos;
  float closestDepth=texture(depthMap,lightDir).r;
  //calculate depth by distance and compare it with sampled value
  float currentDepth=length(lightDir)/farPlane;
  if(closestDepth<currentDepth-0.0002){
    color=vec4(0,0,0,1);
  }else{
    color=vec4(1,1,1,1);
  }
}