#include <glad/glad.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "avalon.h"
#include "avalon_internal.h"


avalon_list meshes = AVALON_LIST_INIT(mesh);


uint64_t avalon_mesh_create(vertex *vertices, uint64_t vertex_count, uint16_t* indices, uint64_t index_count) {
	uint64_t id = meshes.element_count;


	mesh *mesh = avalon_list_get_new(&meshes);

	mesh->index_count= index_count;
	avalon_list_init(&mesh->objects, sizeof(object));

	glGenBuffers(3, &mesh->buffer_index);
	glGenVertexArrays(1, &mesh->vertex_array);

	glBindVertexArray(mesh->vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->buffer_index);

	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(*vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(*indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void *) offsetof(vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void *) offsetof(vertex, uv));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void *) offsetof(vertex, color));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer_object);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(object), (const void *) offsetof(object, position));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(object), (const void *) offsetof(object, color));
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(object), (const void *) offsetof(object, size));
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

	return id;
}



uint64_t avalon_object_create(uint64_t mesh_id) {
	mesh *mesh = avalon_list_get(&meshes, mesh_id);
	uint64_t id = mesh->objects.element_count;

	object *object = avalon_list_get_new(&mesh->objects);
	object->position.x = 0.0f;
	object->position.y = 0.0f;
	object->size.x = 1.0f;
	object->size.y = 1.0f;
	object->color.x = 1.0f;
	object->color.y = 1.0f;
	object->color.z = 1.0f;
	object->color.w = 1.0f;

	return id;
}


object *avalon_object_get(uint64_t mesh_id, uint64_t object_id) {
	mesh *mesh = avalon_list_get(&meshes, mesh_id);
	return avalon_list_get(&mesh->objects, object_id);
}


void avalon_render() {
	uint64_t i;
//	glUseProgram(shader_flat);
	avalon_shader_use(shader_flat);
	glDisable(GL_DEPTH_TEST);

	for (i = 0; i < meshes.element_count; i++) {
		mesh *mesh = avalon_list_get(&meshes, i);
		glBindVertexArray(mesh->vertex_array);
		
		glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer_object);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(object) * mesh->objects.element_count,
			mesh->objects.elements,
			GL_STATIC_DRAW
		);

		glDrawElementsInstanced(
				GL_TRIANGLES,
				mesh->index_count,
				GL_UNSIGNED_SHORT,
				0,
				mesh->objects.element_count
		);
	}
};



uint shader_flat;
uint64_t avalon_mesh_rectangle;
uint64_t avalon_mesh_image;

void avalon_init() {
	char *shader_vertex_source = avalon_file_read("avalon/assets/vertex.glsl");
	char *shader_fragment_source = avalon_file_read("avalon/assets/fragment.glsl");
	shader_flat = avalon_shader_create_vf(shader_vertex_source, shader_fragment_source);
	
	free(shader_vertex_source);
	free(shader_fragment_source);
	avalon_shader_use(shader_flat);

	{
		vertex vertices[] = {
			{.position = {0.0f, 0.0f}, .uv = {0.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}},
			{.position = {1.0f, 0.0f}, .uv = {1.0f, 0.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}},
			{.position = {0.0f, -1.0f}, .uv = {0.0f, 1.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}},
			{.position = {1.0f, -1.0f}, .uv = {1.0f, 1.0f}, .color = {1.0f, 1.0f, 1.0f, 1.0f}}
		};
		uint16_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		avalon_mesh_rectangle = avalon_mesh_create(vertices, 4, indices, 6);
		avalon_mesh_image = avalon_mesh_create(vertices, 4, indices, 6);
	}
}
