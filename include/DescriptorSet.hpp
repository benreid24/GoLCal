#ifndef DESCRIPTORSET_HPP
#define DESCRIPTORSET_HPP

#include <BLIB/Render.hpp>
#include <Constants.hpp>
#include <glm/glm.hpp>
#include <gol/gol.h>

struct ShaderCell {
    unsigned int value;
    unsigned int padding[3];

    ShaderCell& operator=(Cell val) {
        value = val;
        return *this;
    }
};

struct ShaderPayload {
    std::uint32_t width;
    std::uint32_t height;
    glm::vec2 gridSize; // world units
    ShaderCell cells[Width * Height];
};

using Bindings = bl::rc::ds::Bindings<bl::rc::ds::GlobalUniformBuffer<ShaderPayload>>;
using Factory  = bl::rc::ds::GenericDescriptorSetFactory<Bindings, VK_SHADER_STAGE_VERTEX_BIT |
                                                                      VK_SHADER_STAGE_FRAGMENT_BIT>;
using Set      = bl::rc::ds::GenericDescriptorSetInstance<Bindings>;

#endif
