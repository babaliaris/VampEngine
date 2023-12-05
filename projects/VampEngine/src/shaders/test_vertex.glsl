#version 330
layout(location=0) in vec3 m_pos;

void main()
{
    gl_Position = vec4(m_pos, 1.0);
}