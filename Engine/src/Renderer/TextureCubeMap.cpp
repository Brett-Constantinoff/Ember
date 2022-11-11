#include "TextureCubeMap.h"

TextureCubeMap::TextureCubeMap(uint32_t type, std::vector<const char*>& files) :
	Texture{ type }, m_files{ files }
{
	load();
}

TextureCubeMap::~TextureCubeMap()
{
}

void TextureCubeMap::load()
{
	bind();
    int32_t width;
    int32_t height;
    int32_t channels;
    int32_t i = 0;
    for (const char* file : m_files) 
    {
        uint8_t* fileData = stbi_load(file, &width, &height, &channels, 0);
        if (fileData) {
            GLenum format = 0;
            if (channels == 1) 
            {
                format = GL_RED;
            }
            else if (channels == 3) {

                format = GL_RGB;
            }
            else if (channels == 4) 
            {
                format = GL_RGBA;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, fileData);
        }
        else 
        {
            std::cout << "File failed to load: " << file << std::endl;
        }
        stbi_image_free(fileData);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    unbind();
}