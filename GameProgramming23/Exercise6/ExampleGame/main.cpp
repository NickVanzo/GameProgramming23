#include "sre/SpriteAtlas.hpp"

#include "../Engine/Engine/MyEngine.h"
#include "../Engine/Engine/ComponentFactory.h"

#include "Game/ComponentCamera.h"
#include "Game/ComponentRendererMesh.h"
#include "Game/ComponentController.h"
#include "Game/LevelLayoutManager/LevelLayoutManager.h"

MyEngine::Engine engine;
std::shared_ptr<sre::SpriteAtlas> atlas;
std::shared_ptr<LevelLayoutManager> lvlManager;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER", std::make_shared<ComponentController>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CAMERA", std::make_shared<ComponentCamera>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CUBE_RENDERER", std::make_shared<ComponentRendererMesh>());
	engine.Init("../../../../GameProgramming23/Exercise6/ExampleGame/data/scene.json");
}
