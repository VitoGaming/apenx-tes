#include "src/graphics/Window.h"
#include "src/graphics/shader/Shader.h"
#include "src/utils/MathUtils.h"
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <string>

int main()
{
	using namespace std;
	using namespace glm;
	using namespace apenx;
	using namespace graphics;
	using namespace utils;

	Window window("Apenx! (Test Build 01)", 800, 600);
	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

	GLuint vbo;

	GLfloat vertices[] = {
		7, 8, 0,
		7, 5, 0,
		10, 5, 0,

		7, 8, 0,
		10, 5, 0,
		10, 8, 0
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	mat4 transform;
	mat4 modelMatrix = glm::rotate(mat4(1.0), radians(45.0f), vec3(0, 0, 1));
	Shader shader("src/shaders/shader.vert", "src/shaders/shader.frag");
	shader.enable();
	shader.setUnifromMat4("pr_matrix", ortho);
	//shader.setUnifromMat4("vw_matrix", translate(vec3(0, 0, 0)));
	shader.setUnifromMat4("ml_matrix", modelMatrix);

	while (!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getGLFWWindow(), GL_TRUE);
		}

		window.update();
	}

	return 0;
}