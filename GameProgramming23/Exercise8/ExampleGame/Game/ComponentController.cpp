#include "ComponentController.h"
#include "glm/glm.hpp"
#include "SDL.h"
#include "Engine/Components/ComponentPhysicsBody.h"
#include "glm/gtx/matrix_decompose.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using namespace std;
using namespace glm;
using namespace rapidjson;

void ComponentController::Init(rapidjson::Value& serializedData) {
    // TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`

    SetBirdValuesFromJSON(serializedData);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    // Serialize the `serializedData` to a JSON string
    serializedData.Accept(writer);

    // Print the JSON string to the console
    std::cout << buffer.GetString() << std::endl;
}

void ComponentController::SetBirdValuesFromJSON(rapidjson::Value &serializedData) {
    if(serializedData.HasMember("movSpeed") && serializedData.HasMember("rotSpeed")) {
        mov_speed = serializedData["movSpeed"].GetFloat();
        rot_speed = serializedData["rotSpeed"].GetFloat();
        impulseForce = serializedData["impulseForce"].GetFloat();
        cout << "Setting velocity at "<< mov_speed << " and rotation at "<< rot_speed <<" speed of bird" << endl;
    }
}

void ComponentController::Update(float deltaTime) {
    Move(deltaTime);
}

void ComponentController::Move(float deltaTime) {
    vec3 v = glm::vec3(mov_speed, 0,  0);
    mat4 translation = translate(mat4(1.0), v * deltaTime);
    GetGameObject().lock()->transform = translation * GetGameObject().lock()->transform;
}

void ComponentController::KeyEvent(SDL_Event& event)
{
    auto keyPressed =  event.key.keysym.scancode;
    if(keyPressed == SDL_SCANCODE_SPACE) {
        ApplyImpulse();
    }
}

void ComponentController::ApplyImpulse() {
    auto physicsComponent = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>();
    if(physicsComponent.lock()) {
        physicsComponent.lock()->addImpulse(*new bvec2(0, impulseForce));
    }
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
    // TODO gameOver on touching pipes, despawn coins
}
