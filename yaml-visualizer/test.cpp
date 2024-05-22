#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

void resize(GLFWwindow *window, int width, int height);
void input(GLFWwindow *window);
void cursor(GLFWwindow *window, double xpos, double ypos);

const unsigned int WIDTH = 500;
const unsigned int HEIGHT = 500;

float x = 0.0;
float y = 0.0;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "test", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Couldn't load window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, resize);
  glfwSetCursorPosCallback(window, cursor);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Couldn't load GLAD" << std::endl;
    return -1;
  }

  Shader shader("tests/shaders/vertex.vert", "tests/shaders/fragment.frag");

  float vertices[] = {
      // first triangle
      -1.0f, 1.0f, 0.0f,  // left
      1.0f, 1.0f, 0.0f,   // right
      -1.0f, -1.0f, 0.0f, // top
                          // second triangle
      -1.0f, -1.0f, 0.0f, // left
      1.0f, 1.0f, 0.0f,   // right
      1.0f, -1.0f, 0.0f   // top
  };

  unsigned int vertexBufferObject, vertexArrayObject;
  glGenVertexArrays(1, &vertexArrayObject);
  glGenBuffers(1, &vertexBufferObject);

  glBindVertexArray(vertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window))
  {
    input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int timeLocation = shader.getLocation("u_time");
    glUniform1f(timeLocation, glfwGetTime());

    int resolutionLocation = shader.getLocation("u_resolution");
    glUniform2f(resolutionLocation, (float)WIDTH, (float)HEIGHT);

    int cursorLocation = shader.getLocation("u_mouse");
    glUniform2f(cursorLocation, x, y);

    shader.use();

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vertexArrayObject);
  glDeleteBuffers(1, &vertexBufferObject);

  glfwTerminate();
  return 0;
}

void input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void cursor(GLFWwindow *window, double xpos, double ypos)
{
  x = xpos;
  y = ypos;
}

void resize(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}