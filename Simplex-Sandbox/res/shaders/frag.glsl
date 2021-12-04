#version 450

layout(location = 0) out vec4 o_Color;

in vec4 v2f_Color;
in vec2 v2f_TexCoords;

uniform sampler2D u_Texture;

// Dummy UBO here for testing.
//
layout (std140, binding = 0) uniform DummyThiccUniforms
{
	vec2 something;
};

layout (std140, binding = 1) uniform UniformsFS
{
	vec4 u_Tint;
};

void main()
{
	o_Color = texture(u_Texture, v2f_TexCoords) * u_Tint;
}