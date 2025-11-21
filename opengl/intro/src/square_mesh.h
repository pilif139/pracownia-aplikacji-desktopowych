#pragma once

class SquareMesh
{
public:
    SquareMesh();
    ~SquareMesh();
    void draw();

private:
    unsigned int VAO, VBO, EBO;
};