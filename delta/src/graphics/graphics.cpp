#include <array>
#include <delta/graphics/graphics.hpp>
#include <delta/utils/readFile.hpp>
#include <glad/gl.h>
#include <print>

namespace Delta {
Rect::Rect(glm::vec2 position, float width, float height) {
    rectVertices.push_back({0.5f, 0.5f});
    rectVertices.push_back({0.5f, -0.5f});
    rectVertices.push_back({-0.5f, -0.5f});
    rectVertices.push_back({-0.5f, 0.5f});

    if (rectVertices.size() >= 4) {
        std::array<unsigned int, 6> indices{
            0, 1, 3, 1, 2, 3,
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, rectVertices.size() * sizeof(glm::vec2), rectVertices.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
        glEnableVertexAttribArray(0);
    }
}

Renderer::Renderer(int viewportWidth, int viewportHeight) {
    // Vertex Shader
    const std::string vertexCode = readFile("delta/shader/shader.vert");
    const char* vertexShaderCode = vertexCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::println(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
    }

    // Fragment Shader
    const std::string fragmentCode = readFile("delta/shader/shader.frag");
    const char* fragmentShaderCode = fragmentCode.c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::println(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
    }

    // Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::println(stderr, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n{}", infoLog);
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
};

void Renderer::drawRect(Rect& rect) {
    glUseProgram(shaderProgram);
    glBindVertexArray(rect.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace Delta
