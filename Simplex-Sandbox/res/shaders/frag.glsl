#version 460

layout(location = 0) out vec4 o_Color;

in vec4 v2f_Color;
flat in int v2f_ColorIndex;

uniform vec4 colors[3] = {
	vec4(1.0, 0.5, 0.5, 1.0),
	vec4(0.5, 1.0, 0.5, 1.0),
	vec4(0.5, 0.5, 1.0, 1.0)
};

void main()
{
	o_Color = colors[v2f_ColorIndex % 3];
}