#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aCol;

out vec4 ourColor;

void main()
{
	// if(modal[0].x!=0 && modal[3].x!=0 )
	// {
	// 	gl_Position = modal * aPos;
	// }
	// else
	// {
	// 	gl_Position = aPos;
	// }
		gl_Position = aPos;
	ourColor = aCol;
}