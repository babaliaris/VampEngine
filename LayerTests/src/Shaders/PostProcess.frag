#version 330 core
in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D u_Diffuse;

void main()
{
	fragColor = texture(u_Diffuse, textCoord) * vec4(0.0, 0.8, 0.0, 1.0);
}