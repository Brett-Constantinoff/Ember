#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 oTexCoords;

uniform mat4 uProj;
uniform mat4 uView;

void main() 
{
    oTexCoords = aPos;
    vec4 pos = uProj * uView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core
out vec4 oFragColor;

in vec3 oTexCoords;

uniform samplerCube uSkybox;

void main() 
{
    oFragColor = texture(uSkybox, oTexCoords);
}