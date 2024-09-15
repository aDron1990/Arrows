#pragma once

#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"

#include <memory>

namespace engine
{
    class Sprite
    {
    public:
        Sprite(std::shared_ptr<kwee::Texture> texture, kwee::Texture::Region textureRegion);
        std::shared_ptr<kwee::Texture> getTexture();
        kwee::Texture::Region getTextureRegion();

    private:
        std::shared_ptr<kwee::Texture> texture_;
        kwee::Texture::Region textureRegion_;
    };
}