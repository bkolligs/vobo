#shader fragment
#version 330 core

// layout of the color output
layout(location=0) out vec4 oColor;

// take in this variable data from the vertex shader
in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
 // set the color to the vertex color
 oColor = texture(uTexture, vTexCoord);
};


#shader vertex
#version 330 core

// position coordinates of vertex
layout(location=0) in vec4 iPos;
// color of each vertex
layout(location=1) in vec2 aTexCoord;

// pass color to the fragment shader
out vec4 vColor;
out vec2 vTexCoord;

// MVP matrices
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
  // outputs the positions of all vertices
  gl_Position = uProj * uView * uModel * iPos;
  // assigns the colors from vertex data to our output data going to fragment shader
  // vColor = vec4(aTexCoord, 0.0, 0.0);
  vTexCoord = aTexCoord;
};