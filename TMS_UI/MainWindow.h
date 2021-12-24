#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qstackedlayout.h>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "ui_MainWindow.h"
#include "DBHandler.h"
#include "Player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void generateTableWidget1();
    void generateTableWidget2();

public slots:
    void loginScreen();
    void signupScreen();
    void handleLogin();
    void handleSignup();
    void handleLogout();
    void homeNavigation();
    void homeTabsNavigation();
    void matchesTabsNavigation();
    void tournamentsTabsNavigation();
    void teamsTabsNavigation();
    void createTournament();
    void createTeam();
    void createMatch();
    void sendInvite();
    // Table Widgets Click Functions
    void onTableWidget1RemClicked();
    void onTableWidget2AckClicked();
    void onTableWidget2RejClicked();

private:
    Ui::MainWindowClass ui;
    Player player;
    DBHandler DB;

};
