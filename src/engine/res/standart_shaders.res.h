#pragma once

#include <string>

char colored_v_str[] =
"#version 330 core\n" 
"layout (location = 0) in vec2 position;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"\tgl_Position = projection * view * model * vec4(position.x, position.y, 0.0f, 1.0f);\n"
"}";

char colored_f_str[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"uniform float alpha;\n"
"void main()\n"
"{\n"
"\tFragColor = vec4(color, alpha);\n"
"}";

char textured_v_str[] =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec2 aTexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"\tgl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0f, 1.0f);\n"
"\tTexCoord = aTexCoord;\n"
"}";

char textured_f_str[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform vec3 color;\n"
"uniform sampler2D ourTexture;\n"
"uniform float mixval;\n"
"uniform float alpha;\n"
"void main()\n"
"{\n"
"\tFragColor = mix(texture(ourTexture, TexCoord), vec4(color, alpha), mixval);\n"
"}";

char collider_v_str[] =
"#version 330 core\n"
"layout (location = 0) in vec2 position;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"\tgl_Position = projection * view * model * vec4(position.x, position.y, 0.0f, 1.0f);\n"
"}";

char collider_f_str[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"\tFragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}";