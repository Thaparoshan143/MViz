#version 330 core

out vec4 FragColor;

in vec4 ourColor;

uniform vec3 fColor;

void main()
{
	// FragColor = ourColor;
	FragColor = (fColor.x !=0 )? vec4(fColor, 1.0f): ourColor;
}