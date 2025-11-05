#pragma once

class TriangleMesh
{
public:
    TriangleMesh();
    ~TriangleMesh();
    void draw();

private:
    unsigned int VAO, VBO, vertex_count;
};