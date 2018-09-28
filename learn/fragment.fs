#version 330 core

in vec3 colour;
in vec2 texCoord1;
in vec2 texCoord2;
out vec4 FragColor;

uniform float time;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
  FragColor = mix(texture(ourTexture1, texCoord1),
                  texture(ourTexture2, texCoord2),
                  0.5 + sin(time)/2.) *
                  vec4(colour.x * cos(time),
                       colour.y * sin(time),
                       colour.z * cos(time*2. + 0.2),
                       1.0f);
}
