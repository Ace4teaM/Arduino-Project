#include "app/application.h"
#include "mainwindow.h"
#include <QApplication>
#include <arduino_server_choice.h>

Application* app;
MainWindow* w;

int main(int argc, char *argv[])
{
    app = new Application(argc, argv);
    w = new MainWindow();
    app->initialise(w);

    w->show();

    return app->exec();
}
