#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
	vec4 position = projection * vec4(vertex.xy, 0.0, 1.0);
	// position[0] = -1.0 + position[0]*2;
	// position[1] = 1.0 - position[1]*2;

    gl_Position = position;
    TexCoords = vertex.zw;
}  