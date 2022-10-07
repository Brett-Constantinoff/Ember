#include "Shader.h"

Shader::Shader(const std::string& filepath)
{
    m_ID = glCreateProgram(); //creates current shader program

    shaderSource source = Shader::parseShader(filepath);
    uint32_t vShader = Shader::compileShader(source.vertexSource, GL_VERTEX_SHADER); //compiles vertex source
    uint32_t fShader = Shader::compileShader(source.fragmentSource, GL_FRAGMENT_SHADER); //compiles fragment source

    //attaches shaders to program
    glAttachShader(m_ID, vShader);
    glAttachShader(m_ID, fShader);
    //links the shader program
    glLinkProgram(m_ID);
    //ensures successful linking
    glValidateProgram(m_ID);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use(void)
{
    glUseProgram(m_ID);
}

void Shader::disuse(void)
{
    glUseProgram(0);
}

uint32_t Shader::getId(void)
{
    return m_ID;
}

uint32_t Shader::compileShader(const std::string& source, uint32_t type)
{
    const char* src = source.c_str(); //returns a pointer to source

    uint32_t shadermID = glCreateShader(type); //generates a shader mID
    glShaderSource(shadermID, 1, &src, nullptr); //fills source code for desired shader
    glCompileShader(shadermID); //compiles shader

    //ensures succesful compilation
    int32_t success;
    GLchar infoLog[512];
    glGetShaderiv(shadermID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shadermID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::" + std::to_string(type) + "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shadermID);
    }
    return shadermID;
}

shaderSource Shader::parseShader(const std::string& filePath)
{

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::ifstream stream(filePath); //gets current input stream
    if (!stream)
    {
        std::cout << "ERROR::CANNOT FIND FILE : " << filePath << std::endl;
        //exit(EXIT_FAILURE);
    }
    std::string line; //string to hold each line from file
    std::stringstream ss[2];


    while (getline(stream, line))
    {

        if (line.find("#shader") != std::string::npos)
        { //finds "#shader" in file
            if (line.find("vertexShader") != std::string::npos)
            { //the current line holds "vertexShader" set type 
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragmentShader") != std::string::npos)
            {//the current line holds "fragmentShader" set type 
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int32_t)type] << line << '\n'; //push the line into the given array based on the index
        }
    }

    return { ss[0].str(), ss[1].str() };
}

int32_t Shader::getUniform(const char* name)
{
    if (m_uniformCache.find(name) != m_uniformCache.end())
    {
        return m_uniformCache[name];
    }

    int32_t location = glGetUniformLocation(m_ID, name);
    if (location == -1)
    {
        std::cout << "ERROR FINDING UNIFORM :: " << name << std::endl;
        return -1;
    }
    m_uniformCache[name] = location;
    return location;
}

void Shader::setVec4(const char* name, glm::vec4 uniform)
{
    int32_t location = getUniform(name);
    if (location != -1)
    {
        glUniform4fv(location, 1, &uniform[0]);
    }
}

void Shader::setVec3(const char* name, glm::vec3 uniform)
{
    int32_t location = getUniform(name);
    if (location != -1)
    {
        glUniform3fv(location, 1, &uniform[0]);
    }
}

void Shader::setMat4(const char* name, glm::mat4 uniform)
{
    int32_t location = getUniform(name);
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &uniform[0][0]);
    }
}

void Shader::setInt(const char* name, int32_t uniform)
{
    int32_t location = getUniform(name);
    if (location != -1)
    {
        glUniform1i(location, uniform);
    }
}

void Shader::setFloat(const char* name, float uniform)
{
    int32_t location = getUniform(name);
    if (location != -1)
    {
        glUniform1f(location, uniform);
    }
}