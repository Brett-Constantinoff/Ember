#include "Scene.h"

namespace Ember::Scene
{
	Scene::Scene(const SceneCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_sceneEntities{}, m_skyBox{nullptr}, m_fileDataMap{},
		m_sceneShader{nullptr}, m_skyboxShader{nullptr}
	{
		Core::Logger::getInstance().logInfo(std::string{"Scene created"}, __FILE__);
	}

	Scene::~Scene()
	{
		Core::Logger::getInstance().logInfo(std::string{"Scene destroyed"}, __FILE__);
	}

	void Scene::addEntity(Entity* e)
	{
		if (e->m_createInfo.m_type == EntityType::Renderable || e->m_createInfo.m_type == EntityType::Skybox)
		{
			// for file data
			const auto& iterator{ m_fileDataMap.find(e->m_createInfo.m_objFile) };

			// file data has been loaded in the past, no need to re-load it
			if (iterator != m_fileDataMap.end())
			{
				e->m_attrib = iterator->second.m_attrib;
				e->m_materials = iterator->second.m_materials;
				e->m_shapes = iterator->second.m_shapes;
				e->createMeshes(false);
			}

			// create new file data and add it to the map
			else
			{
				e->createMeshes(true);
				m_fileDataMap.insert({ e->m_createInfo.m_objFile, {e->m_attrib,
					e->m_shapes, e->m_materials} });
			}
		}
		m_sceneEntities.emplace_back(e);
	}

	std::vector<std::shared_ptr<Entity>> Scene::getEntities() const
	{
		return m_sceneEntities;
	}

	bool Scene::getSkyboxEnabled() const
	{
		return m_createInfo.m_enableSkybox;
	}

	int32_t Scene::getMeshCount() const
	{
		std::size_t meshCount{ 0 };
		for (const auto& e : m_sceneEntities)
			meshCount += e->m_meshes.size();
		return static_cast<int32_t>(meshCount);
	}

	int32_t Scene::getVertexCount() const
	{
		std::size_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->m_meshes)
				count += (mesh->getRenderData().m_vertexPositions.size()) / 3;
		return static_cast<int32_t>(count);
	}

	int32_t Scene::getPolygonCount() const
	{
		std::size_t count{};
		for (const auto& e : m_sceneEntities)
			for (const auto& mesh : e->m_meshes)
				count += (mesh->getRenderData().m_vertexPositions.size()) / 9;
		return static_cast<int32_t>(count);
	}

	int32_t Scene::getDifferingObjects() const
	{
		return static_cast<int32_t>(m_fileDataMap.size());
	}


	int32_t Scene::getEntityCount() const
	{
		return static_cast<int32_t>(m_sceneEntities.size());
	}

	std::shared_ptr<Camera> Scene::getCamera() const
	{
		return m_createInfo.m_camera;
	}

	std::shared_ptr<Renderer::OpenglShader> Scene::getShadergl() const
	{
		return m_sceneShader;
	}

	std::shared_ptr<Renderer::OpenglShader> Scene::getSkyboxShadergl() const
	{
		return m_skyboxShader;
	}

	std::shared_ptr<Entity> Scene::getSkybox() const
	{
		return m_skyBox;
	}

	SceneShading Scene::getSceneShading() const
	{
		return m_createInfo.m_sceneShading;
	}

	void Scene::createSkybox(Entity* e)
	{
		m_skyBox.reset(e);
		m_skyBox->createMeshes(true);
	}

	void Scene::createSkyboxShadergl(std::string& shaderFile)
	{
		m_skyboxShader.reset(EMBER_NEW Renderer::OpenglShader(shaderFile));
	}

	void Scene::createSceneShadergl(std::string& shaderFile)
	{
		m_sceneShader.reset(EMBER_NEW Renderer::OpenglShader(shaderFile));
	}

	void Scene::createSceneShadervk(std::string& shaderFile)
	{
		m_sceneShadervk.reset(EMBER_NEW Renderer::VulkanShader(shaderFile));
	}
}