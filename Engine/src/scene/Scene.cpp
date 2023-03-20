#include "Scene.h"

namespace Ember::Scene
{
	Scene::Scene(const SceneCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_sceneEntities{}, m_skyBox{nullptr}, m_fileDataMap{},
		m_sceneShader{nullptr}, m_skyboxShader{nullptr}
	{
		setupShaders();
	}

	Scene::~Scene()
	{
	}

	void Scene::addEntity(Entity* e)
	{
		if (e->m_createInfo.m_type == EntityType::RENDERABLE || e->m_createInfo.m_type == EntityType::SKYBOX)
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

	std::shared_ptr<Renderer::Shader> Scene::getShader() const
	{
		return m_sceneShader;
	}

	std::shared_ptr<Renderer::Shader> Scene::getSkyboxShader() const
	{
		return m_skyboxShader;
	}

	std::shared_ptr<Entity> Scene::getSkybox() const
	{
		return m_skyBox;
	}

	void Scene::setupShaders()
	{
		std::filesystem::path dir{ std::filesystem::current_path() };
		std::string shaderPath{ "../Engine/assets/shaders/" };
		std::string objPath{ "../Engine/assets/models/" };
		std::filesystem::path relShader{ std::filesystem::relative(shaderPath, dir) };
		std::filesystem::path relObj{ std::filesystem::relative(objPath, dir) };

		// create skybox shader and entity
		if (m_createInfo.m_enableSkybox)
		{
			std::filesystem::path skyboxShader{ relShader };
			std::filesystem::path skyboxObj{ relObj };
			m_skyboxShader.reset(new Renderer::Shader(skyboxShader.append("skyBox.hlsl").string()));

			EntityCreateInfo createInfo{};
			createInfo.m_name = "Skybox";
			createInfo.m_objFile = skyboxObj.append("skybox.obj").string();
			createInfo.m_mtlFile = "";
			createInfo.m_type = EntityType::SKYBOX;
			m_skyBox.reset(EMBER_NEW Entity(createInfo));
			m_skyBox->createMeshes(true);
		}

		if (m_createInfo.m_sceneShading == SceneShading::BASIC)
		{
			std::filesystem::path shadingPath{ relShader };
			m_sceneShader.reset(new Renderer::Shader(shadingPath.append("basicShading.hlsl").string()));
		}
		else if (m_createInfo.m_sceneShading == SceneShading::CUSTOM)
		{
			// allow custom shading
		}

	}
}