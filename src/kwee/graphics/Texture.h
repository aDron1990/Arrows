#pragma once

#include <vector>
#include <GL/glew.h>

namespace kwee
{
    class Texture
    {
    public:
        Texture(unsigned char* texture_str, int width, int height, int channels);
        ~Texture();
        void bind();

    public:
        struct Region
        {
            float top, bottom, left, right;
        };

    private:
        GLuint id_;
        int width_, height_;
    };
}