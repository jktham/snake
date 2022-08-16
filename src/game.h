#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Game
{
public:
	int id;
	glm::ivec2 size = glm::ivec2(200, 200);
	glm::ivec2 position = glm::ivec2(0, 0);

	GLuint shader;
	GLuint vao;
	GLuint vbo;
	
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	std::vector<float> verts;

	void init();
	void update();
	void upload();
	void draw();
};
