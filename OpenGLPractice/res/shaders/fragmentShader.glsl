#version 150

uniform sampler2D sampler;
varying vec2 texCoord0;

void main()
{
	if (texCoord0.x >= 0 && texCoord0.y >= 0)
    	gl_FragColor = texture2D(sampler, texCoord0);
    else
    	gl_FragColor = vec4(0.0, 0.5, 0.0, 1.0);
}