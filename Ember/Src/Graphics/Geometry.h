#pragma once
#include <vector>
#include "../Math/glm.hpp"
#include "../Math/gtc/constants.hpp"

enum class Type
{
	QUAD = 0,
	CUBE = 1,
	SPHERE = 2,
	CYLINDER = 3,
	CUSTOM = 4,
	OBJ = 5
};

struct Geometry
{
	std::vector<float> m_vertexPos;
	std::vector<uint32_t> m_indices;
	std::vector<float> m_uvs;

	//for built in types
	Geometry(Type Type);

	//obj meshes
	Geometry(const char* filePath = nullptr);

	//can define custom meshes
	Geometry(std::vector<float> vertexPos, std::vector<uint32_t> indices, std::vector<float> m_uvs);
};