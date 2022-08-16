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

	glm::ivec2 size = glm::ivec2(200, 200);
	glm::ivec2 position = glm::ivec2(0, 0);
	glm::ivec2 border = glm::ivec2(10, 10);

	glm::ivec2 grid_size = glm::ivec2(20, 20);
	glm::ivec2 fruit_pos = glm::ivec2(0, 0);
	std::deque<glm::ivec2> snake_pos;
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
	void updateGame();
	void updateMesh();
	void updateVAO();
	void draw();
};
