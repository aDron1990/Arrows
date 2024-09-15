#pragma once

#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"
#include "kwee/graphics/Mesh.h"

#include <string>
#include <memory>

namespace kwee
{
    class ResourceManager
    {
    public:
        virtual void loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName) = 0;
        virtual void loadTexture(const std::string textureFilePath, const std::string resourceName) = 0;
        virtual std::shared_ptr<Shader> getShader(const std::string resourceName) = 0;
        virtual std::shared_ptr<Texture> getTexture(const std::string resourceName) = 0;
        virtual std::shared_ptr<Mesh> getMesh() = 0;

    protected:
        ~ResourceManager() = default;
    };
}