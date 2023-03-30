#ifndef AVALON_H
#define AVALON_H
/*
 * Graphics library for 2D rendering
 * 
 *
 */

#include <stdio.h>
#include <stdint.h>

typedef unsigned int uint;

#define AVALON_LIST_INIT(t) {.elements = NULL, .element_count = 0, .element_max = 0, .element_size = sizeof(t)}

typedef struct {
	void *elements;
	uint64_t element_count;
	uint64_t element_max;
	uint64_t element_size;
} avalon_list;

typedef struct {
	float x, y;
} vec2f;


typedef struct {
	float x, y, z, w;
} vec4f;


typedef struct {
	uint8_t *pixels;
	uint texture;
	uint16_t width;
	uint16_t height;
	uint16_t depth;
	uint8_t dimensions;
} image;


typedef struct {
	vec2f position;
	vec2f uv;
	vec4f color;
} vertex;


typedef struct {
	vec2f position;
	vec2f size;
	vec4f color;
} object;


typedef struct {
	uint buffer_index, buffer_vertex;
	uint buffer_object;
	uint vertex_array;
	avalon_list objects;
	uint64_t index_count;
} mesh;


typedef struct {
	uint program;
	avalon_list uniforms;
} avalon_shader;


uint64_t avalon_mesh_create(vertex *vertices, uint64_t vertex_count, uint16_t *indices, uint64_t index_count);
uint64_t avalon_mesh_create_from_file_obj(char *path);

uint64_t avalon_object_create(uint64_t mesh_id);
object *avalon_object_get(uint64_t mesh_id, uint64_t object_id);


char *avalon_file_read(char *path);

void avalon_list_init(avalon_list *list, uint64_t size);
void *avalon_list_get_new(avalon_list *list);
void *avalon_list_get(avalon_list *list, uint64_t index);

uint64_t avalon_shader_create_vf(char *vertex_source, char *fragment_source);
uint64_t avalon_shader_uniform_seek(uint64_t shader_id, char *uniform);
void avalon_shader_use(uint64_t shader_id);

void avalon_rendertarget_size_set(float width, float height);

uint64_t avalon_image_create_from_data_2d(uint8_t *data, uint16_t width, uint16_t height);

void avalon_init();
void avalon_render();

extern uint64_t avalon_mesh_rectangle;
extern uint64_t avalon_mesh_image;











#endif
