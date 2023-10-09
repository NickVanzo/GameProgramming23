#pragma once

#include "Engine/Component.h"

class ComponentRendererMesh : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass& renderPass) override;

private:
    void SetupLayoutFromJSON(rapidjson::Value &serializedData);
    void CreateMesh(float,float);
    std::vector<glm::vec4> CalculateUvs(float posX, float posY);
    static const int ROWS = 5;
    static const int COLUMNS = 4;
    int _layout[ROWS][COLUMNS];
    std::vector<std::shared_ptr<sre::Mesh>> _meshes;

	std::shared_ptr<sre::Mesh> _mesh;
	std::shared_ptr<sre::Material> _material;
	std::shared_ptr<sre::Texture> _texture;

	// this should be metadata of the texture, but we are keeping them here for simplicity
	// challenge: associate a json to each texture, with their metadata?
	const glm::vec2 textureSize = glm::vec2(1039, 389);
	const glm::vec2 tileSize = glm::vec2(64, 64);
	const glm::vec2 tileSizeWithBorder = glm::vec2(65, 65);

    std::vector<glm::vec3> positions = {
            glm::vec3(-.5, -.5, .5),
            glm::vec3(-.5, .5, .5),
            glm::vec3(.5, .5, .5),
            glm::vec3(.5, -.5, .5)
    };
	const std::vector<uint16_t> idxs = { 3, 1, 0, 3, 2, 1 };
};