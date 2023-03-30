#version 330 core

layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec4 v_color;
layout(location = 3) in vec2 obj_position;
layout(location = 4) in vec4 obj_color;
layout(location = 5) in vec2 obj_size;

uniform vec2 window_scale;

out vec2 f_uv;
out vec4 f_color;

void main() {
	f_uv = v_uv;
	f_color = v_color * obj_color;
	gl_Position = vec4((v_position * obj_size + obj_position*vec2(1.0f, -1.0f)) * window_scale - vec2(1.0f, 0.0f-1.0f), 1.0f, 1.0f);
}
