cmake_minimum_required(VERSION 4.0)
project(zadanie_domowe_29_10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Quick
        REQUIRED)

add_executable(zadanie_domowe_29_10 main.cpp)

qt_add_qml_module(zadanie_domowe_29_10
    URI zadanie_domowe
    VERSION 1.0
    QML_FILES
        qt/qml/main.qml
        qt/qml/LoadPage.qml
        qt/qml/MainPage.qml
)

target_link_libraries(zadanie_domowe_29_10
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Quick
)