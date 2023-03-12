#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oNorm;
out vec3 oFragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    oNorm = mat3(transpose(inverse(model))) * aNorm;
    oFragPos = vec3(model * vec4(aPos, 1.0));
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core
in vec3 oNorm;
in vec3 oFragPos;

uniform vec3 uViewPos;

out vec4 oFragColor;

void main()
{
    vec3 lightPos = vec3(0, 10, 0);
    vec3 lightCol = vec3(0.91, 0.88, 0.79);

    vec3 ambient = 0.1 * lightCol;

    vec3 lightDir = normalize(lightPos - oFragPos);
    float diff = max(dot(oNorm, lightDir), 0.0);
    vec3 diffuse = diff * lightCol;

    vec3 viewDir = normalize(uViewPos - oFragPos);
    vec3 norm = normalize(oNorm);
    vec3 reflect = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflect), 0.0), 32);
    vec3 specular = 0.5 * spec * lightCol;

    vec3 result = (ambient + diffuse + specular) * vec3(0.6, 0.6, 0.6);
    oFragColor = vec4(result, 1.0f);
}