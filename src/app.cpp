#include "app.h"
#include "global.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

void App::setup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	window = glfwCreateWindow(size.x, size.y, "snake", NULL, NULL);
	glfwSetWindowPos(window, 100, 100);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, size.x, size.y);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_cursor_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(1.0f);
	glPointSize(1.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debug_callback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	init();
}

void App::mainloop()
{
	while (!glfwWindowShouldClose(window))
	{
		if ((float)glfwGetTime() - last_tick >= 1.0f / tick_rate)
		{
			current_tick = (float)glfwGetTime();
			delta_tick = current_tick - last_tick;
			last_tick = current_tick;

			std::cout << "dt: "<< delta_tick << "\n";

			updateState();
		}

		if ((float)glfwGetTime() - last_frame >= 1.0f / frame_rate)
		{
			current_frame = (float)glfwGetTime();
			delta_frame = current_frame - last_frame;
			last_frame = current_frame;

			std::cout << "df: " << delta_frame << "\n";

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			menu.updateState();
			updateMesh();
			updateVAO();
			draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
}

void App::cleanup()
{
	glfwTerminate();
}

void App::init()
{
	games = {};

	for (int i = 0; i < game_count; i++)
	{
		Game game;
		games.push_back(game);
	}

	for (int i = 0; i < games.size(); i++)
	{
		games[i].id = i;
		games[i].init();
	}

	Menu m;
	menu = m;
	menu.init();

	paused = true;
}

void App::reset()
{
	games = {};
	init();
}

void App::pause()
{
	paused = !paused;
}

void App::updateState()
{
	for (int i = 0; i < games.size(); i++)
	{
		games[i].updateState();
	}
	//menu.updateState();
}

void App::updateMesh()
{
	for (int i = 0; i < games.size(); i++)
	{
		games[i].updateMesh();
	}
	menu.updateMesh();
}

void App::updateVAO()
{
	for (int i = 0; i < games.size(); i++)
	{
		games[i].updateVAO();
	}
	menu.updateVAO();
}

void App::draw()
{
	for (int i = 0; i < games.size(); i++)
	{
		games[i].draw();
	}
	menu.draw();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		app.reset();
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		app.pause();
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		if (app.games[0].last_move_dir != glm::ivec2(0, 1))
		{
			app.games[0].move_dir = glm::ivec2(0, -1);
		}
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		if (app.games[0].last_move_dir != glm::ivec2(1, 0))
		{
			app.games[0].move_dir = glm::ivec2(-1, 0);
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		if (app.games[0].last_move_dir != glm::ivec2(0, -1))
		{
			app.games[0].move_dir = glm::ivec2(0, 1);
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		if (app.games[0].last_move_dir != glm::ivec2(-1, 0))
		{
			app.games[0].move_dir = glm::ivec2(1, 0);
		}
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		app.click = true;
	}
	else
	{
		app.click = false;
	}
}

void mouse_cursor_callback(GLFWwindow *window, double pos_x, double pos_y)
{
	app.cursor = glm::vec2((float)pos_x, (float)pos_y);
}

void mouse_scroll_callback(GLFWwindow *window, double offset_x, double offset_y)
{
	app.scroll += offset_y;
	if (app.scroll > 0.0f)
	{
		app.scroll = 0.0f;
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	app.size = glm::vec2(width, height);

	glViewport(0, 0, app.size.x, app.size.y);
	for (int i = 0; i < app.games.size(); i++)
	{
		app.games[i].projection = glm::ortho(0.0f, app.size.x, app.size.y, 0.0f, -1.0f, 1.0f);
	}
	app.menu.projection = glm::ortho(0.0f, app.size.x, app.size.y, 0.0f, -1.0f, 1.0f);
}

void APIENTRY debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "Source: API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "Source: Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "Source: Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "Source: Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "Source: Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "Source: Other";
		break;
	}
	std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "Type: Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "Type: Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "Type: Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "Type: Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "Type: Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "Type: Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "Type: Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "Type: Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "Type: Other";
		break;
	}
	std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "Severity: high";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Severity: medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Severity: low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Severity: notification";
		break;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
