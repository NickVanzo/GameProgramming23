#include "ComponentRendererMesh.h"
#include "glm/gtx/transform.hpp"

void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
    std::cout << "In init of ComponentRendererMesh" << std::endl;
    _texture = sre::Texture::create().withFile("data/level0.png")
            .withGenerateMipmaps(false)
            .withFilterSampling(false)
            .build();

    _material = sre::Shader::getUnlit()->createMaterial();
    _material->setTexture(_texture);

	_mesh = sre::Mesh::create()
        .withPositions(positions)
        .withUVs(uvs)
        .withIndices(idxs, sre::MeshTopology::Triangles, 0)
        .build();

    glm::vec3 gameObjectPos = GetGameObject()->GetPosition();
}

void ComponentRendererMesh::Update(float deltaTime) {
//    GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass& renderPass) {
        std::cout << "Rendering" << std::endl;
        renderPass.draw(_mesh, GetGameObject()->transform, _material);

        //draw second face
        glm::mat4 secondFaceTransform = GetGameObject()->transform;
        secondFaceTransform = glm::rotate(secondFaceTransform, glm::radians(90.0f), glm::vec3(0,1,0));
        renderPass.draw(_mesh, secondFaceTransform, _material);

        //draw third face
        glm::mat4 thirdFaceTransform = GetGameObject()->transform;
        thirdFaceTransform = glm::rotate(thirdFaceTransform, glm::radians(-90.0f), glm::vec3(0,1,0));
        renderPass.draw(_mesh, thirdFaceTransform, _material);

        //draw fourth face
        glm::mat4 fourthFaceTransform = GetGameObject()->transform;
        fourthFaceTransform = glm::translate(fourthFaceTransform, glm::vec3(0,0,0));
        fourthFaceTransform = glm::rotate(fourthFaceTransform, glm::radians(180.0f), glm::vec3(0,1,0));
        renderPass.draw(_mesh, fourthFaceTransform, _material);
}