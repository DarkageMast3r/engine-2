#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "avalon_internal.h"


avalon_list shaders = AVALON_LIST_INIT(avalon_shader);

uint avalon_shader_compile(char *source, uint type) {
	uint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, (const char* const*) &source, NULL);
	glCompileShader(shader_id);
	
	int result; 
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
 
		 char *message;
		 message = calloc(1, sizeof(*message) * (length+1));
		 glGetShaderInfoLog(shader_id, length, &length, message);
		 printf(
			 "%s shader compilation error. Source:\n"
			 "%s\n\n"
			"Message:\n"
			"%s\n========\n",
			type == GL_VERTEX_SHADER ? "Vertex" : "Fragment",
			source,
			message
		);
	}

	return shader_id;
}

uint64_t avalon_shader_create_vf(char *vertex_source, char *fragment_source) {
	uint program = glCreateProgram();

	uint shader_vertex = avalon_shader_compile(vertex_source, GL_VERTEX_SHADER);
	uint shader_fragment = avalon_shader_compile(fragment_source, GL_FRAGMENT_SHADER);

	glAttachShader(program, shader_vertex);
	glAttachShader(program, shader_fragment);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(shader_vertex);
	glDeleteShader(shader_fragment);

	uint64_t shader_id = shaders.element_count;
	avalon_shader *shader = avalon_list_get_new(&shaders);
	shader->program = program;
	avalon_list_init(&shader->uniforms, sizeof(avalon_uniform));

	return shader_id;
//	return program;
}




uint8_t string_equal(char *a, char *b) {
	for (; *a & (*a==*b); a++, b++);
	return *a == *b;
}


uint64_t avalon_shader_uniform_seek(uint64_t shader_id, char *string) {
		avalon_shader *shader = avalon_list_get(&shaders, shader_id);

		uint64_t i;
		for (i = 0; i < shader->uniforms.element_count; i++) {
			avalon_uniform *uniform = avalon_list_get(&shader->uniforms, i);
			if (string_equal(string, uniform->title)) {
				return i;
			}
		}
		
		uint loc = glGetUniformLocation(shader->program, string);
		avalon_uniform *uniform = avalon_list_get_new(&shader->uniforms);
		uniform->location = loc;
		for (i = 0; string[i]; i++) {
			uniform->title[i] = string[i];
		}
		uniform->title[i+1] = 0;

		return loc;
}


void avalon_shader_use(uint64_t shader_id) {
	avalon_shader *shader = avalon_list_get(&shaders, shader_id);
	glUseProgram(shader->program);
}
/*
void avalon_shader_uniform_set_f(uint64_t shader_id, char *string, float val) {

t
}
*/
