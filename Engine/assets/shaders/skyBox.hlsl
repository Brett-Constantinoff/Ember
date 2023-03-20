#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    TexCoords = aPos;
    vec4 pos = uProjection * uView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

#shader fragmentShader
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube uSkybox;

void main() {
    FragColor = texture(uSkybox, TexCoords);
}