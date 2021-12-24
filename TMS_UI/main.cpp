#include <windows.h>
#include "MainWindow.h"
#include "DBHandler.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>
#include <QtGui/QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap(":/MainWindow/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();
    QIcon icon(":/MainWindow/gui.ico");
    MainWindow win;
    win.setWindowIcon(icon);
    win.setWindowTitle("Tournament Management System");
    win.show();
    splash.close();
    return app.exec();
}
