#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oNorm;
out vec3 oFragPos;
out vec2 oUv;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    oNorm = mat3(transpose(inverse(model))) * aNorm;
    oFragPos = vec3(model * vec4(aPos, 1.0));
    oUv = aUv;
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core
in vec3 oNorm;
in vec3 oFragPos;
in vec2 oUv;

uniform vec3 uViewPos;
uniform vec3 uDiffuse;

uniform int uDiffTextureExists;
uniform sampler2D uDiffTexture;

out vec4 oFragColor;

void main()
{
    vec3 lightPos = vec3(0, 25, 0);
    vec3 lightCol = vec3(0.91, 0.88, 0.79);

    vec3 ambient = 0.15 * lightCol;

    vec3 lightDir = normalize(lightPos - oFragPos);
    float diff = max(dot(oNorm, lightDir), 0.0);
    vec3 diffuse = diff * lightCol * uDiffuse;

    if (uDiffTextureExists == 1)
    {
        vec3 textureCol = texture(uDiffTexture, oUv).rgb;
        diffuse *= textureCol;
        ambient *= textureCol;
    }

    vec3 viewDir = normalize(uViewPos - oFragPos);
    vec3 norm = normalize(oNorm);
    vec3 reflect = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflect), 0.0), 32);
    vec3 specular = 0.5 * spec * lightCol;

    vec3 result = (ambient + diffuse + specular);

    oFragColor = vec4(result, 1.0f);
}