#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <assert.h>
#include <chrono>
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ShaderHelper.h"
#define BUFFER_OFFSET(i) ((GLvoid *)(i*sizeof(float)))

// Constants for program
GLuint program, VAO, VBO, aPositionLocation, aColorLocation, currentTimeLocation;
const int numVerts = 6;
const int numComponents = 3;
const int vertArraySize = numVerts * numComponents;

// Creates vertices for a regular hexagon
static std::array<GLfloat, vertArraySize> createVertices()
{
	std::array<GLfloat, vertArraySize> vertices;

	for (int i = 0; i < numVerts * numComponents; i += numComponents)
	{
		vertices[i]     = static_cast<GLfloat>(std::cos(2 * M_PI * i / vertArraySize));
		vertices[i + 1] = static_cast<GLfloat>(std::sin(2 * M_PI * i / vertArraySize));
		vertices[i + 2] = 0.0f;
	}

	return vertices;
}

// Get the location handle for current time in the shader
static void getUniformLocation() {
	currentTimeLocation = glGetUniformLocation(program, "currentTime");
	assert(currentTimeLocation != 0xFFFFFFFF);
}

// Main render function
static void RenderSceneCB()
{
	GLfloat currentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	currentTime = currentTime / 1000.0f;
	glUniform1f(currentTimeLocation, currentTime);

	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POLYGON, 0, numVerts);
	glBindVertexArray(0);
	glutSwapBuffers();
}

// Update simply triggers window to redisplay
static void update() {
	glutPostRedisplay();
}

// Setup the callbacks for Free Glut (render and update loops)
static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(update);
}

// Create, setup and fill the vertex buffer object on the GPU.
// Using hard coded location indices (must also be configured in the shader)
void createVBOForLocation() {
	std::array<GLfloat, vertArraySize> vertices = createVertices();
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, numComponents * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, numComponents * sizeof(float), BUFFER_OFFSET(3));
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}

// Create, setup and fill the Vertex Buffer Object on the GPU.
// Using named locations from the shader
void createVBOForAttributes(){ 
	std::array<GLfloat, vertArraySize> vertices = createVertices();
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	aPositionLocation = glGetAttribLocation(program, "position");
	glVertexAttribPointer(aPositionLocation, 3, GL_FLOAT, GL_FALSE, numComponents * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(aPositionLocation);

	//aColorLocation = glGetAttribLocation(program, "color");
	//glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, numComponents * sizeof(float), BUFFER_OFFSET(3));
	//glEnableVertexAttribArray(aColorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}

// Wrapper around VBO creation to associate the VBO with its own Vertex Array Object (VAO)
void createVAOWithVBO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	createVBOForAttributes();

	glBindVertexArray(0);
}

int main(int argc, char **argv) {
	// Setup window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Triangle");
	
	// Setup render and update loops
	InitializeGlutCallbacks();

	// Bind OpenGL functions
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cout << "Error: ," << glewGetErrorString(res);
		return 1;
	}

	// Setup shaders
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	ShaderHelper::compileAndLinkShaders("vertex_shader.glsl", "fragment_shader.glsl", program);
	createVAOWithVBO();
	getUniformLocation();
	glUseProgram(program);

	// Start main loop
	glutMainLoop();

	return 0;
}