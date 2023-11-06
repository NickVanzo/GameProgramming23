#pragma once

#include "Engine/Component.h"
#include "../costants/Costants.h"

/**
 * To setup correctly the tiles in the JSON file keep in mind this:
 *    you need to specify just even numbers, this is because the number selected is the tile in "light" mode, while
 *    the tile in "shadow" is the next selected + 1
 *    Example: I want to render the blue wall with the skeleton, it's position is: 14
 * You can render directly the shadows tiles but that would mix the tiles.
 *    Example: I want to render the blue wall with the skeleton shadowed, It's position is: 15 but then
 *    in this case it's actual shadow becomes the empty blue wall at 16
 *
 *  When you edit the JSON file update the ROWS and COLUMNS variables in the costants header
 */
class ComponentRendererMesh : public MyEngine::Component {
public:
	void Init(rapidjson::Value& serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass& renderPass) override;
private:
    void SetupLayoutFromJSON(rapidjson::Value &serializedData);
    void CreateFacesInLight(float, int, int);
    void CreateFacesInShadow(float, int, int);
    std::vector<glm::vec4> CalculateUvs(float posX, float posY);
    int _layout[MyEngine::ROWS][MyEngine::COLUMNS];
    std::shared_ptr<sre::Mesh> _meshes[MyEngine::ROWS][MyEngine::COLUMNS];
    std::shared_ptr<sre::Mesh> _darkMeshes[MyEngine::ROWS][MyEngine::COLUMNS];

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