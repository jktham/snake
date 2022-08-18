#include "ui.h"
#include "global.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Element::hover()
{
}

void Element::click()
{
}

void Element::reset()
{
}

void Element::generateMesh()
{
}

void Quad::generateMesh()
{
	mesh = {
		position.x,			 position.y,		  color.r, color.g, color.b, color.a,
		position.x,			 position.y + size.y, color.r, color.g, color.b, color.a,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a,
		position.x,			 position.y,		  color.r, color.g, color.b, color.a,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a,
		position.x + size.x, position.y,		  color.r, color.g, color.b, color.a
	};
}

void Button::hover()
{
	color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
}

void Button::click()
{
	color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
}

void Button::reset()
{
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Button::generateMesh()
{
	mesh = {
		position.x,			 position.y,		  color.r, color.g, color.b, color.a,
		position.x,			 position.y + size.y, color.r, color.g, color.b, color.a,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a,
		position.x,			 position.y,		  color.r, color.g, color.b, color.a,
		position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a,
		position.x + size.x, position.y,		  color.r, color.g, color.b, color.a
	};
}