#pragma once

#include <string>
#include <vector>
class CubeMesh
{
public:
    CubeMesh();
    ~CubeMesh();
    void draw();
    void bindVAO();
    void loadTexture(const std::string& path);
    void bindTextures();

private:
    unsigned int VAO, VBO;
    std::vector<unsigned int> texturesIds;
};
