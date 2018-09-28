#version 330 core

layout (location = 0) in vec3 aPos; // aPos is attribute 0
layout (location = 1) in vec3 aCol; // aCol is attribute 1
layout (location = 2) in vec2 aTex1; // aTex1 is attribute 2
layout (location = 3) in vec2 aTex2; // aTex2 is attribute 3

uniform float time;

out vec3 colour;
out vec2 texCoord1;
out vec2 texCoord2;

void main()
{
  colour = aCol;
  texCoord1 = aTex1;
  texCoord2 = vec2( (aTex2.x-0.5) * cos(time*2) + (aTex2.y-0.5) * sin(time*2),
                    (aTex2.x-0.5) * sin(time*2) - (aTex2.y-0.5) * cos(time*2));
  gl_Position = vec4( aPos.x + cos(time)/10.,
                      aPos.y + sin(time)/10.,
                      aPos.z
                      , 1.0);
}
