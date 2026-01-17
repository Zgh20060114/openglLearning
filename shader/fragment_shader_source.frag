  #version 330 core
  out vec4 out_pixel_color;
  in vec4 out_color;
  in vec2 out_texpos;
  uniform sampler2D out_tex1;
  uniform sampler2D out_tex2;
  void main(){
    // out_pixel_color = out_color;
    // out_pixel_color = texture(out_tex1,out_texpos) * out_color;
    out_pixel_color = mix(texture(out_tex1,out_texpos), texture(out_tex2,out_texpos), 0.5);
  }
