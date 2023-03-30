#include "avalon_internal.h"
#include <glad/glad.h>

void avalon_rendertarget_size_set(float width, float height) {
	uint64_t loc = avalon_shader_uniform_seek(shader_flat, "window_scale");
	glUniform2f(loc, 1.0f/width, 1.0f/height);
}

