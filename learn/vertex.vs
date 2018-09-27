#version 330 core

layout (location = 0) in vec3 aPos; // aPos is attribute 0
layout (location = 1) in vec3 aCol; // aCol is attribute 1
layout (location = 2) in vec2 aTex; // aTex is attribute 2

uniform float time;

out vec3 colour;
out vec2 tex;

void main()
{
  colour = aCol;
  tex = aTex;
  gl_Position = vec4( aPos.x + cos(time)/10.,
                      aPos.y + sin(time)/10.,
                      aPos.z
                      , 1.0);
}
