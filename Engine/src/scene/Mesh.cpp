#include "Mesh.h"
#include <iostream>

namespace Ember::Scene
{
	Mesh::Mesh(const RenderData& renderData) :
		 m_renderData{renderData}
	{
	}

	Mesh::~Mesh()
	{
	}

	RenderData& Mesh::getRenderData()
	{
		return m_renderData;
	}

	void Mesh::setRenderData(const RenderData& renderData)
	{
		m_renderData = renderData;
	}
}