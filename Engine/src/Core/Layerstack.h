#pragma once
#include "Layer.h"
#include <stack>
#include <vector>
#include <iostream>
#include <stdint.h>

class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void push(Layer* layer, Window* win);
    void pop();
    int8_t size();
    void updateLayers(float dt);

private:
    bool isEmpty();

private:
    std::vector<Layer*> m_layers;
};