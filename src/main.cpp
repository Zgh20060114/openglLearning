// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

const std::string vertex_shader_source = R"(
#version 330 core
    layout(location = 0) in vec3 inPos;
    layout(location = 1) in vec3 inColor;
    out vec4 out_color;
void main() { gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0f);
  out_color = vec4(inColor,1.0f);
  }
)";

const std::string fragment_shader_source = R"(
  #version 330 core
  out vec4 out_pixel_color;
  in vec4 out_color;
  void main(){
  out_pixel_color = out_color;
  }
)";

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

  GLuint vao{}; // vao相当一台录像机,记录下了vbo储存数据,顶点数据属性配置
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // clang-format off
  std::array<float, 24> triangle_vtx{
    -0.5f, 0.5f, 0.0f, 1.0f,0.0f,0.0f,
    -0.5f, -0.5f,0.0f,0.0f,1.0f,0.0f,
    0.5f, -0.5f, 0.0f, 0.0f,0.0f,1.0f,
    0.5f,0.5f,  0.0f,1.0f,1.0f,1.0f,
  }; // 左上,左下, 右下,右上(带颜色)
  // clang-format on

  GLuint vbo{};          // vbo其实是个id
  glGenBuffers(1, &vbo); // 第一个参数是申请id的对象,第二个参数是存放id的地方
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vtx), triangle_vtx.data(),
               GL_STATIC_DRAW); // 数据首地址 // 将数据放入vbo中

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        static_cast<void *>(0));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        reinterpret_cast<void *>(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  std::array<int, 6> index{0, 1, 2, 0, 2, 3};
  GLuint ebo{};
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    processKeyPress(window);
    glClearColor(0.8f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    // auto time = glfwGetTime();
    // auto green_value = std::sin(time) / 2.0f + 0.5f;
    // auto u_loc = glGetUniformLocation(shader_program, "out_uniform_color");
    // glUniform4f(u_loc, 0.0f, green_value, 0.0f, 1.0f);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void *>(0));
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteBuffers(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteProgram(shader_program);
  glfwTerminate();

  return 0;
}
