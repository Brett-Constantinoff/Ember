#include "OpenglShader.h"

namespace Ember
{
    namespace Renderer
    {
        OpenglShader::OpenglShader(const std::string& filepath) :
            m_shaderFile{filepath}
        {
            m_ID = glCreateProgram(); //creates current shader program

            parseShader();
            uint32_t vShader = compileShader(m_shaderSource.vertexSource, GL_VERTEX_SHADER); //compiles vertex source
            uint32_t fShader = compileShader(m_shaderSource.fragmentSource, GL_FRAGMENT_SHADER); //compiles fragment source

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

        OpenglShader::~OpenglShader()
        {
            glDeleteProgram(m_ID);
        }

        void OpenglShader::use(void)
        {
            glUseProgram(m_ID);
        }

        void OpenglShader::disuse(void)
        {
            glUseProgram(0);
        }

        int32_t OpenglShader::getId(void) const
        {
            return m_ID;
        }

        int32_t OpenglShader::compileShader(const std::string& source, int32_t type)
        {
            const char* src = source.c_str();

            int32_t shadermID = glCreateShader(type);
            glShaderSource(shadermID, 1, &src, nullptr);
            glCompileShader(shadermID);

            int32_t success;
            GLchar infoLog[512];
            glGetShaderiv(shadermID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shadermID, 512, NULL, infoLog);
                Core::Logger::getInstance().logWarn(std::string{"Cannot compile shader from: " + m_shaderFile + " " + infoLog}, __FILE__);
            }
            return shadermID;
        }

        void OpenglShader::parseShader()
        {
            enum class ShaderType
            {
                NONE = -1, VERTEX = 0, FRAGMENT = 1
            };

            ShaderType type = ShaderType::NONE;
            std::ifstream stream(m_shaderFile);
            if (!stream)
                Core::Logger::getInstance().logWarn(std::string{"Cannot find shader file: " + m_shaderFile}, __FILE__);

            std::string line;
            std::stringstream ss[2];

            while (getline(stream, line))
            {
                if (line.find("#shader") != std::string::npos)
                {
                    if (line.find("vertexShader") != std::string::npos)
                        type = ShaderType::VERTEX;
                    
                    else if (line.find("fragmentShader") != std::string::npos)
                        type = ShaderType::FRAGMENT;
                    
                }
                else
                    ss[(int32_t)type] << line << '\n';
            }
            m_shaderSource.vertexSource = ss[0].str();
            m_shaderSource.fragmentSource = ss[1].str();
        }

        int32_t OpenglShader::getUniform(const std::string& name)
        {
            // uniform has been located, return from cache
            if (m_uniformCache.find(name.c_str()) != m_uniformCache.end())
                return m_uniformCache[name.c_str()];
            
            // add new uniform to the not found cache with print value 0
            m_uniformNotFoundCache[name.c_str()] = 0;

            int32_t location = glGetUniformLocation(m_ID, name.c_str());

            // uniform not found
            if (location == -1)
            {
                // only print this message once per uniform, otherwise endless logs will be printed
                if (m_uniformNotFoundCache[name.c_str()] == 0)
                {
                    Core::Logger::getInstance().logWarn(std::string{"Cannot find uniform: " + name}, __FILE__);
                    m_uniformNotFoundCache[name.c_str()] = 1;
                }
            }

            // uniform found correctly, add it to location cache
            m_uniformCache[name.c_str()] = location;
            return location;
        }

        void OpenglShader::setVec4(const std::string& name, const glm::vec4& uniform)
        {
            int32_t location = getUniform(name);
            if (location != -1)
                glUniform4fv(location, 1, &uniform[0]);
        }

        void OpenglShader::setVec3(const std::string& name, const glm::vec3& uniform)
        {
            int32_t location = getUniform(name);
            if (location != -1)
                glUniform3fv(location, 1, &uniform[0]);
        }

        void OpenglShader::setMat4(const std::string& name, const glm::mat4& uniform)
        {
            int32_t location = getUniform(name);
            if (location != -1)
                glUniformMatrix4fv(location, 1, GL_FALSE, &uniform[0][0]);
        }

        void OpenglShader::setInt(const std::string& name, int32_t uniform)
        {
            int32_t location = getUniform(name);
            if (location != -1)
                glUniform1i(location, uniform);
            
        }

        void OpenglShader::setFloat(const std::string& name, float uniform)
        {
            int32_t location = getUniform(name);
            if (location != -1)
                glUniform1f(location, uniform);
        }
    }
}