#version 150

in vec3 position;
in vec2 texCoord;
in vec3 normal;

varying vec2 texCoord0;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
    gl_Position = projection * transform * vec4(position, 1.0);
    texCoord0 = texCoord;
}