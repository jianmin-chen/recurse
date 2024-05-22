#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "yaml.h"
#include "shader.h"

void resize(GLFWwindow *window, int width, int height);
void input(GLFWwindow *window);
void cursor(GLFWwindow *window, double xpos, double ypos);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main(int argc, char *argv[])
{
  bool debug = false;
  if (argc > 1 && !strcmp(argv[1], "--debug"))
    debug = true;

  YAML yaml("tests/kv.yaml");
  yaml.process();
  if (debug)
  {
    std::ofstream file("tokens.json");
    if (!file.is_open())
    {
      std::cout << "ERROR::DEBUG::WRITE_FAILED" << std::endl;
      return -1;
    }

    file << "[";
    for (auto i = 0; i < yaml.lexer.tokens.size(); i++)
    {
      file << yaml.lexer.tokens[i];
      if (i != yaml.lexer.tokens.size() - 1)
        file << ", ";
    }
    file << "]";

    file.close();
  }

  return 0;
}

void input(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void cursor(GLFWwindow *window, double xpos, double ypos)
{
}

void resize(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}