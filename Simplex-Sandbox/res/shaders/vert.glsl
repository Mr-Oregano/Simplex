#version 460

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_ColorIndex;

out vec4 v2f_Color;
flat out int v2f_ColorIndex;

void main()
{
	vec4 offset = (gl_InstanceID - 1) * vec4(0.65, 0.0, 0.0, 0.0);
	gl_Position = a_Position + offset;
	
	v2f_Color = a_Color;
	v2f_ColorIndex = a_ColorIndex;
}