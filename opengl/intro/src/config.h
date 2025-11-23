#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>

#include <vector>

inline std::string getPath(const std::string& relativePath){
    return std::string(PROJECT_ROOT) + "/" + relativePath;
}
