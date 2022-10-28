#include "LayerStack.h"

LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
    for (Layer* layer : m_layers)
    {
        std::cout << "Destroying " << layer->getName() << std::endl;
        layer->onDetach();
        delete layer;
    }
    m_layers.clear();
}

void LayerStack::push(Layer* layer, Window* win)
{
    std::cout << "Creating " << layer->getName() << std::endl;
    layer->onAttach(win);
    m_layers.push_back(layer);
}

void LayerStack::pop()
{
    m_layers.back()->onDetach();
    delete m_layers.back();
}

bool LayerStack::isEmpty()
{
    return m_layers.size() == 0;
}

int8_t LayerStack::size()
{
    return m_layers.size();
}

void LayerStack::updateLayers(float dt)
{
    for (int8_t i = m_layers.size() - 1; i >= 0; i--)
    {
        Layer* layer = m_layers[i];
        layer->onUpdate(dt);
        layer->onRender();
        layer->onImguiRender();
    }
}