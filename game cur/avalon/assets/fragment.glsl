#version 330 core

layout(location=0) out vec4 color;

uniform sampler2D image;

in vec2 f_uv;
in vec4 f_color;

void main() {
//	vec4 c = f_color;
//	c.rg = f_uv;
//	color = c;
	color = texture(image, f_uv);
}
