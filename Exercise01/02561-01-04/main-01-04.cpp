// 02561-01-04

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Angel.h"

using namespace std;
using namespace Angel;

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

GLuint shaderProgram;
GLuint projectionUniform,
	modelViewUniform;
GLuint positionAttribute;
GLuint vertexArrayObject;

const GLfloat DEG_TO_RAD = M_PI / 180.0;

struct Vertex {
	vec2 position;
};

struct CircleVertexData {
	GLuint numVertices;
	std::vector<Vertex> cirleVertexData;
};

std::vector<Vertex> cirleVertexData;

// forward declaration
void loadShader();
void display();
void loadBufferData();
void reshape(int W, int H);
void loadGeometry();
std::vector<Vertex> createCircleGeometry(GLfloat radius, vec2 origin, GLuint segments);

void display() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);

	mat4 projection = Ortho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(projectionUniform, 1, GL_TRUE, projection);

	mat4 modelView;
    glUniformMatrix4fv(modelViewUniform, 1, GL_TRUE, modelView);

	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLE_FAN, 0, cirleVertexData.size());

	glutSwapBuffers();

	Angel::CheckError();
}

void reshape(int W, int H) {
	WINDOW_WIDTH = W;
	WINDOW_HEIGHT = H;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void loadGeometry() {
	cirleVertexData = createCircleGeometry(0.8, vec2(0.0f, 0.0f), 50);
}

std::vector<Vertex> createCircleGeometry(GLfloat radius, vec2 origin, GLuint segments) {
	std::vector<Vertex> vertices;

	GLfloat segAngle = (2 * M_PI) / segments;
	printf("%f %d", segAngle, segments);
	for (int i = 0; i < segments; i++) {
		vertices.push_back({
				vec2(cos(i * segAngle) * radius + origin.x,
					 sin(i * segAngle) * radius + origin.y )
		});
	}
	return vertices;
}

void loadBufferData() {
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	GLuint  vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, cirleVertexData.size() * sizeof(Vertex), &cirleVertexData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(positionAttribute);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)0);
}

void loadShader() {
	shaderProgram = InitShader("const-shader.vert",  "const-shader.frag", "fragColor");
	projectionUniform = glGetUniformLocation(shaderProgram, "projection");
	if (projectionUniform == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'projection' uniform."<<endl;
	}
	modelViewUniform = glGetUniformLocation(shaderProgram, "modelView");
	if (modelViewUniform == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'modelView' uniform."<<endl;
	}
	positionAttribute = glGetAttribLocation(shaderProgram, "position");
	if (positionAttribute == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'position' attribute." << endl;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_3_2_CORE_PROFILE);
	glutCreateWindow("02561-01-04");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	Angel::InitOpenGL();

	loadShader();
	loadGeometry();
	loadBufferData();

	Angel::CheckError();

	glutMainLoop();
}
