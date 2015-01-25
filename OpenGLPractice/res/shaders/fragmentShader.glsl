#version 150

uniform sampler2D sampler;
varying vec2 texCoord0;

void main()
{
    gl_FragColor = texture2D(sampler, texCoord0);
}