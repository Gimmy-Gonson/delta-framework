#include <delta/delta.hpp>
#include <glad/gl.h>

namespace Delta {
void init() {
    gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));

    glViewport(0, 0, 1280, 960);
}
} // namespace Delta
