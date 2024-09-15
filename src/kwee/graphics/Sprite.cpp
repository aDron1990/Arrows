#include "kwee/graphics/Sprite.h"

engine::Sprite::Sprite(std::shared_ptr<kwee::Texture> texture, kwee::Texture::Region textureRegion) : texture_{texture}, textureRegion_{textureRegion} {}

std::shared_ptr<kwee::Texture> engine::Sprite::getTexture()
{
    return texture_;
}

kwee::Texture::Region engine::Sprite::getTextureRegion()
{
    return textureRegion_;
}