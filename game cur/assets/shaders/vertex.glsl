#version 330 core

layout (location=0) in vec2 position;
layout (location=1) in vec2 uv_coord;
layout (location=2) in vec2 offset;
layout (location=3) in vec2 uv_offset;
out vec2 uv;

uniform vec2 origin;
uniform vec2 window_scale;
uniform vec2 uv_scale;

void main() {
	uv = uv_offset + uv_coord * uv_scale;
//	uv = uv_coord * uv_scale + uv_offset;
//	uv.y = 1.0f - uv.y;
	
//	vec2 window_scale = vec2(1.0f);

	gl_Position = vec4(
		(position - origin + offset) * window_scale + vec2(-1.0f, 1.0f),
		1.0f, 1.0f
	);
}
