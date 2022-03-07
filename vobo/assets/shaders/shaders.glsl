#shader fragment
#version 330 core

// layout of the color output
layout(location=0) out vec4 oColor;

// take in this variable data from the vertex shader
in vec4 vColor;

// uniform to specify color coming from the CPU
uniform vec4 uColor;

void main()
{
 // set the color to the vertex color
 oColor = vColor;
};


#shader vertex
#version 330 core

// position coordinates of vertex
layout(location=0) in vec4 iPos;
// color of each vertex
layout(location=1) in vec4 iColor;

// pass color to the fragment shader
out vec4 vColor;

// controls the scale of the vertices
uniform float uScale;

// MVP matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
  // outputs the positions of all vertices
  gl_Position = uProj * uView * uModel * iPos;
  // assigns the colors from vertex data to our output data going to fragment shader
  vColor = iColor;
};