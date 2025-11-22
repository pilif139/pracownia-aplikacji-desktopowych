#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

uniform float xOffset;

void main() {
    gl_Position = vec4(vertexPos.x + xOffset, vertexPos.y + xOffset, vertexPos.z, 1.0);
    fragmentColor = vec3(vertexPos.x + xOffset, vertexPos.y + xOffset, vertexColor.z + xOffset);
}
