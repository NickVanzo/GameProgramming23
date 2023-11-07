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

//    rapidjson::StringBuffer buffer;
//    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
//
//    // Serialize the `serializedData` to a JSON string
//    serializedData.Accept(writer);
//
//    // Print the JSON string to the console
//    std::cout << buffer.GetString() << std::endl;
}

void ComponentController::SetBirdValuesFromJSON(rapidjson::Value &serializedData) {
    if(JSONIsValid(serializedData)) {
        SetValuesFromJSON(serializedData);
    } else {
        SetDefaultValues();
    }
}

bool ComponentController::JSONIsValid(rapidjson::Value &serializedData) {
    return(
            serializedData.HasMember("movSpeed")
            && serializedData.HasMember("rotSpeed")
            && serializedData.HasMember("impulseForce")
            );
}

void ComponentController::SetValuesFromJSON(rapidjson::Value &serializedData) {
    cout << "Setting velocity at "<< mov_speed << " and rotation at "<< rot_speed <<" speed of bird" << endl;
    mov_speed = serializedData["movSpeed"].GetFloat();
    rot_speed = serializedData["rotSpeed"].GetFloat();
    impulseForce = serializedData["impulseForce"].GetFloat();
}

void ComponentController::SetDefaultValues() {
    cout << "Something went wrong while reading from the json. Setting bird variables to default" << endl;
    mov_speed = 1;
    rot_speed = 1;
    impulseForce = 400;
}


void ComponentController::Update(float deltaTime) {
    SetLinearVelocity(mov_speed);
}

void ComponentController::SetLinearVelocity(float velocityAlongTheX) {
    if(!linearVelocitySet) {
        linearVelocitySet = true;
        cout << "Setting the linear velocity of the bird" << endl;
        auto physicsComponent = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>();
        if(physicsComponent.lock()) {
            physicsComponent.lock()->setLinearVelocity(*new vec2(velocityAlongTheX, 0));
        } else {
            cout << "Something went wrong while setting the linear velocity of the game object" << endl;
        }
    }
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
        auto* impulseVector = new bvec2(0, impulseForce);
        physicsComponent.lock()->addImpulse(*impulseVector);
    }
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
    // TODO gameOver on touching pipes, despawn coins
}
