#version 120

varying vec2 texCoordinate0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoordinate0);
}
