// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mainwindow.h"
#include <QApplication>


/**
 * @brief Main entry point for the program
 */
int main(int argc, char *argv[])
{
    // Run the Qt MainWindow application
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
