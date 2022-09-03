#pragma once
#include <vector>
#include "../Math/glm.hpp"
#include "../Math/gtc/constants.hpp"

enum class Primitive
{
	QUAD = 0,
	CUBE = 1,
	SPHERE = 2,
};

struct Geometry
{
	std::vector<float> m_vertexPos;
	std::vector<float> m_vertexNorm;
	std::vector<uint32_t> m_indices;
	std::vector<float> m_uvs;

	//for built in types
	Geometry(Primitive Type);

	//obj meshes
	Geometry(const char* filePath);

	//can define custom meshes
	Geometry(std::vector<float> vertexPos, std::vector<float> vertexNorm, std::vector<uint32_t> indices, std::vector<float> m_uvs);
};