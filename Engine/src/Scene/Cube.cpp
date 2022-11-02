#pragma once
#include "Cube.h"

Cube::Cube(std::string& name, std::string& shader) :
	SceneObject(name, shader), m_colorBuffer{GL_ARRAY_BUFFER}
{
    m_vao.bind();

    float vertexData[] = {
        // positions            // colors
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    };
    m_vbo.bind();
    m_vbo.setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

    m_colorBuffer.bind();
    m_colorBuffer.setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
}

Cube::~Cube()
{
}

