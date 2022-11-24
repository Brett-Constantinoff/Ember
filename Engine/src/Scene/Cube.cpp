#include "Cube.h"

namespace Ember
{
    namespace Scene
    {
        Cube::Cube(const char* name, const Renderer::Material& material, const Renderer::Transformation& transformation) :
            SceneObject{ name, material, transformation }
        {
            m_vao.bind();
            float vertexData[] = {
                // positions              // normals          
               -0.5f, -0.5f, -0.5f,       0.0f,  0.0f, -1.0f,
                0.5f, -0.5f, -0.5f,       0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,       0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,       0.0f,  0.0f, -1.0f,
               -0.5f,  0.5f, -0.5f,       0.0f,  0.0f, -1.0f,
               -0.5f, -0.5f, -0.5f,       0.0f,  0.0f, -1.0f,

               -0.5f, -0.5f,  0.5f,       0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,       0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,       0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,       0.0f,  0.0f,  1.0f,
               -0.5f,  0.5f,  0.5f,       0.0f,  0.0f,  1.0f,
               -0.5f, -0.5f,  0.5f,       0.0f,  0.0f,  1.0f,

               -0.5f,  0.5f,  0.5f,      -1.0f,  0.0f,  0.0f,
               -0.5f,  0.5f, -0.5f,      -1.0f,  0.0f,  0.0f,
               -0.5f, -0.5f, -0.5f,      -1.0f,  0.0f,  0.0f,
               -0.5f, -0.5f, -0.5f,      -1.0f,  0.0f,  0.0f,
               -0.5f, -0.5f,  0.5f,      -1.0f,  0.0f,  0.0f,
               -0.5f,  0.5f,  0.5f,      -1.0f,  0.0f,  0.0f,

                0.5f,  0.5f,  0.5f,       1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,       1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,       1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,       1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,       1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,       1.0f,  0.0f,  0.0f,

               -0.5f, -0.5f, -0.5f,       0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,       0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,       0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,       0.0f, -1.0f,  0.0f,
               -0.5f, -0.5f,  0.5f,       0.0f, -1.0f,  0.0f,
               -0.5f, -0.5f, -0.5f,       0.0f, -1.0f,  0.0f,

               -0.5f,  0.5f, -0.5f,       0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,       0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,       0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,       0.0f,  1.0f,  0.0f,
               -0.5f,  0.5f,  0.5f,       0.0f,  1.0f,  0.0f,
               -0.5f,  0.5f, -0.5f,       0.0f,  1.0f,  0.0f,
            };
            m_vbo.bind();
            m_vbo.setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
            m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
            m_vao.unBind();
        }

        Cube::~Cube()
        {
        }
    }
}

