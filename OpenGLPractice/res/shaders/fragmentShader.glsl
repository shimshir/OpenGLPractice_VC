#version 150

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;
uniform int useLighting = 1;

void main()
{
	if (useLighting == 1)
    	gl_FragColor = texture2D(sampler, texCoord0) * clamp(dot(normalize(-lightDirection), normal0), 0.05, 1.0);
    else
    	gl_FragColor = texture2D(sampler, texCoord0);
}
// * clamp(dot(-lightDirection, normal0), 0.0, 1.0)