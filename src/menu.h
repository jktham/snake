#pragma once

#include "ui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Menu
{
public:
	glm::vec2 size = glm::vec2(400, 0);

	GLuint shader;
	GLuint vao;
	GLuint vbo;
	
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	std::vector<float> mesh;

	std::vector<Element*> elements;
	
	void init();
	void updateState();
	void updateMesh();
	void updateVAO();
	void draw();
};
