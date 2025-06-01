#include <crtdbg.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <QApplication>
#include "MainWindow.h"
#include "Test.h"
#include <QDebug>
#define _CRTDBG_MAP_ALLOC


int main(int argc, char *argv[])
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    qDebug() << "Memory leak detection enabled!";
    test_all();
    ///int* test_leak = new int[100];
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
