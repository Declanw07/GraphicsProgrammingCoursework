#version 120

attribute vec3 position;
attribute vec2 texCoordinate;

varying vec2 texCoordinate0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoordinate0 = texCoordinate;
}
