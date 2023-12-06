#version 330
layout(location=0) in vec3 m_pos;
layout(location=1) in vec2 m_texCoord;

out vec2 texCoord;

void main()
{
    texCoord    = m_texCoord;
    gl_Position = vec4(m_pos, 1.0);
}