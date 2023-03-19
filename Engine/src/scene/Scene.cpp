#include "Scene.h"

namespace Ember::Scene
{
	Scene::Scene(const SceneCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_sceneEntities{}, m_skyBox{nullptr}, m_attribMap{}
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::addEntity(Entity* e)
	{
		// fist check if entity obj data is in map
		const auto& it{ m_attribMap.find(e->getObjFile()) };
		if (it != m_attribMap.end())
			e->setAttrib(it->second);

		m_sceneEntities.emplace_back(e);

		// if object wasnt in map, add it after the data has been loaded
		if (it == m_attribMap.end())
			m_attribMap.insert({ e->getObjFile(), e->getAttrib() });
	}

	void Scene::addSkybox(Entity* skybox)
	{
		m_skyBox.reset(skybox);
	}

	std::vector<std::shared_ptr<Entity>> Scene::getEntities() const
	{
		return m_sceneEntities;
	}

	int32_t Scene::getMeshCount() const
	{
		std::size_t meshCount{ 0 };
		for (const auto& e : m_sceneEntities)
			meshCount += e->getMeshes().size();
		return static_cast<int32_t>(meshCount);
	}

	int32_t Scene::getVertexCount() const
	{
		std::size_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->getMeshes())
				count += (mesh->getRenderData().m_vertexPositions.size()) / 3;
		return static_cast<int32_t>(count);
	}

	int32_t Scene::getPolygonCount() const
	{
		std::size_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->getMeshes())
				count += (mesh->getRenderData().m_vertexPositions.size()) / 9;
		return static_cast<int32_t>(count);
	}

	int32_t Scene::getDifferingObjects() const
	{
		return static_cast<int32_t>(m_attribMap.size());
	}


	int32_t Scene::getEntityCount() const
	{
		return static_cast<int32_t>(m_sceneEntities.size());
	}

	std::shared_ptr<Camera> Scene::getCamera() const
	{
		return m_createInfo.m_camera;
	}

	std::shared_ptr<Renderer::Shader> Scene::getShader() const
	{
		return m_createInfo.m_shader;
	}

	std::shared_ptr<Renderer::Shader> Scene::getSkyboxShader() const
	{
		return m_createInfo.m_skyboxShader;
	}

	std::shared_ptr<Entity> Scene::getSkybox() const
	{
		return m_skyBox;
	}
}