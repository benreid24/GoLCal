#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoords;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragPos;

layout(set = 0, binding = 0) uniform cam {
    mat4 viewProj;
} camera;

layout(std140, set = 1, binding = 0) readonly buffer obj {
    mat4 model[];
} object;

struct Cell {
    uint species;
    vec3 color;
};

layout(set = 2, binding = 0) uniform sd {
    uint width;
    uint height;
    vec2 gridSize;
    Cell cells[1980];
} data;

void main() {
    vec4 worldPos = object.model[gl_InstanceIndex] * vec4(inPosition, 1.0);
	gl_Position = camera.viewProj * worldPos;
	fragColor = inColor;
    fragPos = inPosition.xy;
}
