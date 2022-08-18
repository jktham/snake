#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <functional>

class Element
{
public:
	glm::vec2 size = glm::vec2(0.0f, 0.0f);
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	std::vector<float> mesh = {};

	std::function<void()> action = [](){};

	virtual void hover();
	virtual void click();
	virtual void reset();

	virtual void generateMesh();
};

class Quad: public Element
{
public:
	virtual void generateMesh();
};

class Button: public Element
{
public:
	virtual void hover();
	virtual void click();
	virtual void reset();

	virtual void generateMesh();
};