#pragma once

#include "kwee/graphics/Shader.h"
#include "kwee/graphics/Texture.h"
#include "kwee/graphics/Mesh.h"

#include <vector>
#include <string>
#include <memory>

namespace kwee
{
    class ResourceManager
    {
    public:
		ResourceManager();
		~ResourceManager();

        static void loadShader(const std::string vertexShaderFilePath, const std::string fragmentShaderFilePath, const std::string resourceName);
        static void loadTexture(const std::string textureFilePath, const std::string resourceName);

        static std::shared_ptr<Shader> getShader(const std::string resourceName);
        static std::shared_ptr<Texture> getTexture(const std::string resourceName);
        static std::shared_ptr<Mesh> getMesh();

    private:
        static std::shared_ptr<Shader> compileShader_(const std::string vertexShaderCode, const std::string fragmentShaderCode);

    private:
        static std::vector<std::pair<std::string, std::shared_ptr<Shader>>> shaders_;
        static std::vector<std::pair<std::string, std::shared_ptr<Texture>>> textures_;
        static std::shared_ptr<Mesh> mesh_;
    };
}