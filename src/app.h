#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class App
{
public:
	GLFWwindow* window;

	float current_frame = 0.0f;
	float last_frame = 0.0f;
	float delta_time = 0.0f;

	void initialize();
	void mainloop();
	void cleanup();
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_cursor_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void APIENTRY debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
