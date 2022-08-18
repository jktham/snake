#include "menu.h"
#include "ui.h"
#include "global.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <fstream>

void Menu::init()
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
	projection = glm::ortho(0.0f, app.size.x, app.size.y, 0.0f, -1.0f, 1.0f);

	Quad* quad = new Quad;
	quad->position = glm::vec2(100, 100);
	quad->size = glm::vec2(100, 100);
	elements.push_back(quad);
}

void Menu::updateState()
{

}

void Menu::updateMesh()
{
	mesh = {};

	size.y = app.size.y;

	glm::vec4 mcol = glm::vec4(0.0f, 0.0f, 0.0f, 0.8f);

	std::vector<float> menu_mesh = {
		0.0f,   0.0f,	mcol.r, mcol.g, mcol.b, mcol.a,
		0.0f,   size.y, mcol.r, mcol.g, mcol.b, mcol.a,
		size.x, size.y, mcol.r, mcol.g, mcol.b, mcol.a,
		0.0f,   0.0f,	mcol.r, mcol.g, mcol.b, mcol.a,
		size.x, size.y, mcol.r, mcol.g, mcol.b, mcol.a,
		size.x, 0.0f, 	mcol.r, mcol.g, mcol.b, mcol.a
	};
	mesh.insert(mesh.end(), menu_mesh.begin(), menu_mesh.end());

	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->generateMesh();
		mesh.insert(mesh.end(), elements[i]->mesh.begin(), elements[i]->mesh.end());
	}

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(app.size.x - size.x, 0.0f, 0.0f));
}

void Menu::updateVAO()
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

void Menu::draw()
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
