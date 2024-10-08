#ifndef DESCRIPTORSET_HPP
#define DESCRIPTORSET_HPP

#include <BLIB/Render.hpp>
#include <Constants.hpp>
#include <glm/glm.hpp>
#include <gol/gol.h>

struct ShaderCell {
    unsigned int species;
    glm::vec3 color;

    ShaderCell& operator=(Cell val) {
        species = val.species;
        color.x = val.r;
        color.y = val.g;
        color.z = val.b;
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
