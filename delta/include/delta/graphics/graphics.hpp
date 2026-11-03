#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace Delta {
struct Rect {
    Rect(std::vector<glm::vec2> position, float width, float height);

    unsigned int EBO;
    unsigned int VAO;

private:
    std::vector<glm::vec2> rectVertices;
};

struct Renderer {
    Renderer(int viewportWidth, int viewportHeight);
    void clear(float r, float g, float b, float a);
    void drawRect(Rect& rect);

private:
    unsigned int shaderProgram;
};
} // namespace Delta
