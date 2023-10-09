#include "ComponentRendererMesh.h"
#include "glm/gtx/transform.hpp"

void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
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
                    CreateMesh(_layout[i][j], i, j);
                    std::cout << "Tile found in: [" << i << "," << j << "]" << "->" << row[j].GetInt() << std::endl;
                }
            }
        }
    } else {
        std::cout << "Layout not found" << std::endl;
    }
}

void ComponentRendererMesh::CreateMesh(float tileNumber, int i, int j) {
    _meshes[i][j] = sre::Mesh::create()
                              .withPositions(positions)
                              .withUVs(CalculateUvs(floor(tileNumber / 6), floor(fmod(tileNumber, 16)) ))
                              .withIndices(idxs, sre::MeshTopology::Triangles, 0)
                              .build();
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
        for(int i = 0; i < MyEngine::ROWS; ++i) {
            for(int j = 0; j < MyEngine::COLUMNS; ++j) {
                auto tileValue = _layout[i][j];
                if(tileValue != -1) {
                    auto mesh = _meshes[i][j];

                    glm::mat4 firstFaceTransorm = startingPos;
                    firstFaceTransorm = glm::translate(firstFaceTransorm, glm::vec3(i,0,j));
                    renderPass.draw(mesh, firstFaceTransorm, _material);

                    //draw second face
                    glm::mat4 secondFaceTransform = startingPos;
                    secondFaceTransform = glm::translate(secondFaceTransform, glm::vec3(i,0,j));
                    secondFaceTransform = glm::rotate(secondFaceTransform, glm::radians(90.0f), glm::vec3(0,1,0));
                    renderPass.draw(mesh, secondFaceTransform, _material);

                    //draw third face
                    glm::mat4 thirdFaceTransform = startingPos;
                    thirdFaceTransform = glm::translate(thirdFaceTransform, glm::vec3(i,0,j));
                    thirdFaceTransform = glm::rotate(thirdFaceTransform, glm::radians(-90.0f), glm::vec3(0,1,0));
                    renderPass.draw(mesh, thirdFaceTransform, _material);

                    //draw fourth face
                    glm::mat4 fourthFaceTransform = startingPos;
                    fourthFaceTransform = glm::translate(fourthFaceTransform, glm::vec3(i,0,j));
                    fourthFaceTransform = glm::rotate(fourthFaceTransform, glm::radians(180.0f), glm::vec3(0,1,0));
                    renderPass.draw(mesh, fourthFaceTransform, _material);
                } else {
//                    std::cout << "Found -1 in position: [" << i << "," << j << "]" << std::endl;
                }
            }
        }
}