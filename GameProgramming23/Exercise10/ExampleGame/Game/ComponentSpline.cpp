#include "ComponentSpline.h"
using namespace glm;
using namespace std;
void ComponentSpline::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;
	auto pos = gameObject->GetPosition();

	_speed = serializedData["speed"].GetFloat();

	// apply transform to spline point offsets
	for(int i = 0; i < serializedData["points"].Size(); ++i)
		_points.emplace_back(MyEngine::GameObject::DeserializeVector(serializedData["points"][i]) + pos);

	// create point pairs, for debug purposes
	for (int i = 0; i < _points.size() - 1; ++i)
		_pairs.emplace_back(std::vector<glm::vec3> { _points[i], _points[i + 1]});
}

void ComponentSpline::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t += delta;

	int segment = (int)fmod(_t, _points.size() - 1);
	float t = fmod(_t, 1.0f);

    vec3 a = _points[segment];
    vec3 b = _points[segment + 1];

    vec3 offset = vec3(0,0,0);

    if(b.y > a.y) {
        offset = vec3(-20, 20, 0);
    } else {
        offset = vec3(20, 20, 0);
    }
    if(segment == 2) {
        offset = vec3(-10, -10, 0);
    }
    if(segment == 3) {
        offset = vec3(10,-10,0);
    }
    auto intermediatePoint = vec3((a.x + b.x) / 2, (a.y + b.y) / 2, -1) + offset;

    auto p0 = mix(a, intermediatePoint, t);
    auto p1 = mix(intermediatePoint, b, t);
    auto p2 = mix(p0, p1 , t);

    gameObject->SetPosition(p2);


}

void ComponentSpline::PrintPoint(glm::vec2 p) {
    std::cout << p.x << " " << p.y << std::endl;
}

void ComponentSpline::Render(sre::RenderPass& renderPass) {
	for (auto& pair : _pairs)
		renderPass.drawLines(pair);
}