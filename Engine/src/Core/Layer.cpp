#include "Layer.h"

Layer::Layer(const char* name) :
	m_name{ name }
{
}

const char* Layer::getName()
{
	return m_name;
}