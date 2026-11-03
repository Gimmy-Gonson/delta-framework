#include <delta/utils/readFile.hpp>

#include <fstream>
#include <print>
#include <sstream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::println(stderr, "Error: Failed to open file: {}", path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
