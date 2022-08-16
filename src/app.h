#pragma once

#include "game.h"

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
	float delta_time = 0.0f;

	std::vector<Game> games;
	int gameCount = 20;

	void setup();
	void mainloop();
	void cleanup();

	void initGames();
	void updateGames();
	void uploadGames();
	void drawGames();
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_cursor_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void APIENTRY debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
