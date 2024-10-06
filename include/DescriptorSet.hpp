#ifndef DESCRIPTORSET_HPP
#define DESCRIPTORSET_HPP

#include <BLIB/Render.hpp>
#include <Constants.hpp>
#include <gol/gol.h>

struct ShaderPayload {
    std::uint32_t width;
    std::uint32_t height;
    float cellSize;
    float padding;
    Cell cells[Width * Height];
};

using Bindings = bl::rc::ds::Bindings<bl::rc::ds::GlobalUniformBuffer<ShaderPayload>>;
using Factory =
    bl::rc::ds::GenericDescriptorSetFactory<Bindings, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT>;
using Set = bl::rc::ds::GenericDescriptorSetInstance<Bindings>;

#endif
