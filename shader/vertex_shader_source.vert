#version 330 core
    layout(location = 0) in vec3 inPos;
    layout(location = 1) in vec3 inColor;
    layout(location = 2) in vec2 inTexPos;
    out vec4 out_color;
    out vec2 out_texpos;

void main() { gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0f);
  out_color = vec4(inColor,1.0f);
  out_texpos = inTexPos;
  }
