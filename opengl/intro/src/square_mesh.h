#pragma once

#include <string>
#include <vector>
class SquareMesh
{
public:
    SquareMesh();
    ~SquareMesh();
    void draw();
    void loadTexture(const std::string& path);

private:
    unsigned int VAO, VBO, EBO;
    std::vector<unsigned int> texturesIds;
};
