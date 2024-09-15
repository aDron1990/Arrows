#pragma once

#include "kwee/systems/ResourceManager.h"
#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"
#include "kwee/graphics/Mesh.h"

#include <vector>
#include <string>
#include <memory>

namespace kwee
{
    class ResourceManagerBase : public ResourceManager
    {
    public:
        ResourceManagerBase();
        void loadStandartResources();
        void loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName) override;
        void loadTexture(const std::string textureFilePath, const std::string resourceName) override;
        std::shared_ptr<Shader> getShader(const std::string resourceName) override;
        std::shared_ptr<Texture> getTexture(const std::string resourceName) override;
        std::shared_ptr<Mesh> getMesh() override;

    private:
        std::shared_ptr<Shader> compileShader_(const std::string vertexShaderCode, const std::string fragmentShaderCode);

    private:
        std::vector<std::pair<std::string, std::shared_ptr<Shader>>> shaders_;
        std::vector<std::pair<std::string, std::shared_ptr<Texture>>> textures_;
        std::shared_ptr<Mesh> mesh_;
    };
}