#version 450

layout(location = 0) out vec4 o_Color;

in vec4 v2f_Color;
in vec2 v2f_TexCoords;

uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, v2f_TexCoords);
}