#include "avalon_internal.h"
#include <glad/glad.h>

avalon_list images = AVALON_LIST_INIT(image);


uint64_t avalon_image_create_from_data_2d(uint8_t *pixels, uint16_t width, uint16_t height) {
	uint64_t i = images.element_count;
	image *image = avalon_list_get_new(&images);	
	image->pixels = pixels;
	image->width = width;
	image->height = height;
	image->depth = 0;
	image->dimensions = 2;

	glGenTextures(1, &image->texture);

	glBindTexture(GL_TEXTURE_2D, image->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	return i;
}
