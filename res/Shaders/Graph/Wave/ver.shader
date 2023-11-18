#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 modal;

void main()
{
	gl_Position = modal * aPos;
}