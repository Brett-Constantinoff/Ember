#pragma once
#include <string>
#include <sstream>
#include "../Math/glm.hpp"
#include "Shader.h"
#include "Light.h"

template <typename T>
class LightCaster
{
public:
	LightCaster(T light);
	~LightCaster();

	T* getLight();

private:
	T m_light;
};

template <typename T>
LightCaster<T>::LightCaster(T light) :
	m_light{ light }
{
}

template <typename T>
LightCaster<T>::~LightCaster()
{
}

template <typename T>
T* LightCaster<T>::getLight(void)
{
	return &m_light;
}