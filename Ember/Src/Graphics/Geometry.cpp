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
		int32_t n = 32;
		int32_t m = 16;
		float theta = 0.0f;
		float thetaStep = glm::two_pi<float>() / n;
		float phi = 0.0f;
		float phiStep = glm::pi<float>() / m;

		for (int32_t i = 0; i < m + 1; i++)
		{
			for (int32_t j = 0; j < n + 1; j++)
			{
				m_vertexPos.push_back(cos(theta)* sin(phi));
				m_vertexPos.push_back(cos(phi));
				m_vertexPos.push_back(sin(theta) * sin(phi));
				theta += thetaStep;

				float s = static_cast<float>(j) / static_cast<float>(n);
				float t = static_cast<float>(i) / static_cast<float>(m);

				m_uvs.push_back(s);
				m_uvs.push_back(t);
			}
			phi += phiStep;
			theta = 0;
		}

		for (int32_t i = 0; i < m_vertexPos.size() / 3 - n - 2; i++)
		{
			m_indices.push_back(i);
			m_indices.push_back(i + n + 1);
			m_indices.push_back(i + n + 2);

			m_indices.push_back(i);
			m_indices.push_back(i + n + 2);
			m_indices.push_back(i + 1);
		}

	}
	else if (type == Type::CYLINDER)
	{
		int32_t n = 32;
		float thetaStep = glm::two_pi<float>() / n;
		float theta = 0.0f;

		//top
		m_vertexPos.push_back(0.0f);
		m_vertexPos.push_back(1.0f);
		m_vertexPos.push_back(0.0f);

		for (int32_t i = 0; i < n + 2; i++)
		{
			float x = cos(theta);
			float y = 1.0;
			float z = sin(theta);

			m_vertexPos.push_back(x);
			m_vertexPos.push_back(-y);
			m_vertexPos.push_back(z);

			m_vertexPos.push_back(x);
			m_vertexPos.push_back(y);
			m_vertexPos.push_back(z);

			theta += thetaStep;
		}

		//bottom
		m_vertexPos.push_back(0.0f);
		m_vertexPos.push_back(-1.0f);
		m_vertexPos.push_back(0.0f);

		//body
		for (int32_t i = 3; i < m_vertexPos.size() / 3 - 1; i += 2)
		{
			m_indices.push_back(i);
			m_indices.push_back(i + 1);
			m_indices.push_back(i + 2);

			m_indices.push_back(i + 1);
			m_indices.push_back(i + 3);
			m_indices.push_back(i + 2);
		}

		//circles
		for (int32_t i = 3; i < m_vertexPos.size() / 3 - 1; i += 2)
		{
			m_indices.push_back(i + 2);
			m_indices.push_back(2);
			m_indices.push_back(i);

			m_indices.push_back(i + 1);
			m_indices.push_back(1);
			m_indices.push_back(i + 3);
		}
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