#include "Geometry.h"

Geometry::Geometry(Type type)
{
	if (type == Type::QUAD)
	{
		m_vertexPos = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
		};
		m_indices = {
			 0, 1, 2,
			 2, 3, 0
		};
		m_uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};
	}

	else if (type == Type::CUBE)
	{
		m_vertexPos = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,

			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
		};
		m_indices = {
			0,  1,  2,      0,  2,  3,
			4,  5,  6,      4,  6,  7,
			8,  9,  10,     8,  10, 11,
			12, 13, 14,     12, 14, 15,
			16, 17, 18,     17, 18, 19,
			20, 21, 22,     21, 22, 23
		};
		m_uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
		};
	}
	else if (type == Type::SPHERE)
	{
		//generate sphere geometry
	}
	else if (type == Type::CYLINDER)
	{
		//generate cylinder geometry
	}
}

Geometry::Geometry(const char* file)
{
	//load geometry from file
}

Geometry::Geometry(std::vector<float> vertexPos, std::vector<uint32_t> indices, std::vector<float> uvs) :
	m_vertexPos{ vertexPos }, m_indices{ indices }, m_uvs{ uvs }
{
}