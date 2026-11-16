#include <delta/graphics/graphics.hpp>
#include <delta/utils/readFile.hpp>
#include <glad/gl.h>
#include <print>
#include <delta/delta.hpp>

namespace Delta {
Rect::Rect(glm::vec2 position, float width, float height, Color tint) {
    const unsigned int baseVertex = static_cast<unsigned int>(rectVertices.size());

    glm::vec2 const topRight = {position.x + width, position.y};
    glm::vec2 const bottomRight = {position.x + width, position.y + height};
    glm::vec2 const bottomLeft = {position.x, position.y + height};
    glm::vec2 const topLeft = position;
    rectVertices.push_back({2.0f * topRight.x / 1280.0f - 1.0f, 1.0f - 2.0f * topRight.y / 960.0f});
    rectVertices.push_back({2.0f * bottomRight.x / 1280.0f - 1.0f, 1.0f - 2.0f * bottomRight.y / 960.0f});
    rectVertices.push_back({2.0f * bottomLeft.x / 1280.0f - 1.0f, 1.0f - 2.0f * bottomLeft.y / 960.0f});
    rectVertices.push_back({2.0f * topLeft.x / 1280.0f - 1.0f, 1.0f - 2.0f * topLeft.y / 960.0f});

    // if (rectVertices.size() > 4) {
    //     indices.reserve(indices.size() + 6);
    //     const unsigned int indicesOffset = indices.size() - 6;
    //     for (int i = indicesOffset; i < indices.size(); i++) {
    //         indices.emplace_back(indices[i] + 4);
    //         std::println("{}", indices[i]);
    //     }
    // }
    indices.push_back(baseVertex + 0);
    indices.push_back(baseVertex + 1);
    indices.push_back(baseVertex + 3);
    indices.push_back(baseVertex + 1);
    indices.push_back(baseVertex + 2);
    indices.push_back(baseVertex + 3);
    // std::println("{}", indices.size());

    if (rectVertices.size() >= 4) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, rectVertices.size() * sizeof(glm::vec2), rectVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Renderer::Renderer(const int viewportWidth, const int viewportHeight) {
    glViewport(0, 0, viewportWidth, viewportHeight);

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

void Renderer::drawRect(const Rect& rect) {
    glUseProgram(shaderProgram);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, rect.tint);

    glBindVertexArray(rect.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.EBO);

    glDrawElements(GL_TRIANGLES, rect.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace Delta
