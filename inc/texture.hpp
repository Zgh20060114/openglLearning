#include <compare>
#include <filesystem>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
public:
  Texture(std::filesystem::path path, GLint wrap_s = GL_REPEAT,
          GLint wrap_t = GL_REPEAT, GLint min_filter = GL_NEAREST,
          GLint mag_filter = GL_NEAREST)
      : tex_id(0), width(0), height(0), color_channel(0) {
    stbi_set_flip_vertically_on_load(true);
    auto data = stbi_load(path.c_str(), &width, &height, &color_channel, 0);
    if (!data) {
      throw std::runtime_error("stb failed to load png!");
    }

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    if (color_channel == 3) {
      internal_format = GL_RGB;
      data_format = GL_RGB;
    } else if (color_channel == 4) {
      internal_format = GL_RGBA;
      data_format = GL_RGBA;
    } else {
      internal_format = GL_RED;
      data_format = GL_RED;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0,
                 data_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
  }
  ~Texture() {
    if (tex_id != 0) {
      glDeleteTextures(1, &tex_id);
    }
  }
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  Texture(Texture &&) = delete;
  Texture &operator=(Texture &&) = delete;

  void bind(GLenum tex_unit) {
    glActiveTexture(tex_unit);
    glBindTexture(GL_TEXTURE_2D, tex_id);
  }
  static void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

private:
  GLuint tex_id;
  int width;
  int height;
  int color_channel;
  GLint internal_format;
  GLint data_format;
};
