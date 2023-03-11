#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core
out vec4 oFragColor;

void main()
{
    oFragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}