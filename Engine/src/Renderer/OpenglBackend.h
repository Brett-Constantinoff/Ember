#pragma once
#include "RendererBackend.h"
#include "../core/ImageLoading.h"

namespace Ember::Renderer
{
	class OpenglBackend : public RendererBackend
	{
	public:
		OpenglBackend() = default;

	private:
		virtual void init(const RendererCreateInfo& createInfo);
		virtual void destroy();
		virtual void update(float dt);
		virtual void render();
		virtual void renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh);
		virtual void renderSkybox();
		virtual void loadSkybox();

		
	};
}