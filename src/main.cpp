// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on
#include <array>
#include <iostream>

void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processKeyPress(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, char **argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  auto window = glfwCreateWindow(800, 600, "111", nullptr, nullptr);
  if (!window) {
    std::cout << "window create error!" << "\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "load glproc failed!" << "\n";
    return -1;
  }
  glViewport(0, 0, 800, 600); // 不是glfw窗口坐标系坐标,会自动对齐
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

  std::array<float, 9> triangle_vtx{-0.5f, -0.5f, 0.0f, 0.}

  while (!glfwWindowShouldClose(window)) {
    processKeyPress(window);
    glClearColor(0.8f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();

  return 0;
  e
}
