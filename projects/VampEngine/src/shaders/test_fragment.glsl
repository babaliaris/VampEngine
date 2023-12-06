#version 330
out vec4 m_color;

in vec2 texCoord;

void main()
{
    m_color = vec4(texCoord, 0.0, 1.0);
}