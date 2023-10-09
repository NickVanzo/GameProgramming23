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

    SetupLayoutFromJSON(serializedData);
}

void ComponentRendererMesh::SetupLayoutFromJSON(rapidjson::Value &serializedData) {
    if(serializedData.HasMember("layout") && serializedData["layout"].IsArray()) {
        auto& layout = serializedData["layout"];
        for(rapidjson::SizeType i = 0; i < layout.Size(); ++i) {
            auto& row = layout[i];
            if(row.IsArray()) {
                for(rapidjson::SizeType j = 0; j < row.Size(); ++j) {
                    _layout[i][j] = row[j].GetInt();
                    CreateMesh(i, j);
                }
            }
        }
    } else {
        std::cout << "Layout not found" << std::endl;
    }
}

void ComponentRendererMesh::CreateMesh(float tilePosX, float tilePosY) {
    _meshes.push_back(
            sre::Mesh::create()
                              .withPositions(positions)
                              .withUVs(CalculateUvs(tilePosX, tilePosY))
                              .withIndices(idxs, sre::MeshTopology::Triangles, 0)
                              .build());
}

std::vector<glm::vec4> ComponentRendererMesh::CalculateUvs(float tilePosX, float tilePosY) {
    const glm::vec2 min = glm::vec2(tilePosX * tileSizeWithBorder.x, tilePosY * tileSizeWithBorder.y) / textureSize;
    const glm::vec2 max = min + tileSize / textureSize;
    const std::vector<glm::vec4> uvs = {
            glm::vec4(min.x, min.y, 0, 0),
            glm::vec4(min.x, max.y, 0, 0),
            glm::vec4(max.x, max.y, 0, 0),
            glm::vec4(max.x, min.y, 0, 0)
    };
    return uvs;
}

void ComponentRendererMesh::Update(float deltaTime) {
//    GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass& renderPass) {
        glm::mat4 startingPos = GetGameObject()->transform;
        for(int i = 0; i < _meshes.size(); ++i) {
            for(int j = 0; j < 1; ++j) {
                auto mesh = _meshes[i];

                glm::mat4 firstFaceTransorm = startingPos;
                firstFaceTransorm = glm::translate(firstFaceTransorm, glm::vec3(i - j,0,0));
                renderPass.draw(mesh, firstFaceTransorm, _material);

                //draw second face
                glm::mat4 secondFaceTransform = startingPos;
                secondFaceTransform = glm::translate(secondFaceTransform, glm::vec3(i - j,0,0));
                secondFaceTransform = glm::rotate(secondFaceTransform, glm::radians(90.0f), glm::vec3(0,1,0));
                renderPass.draw(mesh, secondFaceTransform, _material);

                //draw third face
                glm::mat4 thirdFaceTransform = startingPos;
                thirdFaceTransform = glm::translate(thirdFaceTransform, glm::vec3(i - j,0,0));
                thirdFaceTransform = glm::rotate(thirdFaceTransform, glm::radians(-90.0f), glm::vec3(0,1,0));
                renderPass.draw(mesh, thirdFaceTransform, _material);

                //draw fourth face
                glm::mat4 fourthFaceTransform = startingPos;
                fourthFaceTransform = glm::translate(fourthFaceTransform, glm::vec3(i - j,0,0));
                fourthFaceTransform = glm::rotate(fourthFaceTransform, glm::radians(180.0f), glm::vec3(0,1,0));
                renderPass.draw(mesh, fourthFaceTransform, _material);
            }
        }
}