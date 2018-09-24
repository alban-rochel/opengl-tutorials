#version 330 core

layout (location = 0) in vec3 aPos; // aPos is attribute 0
layout (location = 1) in vec3 aCol; // aPos is attribute 0

out vec3 colour;

void main()
{
  colour = aCol;
  gl_Position = vec4(aPos, 1.0);
}
