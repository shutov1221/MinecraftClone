#include "ShaderCollection.h"

ShaderCollection* ShaderCollection::instance = nullptr;
std::array<Shader*, (int)ShaderType::SIZE> ShaderCollection::shaders = { nullptr };


void ShaderCollection::Create() {
    if (ShaderCollection::instance == nullptr) {
        ShaderCollection::instance = new ShaderCollection();
    }
}

Shader* ShaderCollection::GetShader(ShaderType shaderType) {
    if (instance == nullptr) {
        return nullptr;
    }

    return shaders[(int)shaderType];
}

ShaderCollection::~ShaderCollection() {
    for (auto& shader : shaders) {
        delete shader;
    }
}

ShaderCollection::ShaderCollection() {
    shaders[(int)ShaderType::MeshNonTransparentShader] = loadShader("res/shaders/non_transparent_blocks_vertex.glsl", "res/shaders/non_transparent_blocks_fragment.glsl");
    shaders[(int)ShaderType::MesTransparentShader] = loadShader("res/shaders/transparent_blocks_vertex.glsl", "res/shaders/transparent_blocks_fragment.glsl");
    shaders[(int)ShaderType::DepthMapShader] = loadShader("res/shaders/shadow_mapping_vertex.glsl", "res/shaders/shadow_mapping_fragment.glsl");
    shaders[(int)ShaderType::SSAOGeometryShader] = loadShader("res/shaders/ssao_geometry_vertex.glsl", "res/shaders/ssao_geometry_fragment.glsl");
    shaders[(int)ShaderType::SSAOShader] = loadShader("res/shaders/ssao_vertex.glsl", "res/shaders/ssao_fragment.glsl");
    shaders[(int)ShaderType::SSAOBlurShader] = loadShader("res/shaders/ssao_vertex.glsl", "res/shaders/ssao_blur_fragment.glsl");
}
