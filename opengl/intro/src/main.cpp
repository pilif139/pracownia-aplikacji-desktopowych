#include "config.h"
#include "shader.h"
#include "square_mesh.h"
// #include "triangle_mesh.h"

unsigned int make_module(const std::string &filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line))
    {
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char *shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n " << errorLog << std::endl;
    }

    return shaderModule;
}

unsigned int make_shader(const std::string &vertex_filepath, const std::string &fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for (unsigned int module : modules)
    {
        glAttachShader(shader, module);
    }
    glLinkProgram(shader);
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader linking error:\n " << errorLog << std::endl;
    }

    for (unsigned int module : modules)
    {
        glDeleteShader(module);
    }
    return shader;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.0f, 0.1f, 0.1f, 0.1f);
    // int w, h;
    // glfwGetFramebufferSize(window, &w, &h);
    // glViewport(0, 0, 200, 200);

    // TriangleMesh *triangle = new TriangleMesh();
    SquareMesh *square = new SquareMesh();
    square->loadTexture(getPath("./assets/wall.jpg"));
    square->loadTexture(getPath("./assets/awesomeface.png"));

    Shader shader(getPath("./src/shaders/textureVertex.glsl").c_str(), getPath("./src/shaders/textureFragment.glsl").c_str());

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    float xOffset = 0.0f;
    int direction = 1;
    while (!glfwWindowShouldClose(window))
    {
        if(xOffset > 0.5f){
            direction = -1;
        } else if (xOffset < -0.5f) {
            direction = 1;
        }
        xOffset += 0.02f * direction;
        glfwPollEvents();

        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        shader.setInt("texture2", 1);
        // shader.setFloat("xOffset", xOffset);
        // float timeValue = glfwGetTime();
        // float greenValue = sin(timeValue)/2 + 0.5f;
        // shader.setVec3("color", greenValue -0.5f, greenValue, greenValue -0.5f);
        // triangle->draw();
        square->draw();

        glfwSwapBuffers(window);
    }

    delete square;
    // delete triangle;
    glfwTerminate();
    return 0;
}
