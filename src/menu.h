#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Menu
{
public:
	int width = 400;

	GLuint shader;
	GLuint vao;
	GLuint vbo;
	
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	std::vector<float> mesh;
	
	void init();
	void updateState();
	void updateMesh();
	void updateVAO();
	void draw();
};
