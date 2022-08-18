#include "ui.h"
#include "global.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Element::generateMesh()
{
	mesh = {};
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