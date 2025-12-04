#include "config.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "shader.h"
// #include "square_mesh.h"
// #include "triangle_mesh.h"
#include "cube_mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float mixValue = 0.2f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        mixValue += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        mixValue -= 0.01f;
    }
    mixValue = std::max(0.0f, std::min(1.0f, mixValue));
    // fov = std::max(1.0f, std::min(179.0f, fov));

    // camera handling
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = std::max(-89.0f, std::min(89.0f, pitch));
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    fov = std::max(1.0f, std::min(45.0f, fov));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        std::cout << "GLFW could not be initialized!" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// On macOS, this is required for OpenGL 3.3+
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(800, 600, "Hello world", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.0f, 0.1f, 0.1f, 0.1f);
    glEnable(GL_DEPTH_TEST);
    // int w, h;
    // glfwGetFramebufferSize(window, &w, &h);
    // glViewport(0, 0, 200, 200);

    // TriangleMesh *triangle = new TriangleMesh();
    // SquareMesh *square = new SquareMesh();
    // square->loadTexture(getPath("./assets/wall.jpg"));
    // square->loadTexture(getPath("./assets/awesomeface.png"));
    CubeMesh *cube = new CubeMesh();
    cube->loadTexture(getPath("./assets/wall.jpg"));
    cube->loadTexture(getPath("./assets/awesomeface.png"));

    Shader shader(getPath("./src/shaders/cube.vert").c_str(), getPath("./src/shaders/cube.frag").c_str());

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    float xOffset = 0.0f;
    float yOffset = 0.0f;
    // int yDirection = 1;
    // int xDirection = 1;

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (!glfwWindowShouldClose(window))
    {
        // if(xOffset > 0.5f){
        //     xDirection = -1;
        // } else if (xOffset < -0.5f) {
        //     xDirection = 1;
        // }
        // if(yOffset > 0.5f){
        //     yDirection = -1;
        // } else if (yOffset < -0.5f) {
        //     yDirection = 1;
        // }
        // xOffset += 0.001f * xDirection;
        // yOffset += 0.0005f * yDirection;

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov), 10.0f / 10.0f, 0.1f, 100.0f);

        glfwPollEvents();
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube->bindTextures();
        shader.use();
        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);
        shader.setFloat("mixFactor", mixValue);
        shader.setFloat("xOffset", xOffset);
        shader.setFloat("yOffset", yOffset);
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        cube->bindVAO();
        for(unsigned int i=0; i<10; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            float angle = 35.0f * (i % 2 ? 1.0f : -1.0f);
            model = glm::rotate(model,static_cast<float>(glfwGetTime()) * glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.5f));

            unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            cube->draw();
        }

        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue)/2 + 0.5f;
        // shader.setVec3("color", greenValue -0.5f, greenValue, greenValue -0.5f);
        // triangle->draw();
        // square->draw();

        // trans = glm::mat4(1.0f);
        // trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        // float scaleValue = static_cast<float>(glm::abs(glm::sin(glfwGetTime())));
        // trans = glm::scale(trans, glm::vec3(scaleValue, scaleValue, scaleValue));
        // glUniformMatrix4fv(transformLoc,1, GL_FALSE, &trans[0][0]);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // CubeMesh doesn't have an EBO!

        glfwSwapBuffers(window);
    }

    delete cube;
    // delete triangle;
    glfwTerminate();
    return 0;
}
