#include "ComponentController.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/transform.hpp"
#include "SDL.h"
#include "MyEngine.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
    GetGameObject()->transform = glm::translate(glm::vec3(2,0,4));
}

void ComponentController::Update(float deltaTime) {
    if(velocity != 0) {
        glm::vec3 v = glm::vec3(0, 0, -velocity * friction * 10);
        GetGameObject()->transform = glm::translate(GetGameObject()->transform, v * deltaTime);
    }


    velocity = 0;
}

void ComponentController::KeyEvent(SDL_Event& event)
{
    glm::vec3 cameraForward = -glm::normalize(glm::vec3(GetGameObject()->transform[2]));
    auto keyPressed =event.key.keysym.scancode;
    if(keyPressed == SDL_SCANCODE_W) {
        velocity += 1;
    } else if(keyPressed == SDL_SCANCODE_S) {
        velocity -= 1;
    } else if(keyPressed == SDL_SCANCODE_D) {
        glm::vec3 yAxis = glm::vec3(0,1,0);
        float angle = glm::radians(-4.0f);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),angle, yAxis);
        GetGameObject()->transform = GetGameObject()->transform * rotation;
    } else if(keyPressed == SDL_SCANCODE_A) {
        glm::vec3 yAxis = glm::vec3(0,1,0);
        float angle = glm::radians(4.0f);
        glm::mat4 rotation = glm::rotate(angle, yAxis);
        GetGameObject()->transform = GetGameObject()->transform * rotation;
    } else {}

}

void ComponentController::Render(sre::RenderPass&) {
	glm::vec3 position, scale;
	glm::quat rotation;
	// we don't really care about these for gameObjects, but we need to matck glm::decompose() signature
	glm::vec3 skew; glm::vec4 perspective;

	glm::decompose(GetGameObject()->transform, scale, rotation, position, skew, perspective);

	glm::vec3 display_rot = glm::degrees(glm::eulerAngles(rotation));
	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 75), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::DragFloat3("Position", glm::value_ptr(position));
	ImGui::DragFloat("Rotation", &display_rot.y);
	ImGui::End();

	GetGameObject()->transform =
		glm::scale(scale) *
		glm::translate(position) *
		glm::mat4_cast(glm::quat(glm::radians(display_rot)));
}