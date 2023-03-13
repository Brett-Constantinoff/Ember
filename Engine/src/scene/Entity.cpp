#include "Entity.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>

namespace Ember::Scene
{
	Entity::Entity(const EntityCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_mesh{createInfo.m_objFile}
	{
	}

	Entity::~Entity()
	{
	}

	EntityType& Entity::getType()
	{
		return m_createInfo.m_type;
	}

	Mesh& Entity::getMesh() 
	{
		return m_mesh;
	}

	void Entity::rotateFixedY(float angle)
	{
		auto rotation{ m_mesh.getTransformData().m_rotate };
		m_mesh.getTransformData().m_rotate = glm::rotate(rotation, glm::radians(angle), { 0, 1, 0 });
	}
}