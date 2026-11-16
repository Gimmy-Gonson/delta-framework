#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace Delta {
struct Color {
    float red;
    float green;
    float blue;
    float alpha;
};

struct Rect {
    Rect(glm::vec2 position, float width, float height, Color tint);

    inline static unsigned int VBO;
    inline static unsigned int EBO;
    inline static unsigned int VAO;

    inline static std::vector<unsigned int> indices; /*= {{0, 1, 3, 1, 2, 3,}};*/

private:
    inline static std::vector<glm::vec2> rectVertices;
};

struct Renderer {
    Renderer(int viewportWidth, int viewportHeight);
    void clear(float r, float g, float b, float a);
    void drawRect(const Rect& rect);

private:
    unsigned int shaderProgram;
};
} // namespace Delta
