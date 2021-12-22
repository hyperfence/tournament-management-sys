#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // Binding all the buttons to their handlers
    connect(ui.loginBtn, SIGNAL(clicked()), this, SLOT(handleLogin()));
    connect(ui.signupBtn, SIGNAL(clicked()), this, SLOT(handleSignup()));
    connect(ui.toLoginBtn, SIGNAL(clicked()), this, SLOT(loginScreen()));
    connect(ui.toSignupBtn, SIGNAL(clicked()), this, SLOT(signupScreen()));
    connect(ui.teamsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.matchesBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.tournamentsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.tabWidget1, SIGNAL(currentChanged(int)), this, SLOT(homeTabsNavigation()));
}

void MainWindow::loginScreen()
{
    ui.stackedWidget->setCurrentWidget(ui.Login);
}
void MainWindow::signupScreen()
{
    ui.stackedWidget->setCurrentWidget(ui.Signup);
}
void MainWindow::handleLogin()
{
    ui.loginBtn->setText("Wait...");
    QString email = ui.inpLoginEmail->text();
    QString pass = ui.inpLoginPass->text();
    if (player.login(email.toStdString(), pass.toStdString()) == true)
    {
        ui.stackedWidget->setCurrentWidget(ui.Home);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Credentials", "The username and password your provided are invalid! Please try again with valid credentials.");
        ui.loginBtn->setText("Login");
    }
}
void MainWindow::handleSignup()
{
    ui.signupBtn->setText("Wait...");
    QString name = ui.inpRegName->text();
    QString email = ui.inpRegEmail->text();
    QString pass = ui.inpRegPass->text();
    if (player.signup(name.toStdString(), email.toStdString(), pass.toStdString()) == true)
    {
        QMessageBox successBox;
        successBox.information(this, "Account Created", "Your account was created successfully! Pleae login with your credentials.");
        ui.stackedWidget->setCurrentWidget(ui.Login);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Input", "Failed to create your account! Please try again with valid input.");
        ui.signupBtn->setText("Register");
    }
}
void MainWindow::homeNavigation()
{
    QObject* button = QObject::sender();
    if (button == ui.homeBtn || button == ui.homeBtn_2 || button == ui.homeBtn_3 || button == ui.homeBtn_4)
    {
        connect(ui.teamsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.stackedWidget->setCurrentWidget(ui.Home);
    }
    else if (button == ui.teamsBtn || button == ui.teamsBtn_2 || button == ui.teamsBtn_3 || button == ui.teamsBtn_4)
    {
        connect(ui.homeBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.stackedWidget->setCurrentWidget(ui.Teams);
    }
    else if (button == ui.matchesBtn || button == ui.matchesBtn_2 || button == ui.matchesBtn_3 || button == ui.matchesBtn_4)
    {
        connect(ui.homeBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.teamsBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.stackedWidget->setCurrentWidget(ui.Matches);
    }
    else if (button == ui.tournamentsBtn || button == ui.tournamentsBtn_2 || button == ui.tournamentsBtn_3 || button == ui.tournamentsBtn_4)
    {
        connect(ui.homeBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.teamsBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.stackedWidget->setCurrentWidget(ui.Tournaments);
    }
}
void MainWindow::homeTabsNavigation()
{
    int index = ui.tabWidget1->currentIndex();
    if (index == 0)
    {

    }
    else if (index == 1)
    {

    }
}