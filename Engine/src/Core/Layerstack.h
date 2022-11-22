#pragma once
#include <iostream>
#include <stack>
#include <stdint.h>
#include <vector>
#include "Layer.h"

namespace Ember
{
    namespace Core
    {
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
    }
}
