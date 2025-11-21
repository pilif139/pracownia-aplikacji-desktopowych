cmake_minimum_required(VERSION 3.16)

project(zadanie05_11 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Switch to Widgets-based application instead of QML/Quick
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Charts)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appzadanie05_11
    main.cpp
    MainWindow.cpp
        utils/filehandler.cpp
        utils/filehandler.h
    MainWindow.h
    MainWindow.cpp
        utils/image/PBMImage.cpp
        utils/image/PBMImage.h
        utils/image/PGMImage.h
        utils/image/PGMImage.cpp
        utils/image/PPMImage.cpp
        utils/image/PPMImage.h
        components/file/FileController.h
        components/file/FileController.cpp
        components/tools/ToolsManager.h
        components/tools/ToolsManager.cpp
        components/tools/GrayscaleDialog.cpp
        components/tools/InvertDialog.h
        components/tools/InvertDialog.cpp
        components/tools/contrast/LinearContrastDialog.cpp
        components/tools/contrast/LinearContrastDialog.h
        components/tools/contrast/LogContrastDialog.cpp
        components/tools/contrast/LogContrastDialog.h
        components/tools/contrast/ExpContrastDialog.cpp
        components/tools/contrast/ExpContrastDialog.h
        components/tools/contrast/ContrastTools.cpp
        components/tools/contrast/ContrastTools.h
        utils/image/Image.h
)

target_link_libraries(appzadanie05_11
    PRIVATE Qt6::Widgets Qt6::Core Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appzadanie05_11
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
