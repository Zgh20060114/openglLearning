#pragma once

#include "glad/glad.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Shader {
public:
  explicit Shader(const std::filesystem::path &vertex_shader_path,
                  const std::filesystem::path &fragment_shader_path) {
    std::string vertex_shader_source = readFile(vertex_shader_path);
    std::string fragment_shader_source = readFile(fragment_shader_path);
    compileAndLinkShader(vertex_shader_source, fragment_shader_source);

  }
  void use() { glUseProgram(shader_program); }
  ~Shader() {
    if (shader_program != 0) {
      glDeleteProgram(shader_program);
    }
  }
  Shader(const Shader &other) = delete;
  Shader &operator=(const Shader &other) = delete;

  Shader(Shader &&other) {
    shader_program = other.shader_program;
    other.shader_program = 0; // 保证id不能重复
  }
  Shader &operator=(Shader &&other) {
    if (this != &other) {
      if (shader_program != 0) {
        glDeleteProgram(shader_program);
      }
      shader_program = other.shader_program;
      other.shader_program = 0;
    }
    return *this;
  }

private:
  GLuint shader_program{};

  std::string readFile(const std::filesystem::path &path) {
    if (!std::filesystem::exists(path)) {
      throw std::runtime_error("file not exists: " + path.string());
    }
    if (!std::filesystem::is_regular_file(path)) {
      throw std::runtime_error("not a regular file: " + path.string());
    }
    std::ifstream file(path);
    if (!file.is_open()) {
      throw std::runtime_error("can't open file: " + path.string());
    }
    std::stringstream ss{};
    ss << file.rdbuf(); // 想当于缓冲区水龙头
    return ss.str();
  }

  void compileAndLinkShader(const std::string &vss, const std::string &fss) {
    GLuint vshadero{};
    vshadero = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_shader_source_c =
        vss.c_str(); // 转化为char vertex_shader_source[]
    glShaderSource(vshadero, 1, &vertex_shader_source_c, 0);
    glCompileShader(vshadero); // glsl需要动态编译

    GLuint fshadero{};
    fshadero = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_shader_source_c = fss.c_str();
    glShaderSource(fshadero, 1, &fragment_shader_source_c, 0);
    glCompileShader(fshadero);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vshadero);
    glAttachShader(shader_program, fshadero);
    glLinkProgram(shader_program);

    GLint v_compile_success{};
    glGetShaderiv(vshadero, GL_COMPILE_STATUS, &v_compile_success);
    if (!v_compile_success) {
      // GLchar compile_infolog[512]{};
      GLint log_length{};
      glGetShaderiv(vshadero, GL_INFO_LOG_LENGTH, &log_length);
      std::vector<char> compile_infolog(log_length + 1); // 避免为空vec
      glGetShaderInfoLog(
          vshadero, log_length, 0,
          compile_infolog.data()); // 首元素地址,就是c风格的数组名
      std::cout << "Vertex Shader Compile Error: " << compile_infolog.data()
                << "\n";
    }

    GLint f_compile_success{};
    glGetShaderiv(fshadero, GL_COMPILE_STATUS, &f_compile_success);
    if (!f_compile_success) {
      // GLchar compile_infolog[512]{};
      GLint log_length{};
      glGetShaderiv(fshadero, GL_INFO_LOG_LENGTH, &log_length);
      std::vector<char> compile_infolog(log_length + 1); // 避免为空vec
      glGetShaderInfoLog(
          fshadero, log_length, 0,
          compile_infolog.data()); // 首元素地址,就是c风格的数组名
      std::cout << "Fragment Shader Compile Error: " << compile_infolog.data()
                << "\n";
    }
    GLint program_link_success{};
    glGetProgramiv(shader_program, GL_LINK_STATUS, &program_link_success);
    if (!program_link_success) {
      // GLchar compile_infolog[512]{};
      GLint log_length{};
      glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);
      std::vector<char> link_infolog(log_length + 1); // 避免为空vec
      glGetProgramInfoLog(shader_program, log_length, 0,
                          link_infolog.data()); // 首元素地址,就是c风格的数组名
      std::cout << "Shder Program Error: " << link_infolog.data() << "\n";
    }
    glDeleteShader(vshadero);
    glDeleteShader(fshadero);
  }
};
