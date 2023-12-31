#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aCol;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 ourColor;

void main()
{
	color = vec4(ourColor,1);
}