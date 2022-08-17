#include "game.h"
#include "global.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <random>
#include <algorithm>
#include <vector>

void Game::init()
{
	const char *vert_source;
	std::ifstream vert_file("res/shaders/shader.vs");
	std::string vert_string((std::istreambuf_iterator<char>(vert_file)), std::istreambuf_iterator<char>());
	vert_source = vert_string.c_str();

	GLuint vert_shader;
	vert_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vert_shader, 1, &vert_source, NULL);
	glCompileShader(vert_shader);

	const char *frag_source;
	std::ifstream frag_file("res/shaders/shader.fs");
	std::string frag_string((std::istreambuf_iterator<char>(frag_file)), std::istreambuf_iterator<char>());
	frag_source = frag_string.c_str();

	GLuint frag_shader;
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(frag_shader, 1, &frag_source, NULL);
	glCompileShader(frag_shader);

	shader = glCreateProgram();
	glAttachShader(shader, vert_shader);
	glAttachShader(shader, frag_shader);
	glLinkProgram(shader);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)app.size.x, (float)app.size.y, 0.0f, -1.0f, 1.0f);
	
	mesh = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	fruit_pos = glm::ivec2(std::rand() % grid_size.x, std::rand() % grid_size.y);
	snake_pos = {glm::ivec2(0, 0)};
	if (fruit_pos == snake_pos[0])
	{
		fruit_pos = glm::ivec2(1, 0);
	}
	move_dir = glm::ivec2(1, 0);
}

void Game::start()
{
	paused = false;
}

void Game::updateState()
{
	if (dead || paused)
		return;

	snake_pos.push_front(snake_pos[0] + move_dir);
	last_move_dir = move_dir;

	if (snake_pos[0] == fruit_pos)
	{
		fruit_pos = glm::ivec2(std::rand() % grid_size.x, std::rand() % grid_size.y);
		points += 1;
		grow = true;
	}
	else
	{
		snake_pos.pop_back();
		grow = false;
	}

	if (snake_pos[0].x < 0 || snake_pos[0].x > grid_size.x - 1 || snake_pos[0].y < 0 || snake_pos[0].y > grid_size.y - 1 || std::count(snake_pos.begin(), snake_pos.end(), snake_pos[0]) > 1)
	{
		dead = true;
	}
}

void Game::updateMesh()
{	
	mesh = {};

	glm::vec2 cell = glm::vec2(1.0f) / glm::vec2(grid_size);

	glm::vec4 gcol = glm::vec4(0.0f, 0.0f, 0.0f, 0.8f);

	std::vector<float> grid_mesh = {
		0.0f, 0.0f, gcol.r, gcol.g, gcol.b, gcol.a,
		0.0f, 1.0f, gcol.r, gcol.g, gcol.b, gcol.a,
		1.0f, 1.0f, gcol.r, gcol.g, gcol.b, gcol.a,
		0.0f, 0.0f, gcol.r, gcol.g, gcol.b, gcol.a,
		1.0f, 1.0f, gcol.r, gcol.g, gcol.b, gcol.a,
		1.0f, 0.0f, gcol.r, gcol.g, gcol.b, gcol.a
	};
	mesh.insert(mesh.end(), grid_mesh.begin(), grid_mesh.end());

	glm::vec2 fpos = glm::vec2(fruit_pos) / glm::vec2(grid_size);
	glm::vec4 fcol = glm::vec4(0.0f, 1.0f, 0.0f, 0.8f);

	std::vector<float> fruit_mesh = {
		fpos.x, 		 fpos.y, 		  fcol.r, fcol.g, fcol.b, fcol.a,
		fpos.x, 		 fpos.y + cell.y, fcol.r, fcol.g, fcol.b, fcol.a,
		fpos.x + cell.x, fpos.y + cell.y, fcol.r, fcol.g, fcol.b, fcol.a,
		fpos.x, 		 fpos.y,		  fcol.r, fcol.g, fcol.b, fcol.a,
		fpos.x + cell.x, fpos.y + cell.y, fcol.r, fcol.g, fcol.b, fcol.a,
		fpos.x + cell.x, fpos.y,		  fcol.r, fcol.g, fcol.b, fcol.a
	};
	mesh.insert(mesh.end(), fruit_mesh.begin(), fruit_mesh.end());
	
	for (int i = 0; i < snake_pos.size(); i++)
	{
		glm::vec2 spos = glm::vec2(snake_pos[i]) / glm::vec2(grid_size);
		glm::vec4 scol = glm::vec4(1.0f, 1.0f, 1.0f, 0.8f);

		if (dead)
			scol = glm::vec4(1.0f, 0.0f, 0.0f, 0.8f);

		if (grow)
			scol = glm::vec4(0.0f, 0.0f, 1.0f, 0.8f);
		
		if (paused)
			scol = glm::vec4(0.5f, 0.5f, 0.5f, 0.8f);

		std::vector<float> snake_mesh = {
			spos.x, 		 spos.y, 		  scol.r, scol.g, scol.b, scol.a,
			spos.x, 		 spos.y + cell.y, scol.r, scol.g, scol.b, scol.a,
			spos.x + cell.x, spos.y + cell.y, scol.r, scol.g, scol.b, scol.a,
			spos.x, 		 spos.y,		  scol.r, scol.g, scol.b, scol.a,
			spos.x + cell.x, spos.y + cell.y, scol.r, scol.g, scol.b, scol.a,
			spos.x + cell.x, spos.y,		  scol.r, scol.g, scol.b, scol.a
		};
		mesh.insert(mesh.end(), snake_mesh.begin(), snake_mesh.end());
	}

	int columns = (app.size.x - border.x - app.menu.width) / (size.x + border.x);
	int x = id % columns;
	int y = id / columns;
	position = glm::ivec2(x * size.x + (x+1) * border.x, y * size.y + (y+1) * border.y);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
}

void Game::updateVAO()
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.size(), mesh.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Game::draw()
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(0);

	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.size() / 6);
	glBindVertexArray(0);
	glUseProgram(0);
}