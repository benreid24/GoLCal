#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragPos;

layout(location = 0) out vec4 outColor;

layout(set = 2, binding = 0) uniform sd {
    uint width;
    uint height;
    vec2 gridSize;
    uint cells[1980];
} data;

void main() {
    float w = data.width;
    float cellSize = data.gridSize.x / w;
    uint cellSizeI = uint(cellSize);

    uint x = uint(fragPos.x);
    uint y = uint(fragPos.y);
    uint gw = uint(data.gridSize.x);
    uint gh = uint(data.gridSize.y);

    uint cellX = x / cellSizeI;
    uint cellY = y / cellSizeI;
    bool isLine = x % cellSizeI == 0 || y % cellSizeI == 0 || gw - 1 == x || gh - 1 == y;

    if (isLine) {
        outColor = vec4(1, 1, 1, 1);
    }
    else {
        switch (data.cells[cellY * data.width + cellX]) {
        case 0:
            outColor = vec4(0);
            break;
        case 1:
            outColor = vec4(66.0 / 255.0, 135.0 / 255.0, 245.0 / 255.0, 1);
            break;
        case 2:
            outColor = vec4(41.0 / 255.0, 230.0 / 255.0, 66.0 / 255.0, 1);
            break;
        case 3:
            outColor = vec4(214.0 / 255.0, 36.0 / 255.0, 36 / 255.0, 1);
            break;
        }
    }
}
