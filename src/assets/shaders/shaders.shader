#shader fragment
#version 330 core

layout(location=0) out vec4 oColor;

in vec4 vColor;

uniform vec4 uColor;

void main()
{
 oColor = vColor;
};

#shader vertex
#version 330 core

layout(location=0) in vec4 iPos;
layout(location=1) in vec4 iColor;

out vec4 vColor;

void main()
{
  gl_Position = iPos;
  vColor = iColor;
};