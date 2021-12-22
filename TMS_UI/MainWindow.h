#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qstackedlayout.h>
#include <QMessageBox>
#include "ui_MainWindow.h"
#include "Player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
    void loginScreen();
    void signupScreen();
    void handleLogin();
    void handleSignup();
    void homeNavigation();
    void homeTabsNavigation();
    /*void page3Screen();
    void page4Screen();
    void page5Screen();*/

private:
    Ui::MainWindowClass ui;
    Player player;

};
