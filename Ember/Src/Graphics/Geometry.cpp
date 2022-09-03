#include "Geometry.h"

Geometry::Geometry(Primitive type)
{
	if (type == Primitive::QUAD)
	{
		m_vertexPos = {
			0.5f, 0.0f,  0.5f, 
		   -0.5f, 0.0f,  0.5f, 
		   -0.5f, 0.0f, -0.5f,

		    0.5f, 0.0f,  0.5f, 
		   -0.5f, 0.0f, -0.5f, 
		    0.5f, 0.0f, -0.5f
		};

		m_vertexNorm = {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};

		m_uvs = {
			1.0f, 0.0f, 
			0.0f, 0.0f, 
			0.0f, 1.0f,

			1.0f, 0.0f, 
			0.0f, 1.0f, 
			1.0f, 1.0f
		};
	}

	else if (type == Primitive::CUBE)
	{
		m_vertexPos = {
		   -0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
		   -0.5f,  0.5f, -0.5f,
		   -0.5f, -0.5f, -0.5f,

		   -0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
		   -0.5f,  0.5f,  0.5f,
		   -0.5f, -0.5f,  0.5f,

		   -0.5f,  0.5f,  0.5f,
		   -0.5f,  0.5f, -0.5f,
		   -0.5f, -0.5f, -0.5f,
		   -0.5f, -0.5f, -0.5f,
		   -0.5f, -0.5f,  0.5f,
		   -0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

		   -0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
		   -0.5f, -0.5f,  0.5f,
		   -0.5f, -0.5f, -0.5f,

		   -0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
		   -0.5f,  0.5f,  0.5f,
		   -0.5f,  0.5f, -0.5f,
		};

		m_vertexNorm = {
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,

			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,

			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		m_uvs = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};
	}
	//dont need to recalculate every time
	else if (type == Primitive::SPHERE)
	{
		int32_t stack = 18;
		int32_t sector = 36;
		float sectorStep = glm::two_pi<float>() / static_cast<float>(sector);
		float stackStep = glm::pi<float>() / static_cast<float>(stack);

		for (int32_t i = 0; i <= stack; i++)
		{
			float stackAngle = glm::half_pi<float>() - static_cast<float>(i * stackStep);
			float xy = cosf(stackAngle);
			float z = sinf(stackAngle);

			for (int32_t j = 0; j <= sector; j++)
			{
				float sectorAngle = static_cast<float>(j) * sectorStep;
				float x = xy * cosf(sectorAngle);
				float y = xy * sinf(sectorAngle);
				m_vertexPos.push_back(x);
				m_vertexPos.push_back(y);
				m_vertexPos.push_back(z);

				m_vertexNorm.push_back(x);
				m_vertexNorm.push_back(y);
				m_vertexNorm.push_back(z);

				float s = static_cast<float>(j) / static_cast<float>(sector);
				float t = static_cast<float>(i) / static_cast<float>(stack);
				m_uvs.push_back(s);
				m_uvs.push_back(t);
			}
		}

		for (int32_t i = 0; i < stack; i++)
		{
			int32_t k1 = i * (sector + 1);
			int32_t k2 = k1 + sector + 1;

			for (int32_t j = 0; j < sector; j++, k1++, k2++)
			{
				if (i != 0)
				{
					m_indices.push_back(k1);
					m_indices.push_back(k2);
					m_indices.push_back(k1 + 1);
				}

				if (i != (stack - 1))
				{
					m_indices.push_back(k1 + 1);
					m_indices.push_back(k2);
					m_indices.push_back(k2 + 1);
				}
			}
		}
	}
}

Geometry::Geometry(const char* file)
{
	//load geometry from file
}

Geometry::Geometry(std::vector<float> vertexPos, std::vector<float> vertexNorm, std::vector<uint32_t> indices, std::vector<float> uvs) :
	m_vertexPos{ vertexPos }, m_vertexNorm{vertexNorm}, m_indices{ indices }, m_uvs{ uvs }
{
}