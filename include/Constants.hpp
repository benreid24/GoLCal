#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr std::uint32_t PipelineId = 1024;

constexpr float WindowWidth  = 1920.f;
constexpr float WindowHeight = 1080.f;
constexpr glm::vec2 WindowSize(WindowWidth, WindowHeight);

constexpr float TicksPerSecond = 1.f;
constexpr float TickPeriod     = 1.f / TicksPerSecond;
constexpr float CellSize       = 32.f;

constexpr unsigned int Width  = WindowWidth / CellSize;
constexpr unsigned int Height = WindowHeight / CellSize;

#endif
