#version 450

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;

out vec4 v2f_Color;
out vec2 v2f_TexCoords;

layout (std140, binding = 0) uniform UniformsVS
{
	mat4 u_Model;
};

void main()
{
	gl_Position = u_Model * a_Position;
	
	v2f_Color = a_Color;
	v2f_TexCoords = a_TexCoords;
}