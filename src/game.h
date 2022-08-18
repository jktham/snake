#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <deque>

class Game
{
public:
	int id;

	glm::vec2 size = glm::vec2(200, 200);
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 border = glm::vec2(10, 10);

	glm::ivec2 grid_size = glm::ivec2(20, 20);
	glm::ivec2 fruit_pos = glm::ivec2(0, 0);
	std::deque<glm::ivec2> snake_pos = {glm::ivec2(0, 0)};
	glm::ivec2 move_dir = glm::ivec2(0, 0);
	glm::ivec2 last_move_dir = glm::ivec2(0, 0);
	int points = 0;
	bool dead = false;
	bool grow = false;

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
