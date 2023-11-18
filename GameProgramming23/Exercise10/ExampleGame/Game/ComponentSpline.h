#pragma once

#include "Engine/Component.h"

class ComponentSpline : public MyEngine::Component {
	virtual void Init(rapidjson::Value& serializedData) override;
	virtual void Update(float) override;
	virtual void Render(sre::RenderPass& renderPass) override;

private:
    void PrintPoint(glm::vec2);
	float _speed;
	std::vector<glm::vec3> _points;

	float _t = 0;
    glm::vec3 firstPoint = glm::vec3(0,0,0);
	// for debugging purposes
	std::vector<std::vector<glm::vec3>> _pairs;

    glm::vec3 GetCrossProduct(glm::vec3&, glm::vec3&);
};