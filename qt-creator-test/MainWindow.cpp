#include "MainWindow.h"
#include "QSlider"
#include "QWidget"
#include "QHBoxLayout"
#include "QCalendarWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto widget = new QWidget(this);
    setCentralWidget(widget);

    auto mainLayout = new QHBoxLayout(widget);
    mainLayout->addWidget(new QSlider(this));
    mainLayout->addWidget(new QCalendarWidget(this));
}

MainWindow::~MainWindow() {}
