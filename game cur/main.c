#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "avalon/avalon.h"


void window_resize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	avalon_rendertarget_size_set(width, height);
}

int main(void) {
	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(
		1024, 1024,
		"Game",
		0, NULL
	);

	if (window == NULL) {
		glfwTerminate();
		printf("Failed to create window!\n");
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD!\n");
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, window_resize);


	avalon_init();

/*
	uint64_t mesh_square;
	{
		vertex vertices[] = {
			{.position = {-0.5f, -0.5f}, .uv = {-1.0f, -1.0f}, .color = {1.0f, 0.0f, 0.0f, 1.0f}},
			{.position = { 0.0f,  0.5f}, .uv = { 0.0f,  1.0f}, .color = {0.0f, 1.0f, 0.0f, 1.0f}},
			{.position = { 0.5f, -0.5f}, .uv = { 1.0f, -1.0f}, .color = {0.0f, 0.0f, 1.0f, 1.0f}}
		};
		uint16_t indices[] = {
			0, 1, 2
		};
		mesh_square = avalon_mesh_create(
			vertices, 3, indices, 3		
		);
	}
*/

	{
		uint64_t object_id;
		object *object;
		object_id = avalon_object_create(avalon_mesh_rectangle);
		object = avalon_object_get(avalon_mesh_rectangle, object_id);
		object->color.x = 0.5f;
		object->color.y = 0.0f;
		object->color.z = 0.5f;
		object->color.w = 1.0f;
		object->position.x = 20.0f;
		object->position.y = 50.0f;
		object->size.x = 500.0f;
		object->size.y = 50.0f;

		uint8_t pixels[] = {
			 0, 0, 0, 0,  16, 16, 16, 16,  32, 32, 32, 32,  48, 48, 48, 48,
			 64, 64, 64, 64,  80, 80, 80, 80,  96, 96, 96, 96,  112, 112, 112, 112,
			 128, 128, 128, 128,  144, 144, 144, 144,  160, 160, 160, 160,  176, 176, 176, 176,
			 192, 192, 192, 192,  208, 208, 208, 208,  224, 224, 224, 224,  240, 240, 240, 240
		};
		uint64_t image_id = avalon_image_create_from_data_2d(pixels, 4, 4);
//		uint64_t image_loc = avalon_shader_uniform_seek(shader_flat, "image");
//		glUniform


		object_id = avalon_object_create(avalon_mesh_rectangle);
		object = avalon_object_get(avalon_mesh_rectangle, object_id);
		object->color.x = 0.5f;
		object->color.y = 1.0f;
		object->color.z = 0.1f;
		object->color.w = 1.0f;
		object->position.x = 1.0f;
		object->position.y = 1.0f;
		object->size.x = 500.0f;
		object->size.y = 50.0f;

	}
	

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		avalon_render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

