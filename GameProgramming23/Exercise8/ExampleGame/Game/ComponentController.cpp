#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "Engine/Components/ComponentPhysicsBody.h"
#include "glm/gtx/matrix_decompose.hpp"

using namespace std;
using namespace glm;
using namespace rapidjson;

void ComponentController::Init(rapidjson::Value& serializedData) {
    // TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
    ReadJSON(serializedData);
}

void ComponentController::ReadJSON(rapidjson::Value &serializedData) {
    if(serializedData.HasMember("movSpeed") && serializedData.HasMember("rotSpeed")) {
        mov_speed = serializedData["movSpeed"].GetFloat();
        rot_speed = serializedData["rotSpeed"].GetFloat();
    }
}

void ComponentController::Update(float deltaTime) {
	Move(deltaTime);
}

void ComponentController::Move(float deltaTime) {
    vec3 v = glm::vec3(10.0f, 0,  0);
    GetGameObject().lock()->transform = translate(GetGameObject().lock()->transform, v * deltaTime);
}

void ComponentController::KeyEvent(SDL_Event& event)
{
    auto keyPressed =  event.key.keysym.scancode;
    if(keyPressed == SDL_SCANCODE_SPACE) {
        ApplyImpulse();
    }
}

void ComponentController::ApplyImpulse() {}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}