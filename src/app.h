#pragma once

#include "game.h"
#include "menu.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class App
{
public:
	GLFWwindow* window;
	glm::ivec2 size = glm::ivec2(1920, 1080);

	float current_frame = 0.0f;
	float last_frame = 0.0f;
	float delta_frame = 0.0f;
	float frame_rate = 120.0f;

	float current_tick = 0.0f;
	float last_tick = 0.0f;
	float delta_tick = 0.0f;
	float tick_rate = 12.0f;

	std::vector<Game> games;
	int game_count = 20;

	Menu menu;

	void setup();
	void mainloop();
	void cleanup();

	void init();
	void start();
	void updateState();
	void updateMesh();
	void updateVAO();
	void draw();
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_cursor_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void APIENTRY debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
