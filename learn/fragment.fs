#version 330 core

in vec3 colour;
in vec2 tex;
out vec4 FragColor;

uniform float time;
uniform sampler2D ourTexture;

void main()
{
  /*FragColor = vec4(colour.x * cos(time),
                   colour.y * sin(time),
                   colour.z * cos(time*2. + 0.2),
                   1.0f);*/
  FragColor = texture(ourTexture, tex);
}
