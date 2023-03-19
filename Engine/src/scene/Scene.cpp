#include "Scene.h"

namespace Ember::Scene
{
	Scene::Scene(const SceneCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_sceneEntities{}, m_wireframe{ false }, m_skyBox{nullptr}
	{
	}

	Scene::~Scene()
	{
	}


	void Scene::addEntity(Entity* e)
	{
		m_sceneEntities.emplace_back(e);
	}

	void Scene::addSkybox(Entity* skybox)
	{
		m_skyBox.reset(skybox);
	}

	std::vector<std::shared_ptr<Entity>> Scene::getEntities()
	{
		return m_sceneEntities;
	}

	int32_t Scene::getMeshCount()
	{
		int32_t meshCount{ 0 };
		for (const auto& e : m_sceneEntities)
			meshCount += e->getMeshes().size();
		return meshCount;
	}

	int32_t Scene::getVertexCount()
	{
		int32_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->getMeshes())
				count += (mesh->getRenderData().m_vertexPositions.size()) / 3;
		return count;
	}

	int32_t Scene::getPolygonCount()
	{
		int32_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->getMeshes())
				count += (mesh->getRenderData().m_vertexPositions.size()) / 9;
		return count;
	}


	int32_t Scene::getEntityCount() const
	{
		return m_sceneEntities.size();
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

	bool& Scene::getWireFrame()
	{
		return m_wireframe;
	}
}