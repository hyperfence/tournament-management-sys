#include "MainWindow.h"
#include "Tournament.h"
#include "Team.h"
#include "Invitation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    DB.establishConnection();
    // Binding all the buttons to their handlers
    connect(ui.loginBtn, SIGNAL(clicked()), this, SLOT(handleLogin()));
    connect(ui.signupBtn, SIGNAL(clicked()), this, SLOT(handleSignup()));
    connect(ui.toLoginBtn, SIGNAL(clicked()), this, SLOT(loginScreen()));
    connect(ui.toSignupBtn, SIGNAL(clicked()), this, SLOT(signupScreen()));
    connect(ui.teamsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.matchesBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.tournamentsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
    connect(ui.logoutBtn, SIGNAL(clicked()), this, SLOT(handleLogout()));
    connect(ui.tabWidget1, SIGNAL(currentChanged(int)), this, SLOT(homeTabsNavigation()));
    connect(ui.tabWidget2, SIGNAL(currentChanged(int)), this, SLOT(teamsTabsNavigation()));
    connect(ui.tabWidget4, SIGNAL(currentChanged(int)), this, SLOT(tournamentsTabsNavigation()));
    connect(ui.tabWidget3, SIGNAL(currentChanged(int)), this, SLOT(matchesTabsNavigation()));
    ui.stackedWidget->setCurrentWidget(ui.Login);
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
    DB.establishConnection();
    if (player.login(email.toStdString(), pass.toStdString()) == true)
    {

        ui.inpLoginEmail->setText("");
        ui.inpLoginPass->setText("");
        ui.lblProfName->setText(QString::fromStdString(this->player.getName()));
        ui.lblProfEmail->setText(QString::fromStdString(this->player.getEmail()));
        ui.lblProfStatus->setText(QString::fromStdString(this->player.getStatus()));
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
    DB.establishConnection();
    if (name != "" && email != "" && pass != "" && email != "Email" && player.signup(name.toStdString(), email.toStdString(), pass.toStdString()) == true)
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
void MainWindow::handleLogout()
{
    this->player.logout();
    QMessageBox successBox;
    successBox.information(this, "Logout", "You were logged out of your account successfully.");
    ui.stackedWidget->setCurrentWidget(ui.Login);
}
void MainWindow::homeNavigation()
{
    QObject* button = QObject::sender();
    if (button == ui.homeBtn || button == ui.homeBtn_2 || button == ui.homeBtn_3 || button == ui.homeBtn_4)
    {
        connect(ui.teamsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.tabWidget1->setCurrentIndex(0);
        ui.stackedWidget->setCurrentWidget(ui.Home);
    }
    else if (button == ui.teamsBtn || button == ui.teamsBtn_2 || button == ui.teamsBtn_3 || button == ui.teamsBtn_4)
    {
        connect(ui.homeBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn_2, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.sendInviteBtn, SIGNAL(clicked()), this, SLOT(sendInvite()));
        connect(ui.createTeamBtn, SIGNAL(clicked()), this, SLOT(createTeam()));
        ui.tabWidget2->setCurrentIndex(0);
        ui.stackedWidget->setCurrentWidget(ui.Teams);
    }
    else if (button == ui.matchesBtn || button == ui.matchesBtn_2 || button == ui.matchesBtn_3 || button == ui.matchesBtn_4)
    {
        connect(ui.homeBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.teamsBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.tournamentsBtn_3, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        ui.tabWidget3->setCurrentIndex(0);
        ui.stackedWidget->setCurrentWidget(ui.Matches);
    }
    else if (button == ui.tournamentsBtn || button == ui.tournamentsBtn_2 || button == ui.tournamentsBtn_3 || button == ui.tournamentsBtn_4)
    {
        connect(ui.homeBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.teamsBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.matchesBtn_4, SIGNAL(clicked()), this, SLOT(homeNavigation()));
        connect(ui.createMatchBtn, SIGNAL(clicked()), this, SLOT(createMatch()));
        connect(ui.createTournamentBtn, SIGNAL(clicked()), this, SLOT(createTournament()));
        ui.tabWidget4->setCurrentIndex(0);
        ui.stackedWidget->setCurrentWidget(ui.Tournaments);
        this->generateTableWidget1();
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
void MainWindow::teamsTabsNavigation()
{
    int index = ui.tabWidget2->currentIndex();
    if (index == 0)
    {

    }
    else if (index == 1)
    {
        this->generateTableWidget2();
    }
    else if (index == 2)
    {

    }
}
void MainWindow::matchesTabsNavigation()
{
    int index = ui.tabWidget3->currentIndex();
    if (index == 0)
    {

    }
    else if (index == 1)
    {

    }
}
void MainWindow::tournamentsTabsNavigation()
{
    int index = ui.tabWidget4->currentIndex();
    if (index == 0)
    {
        this->generateTableWidget1();
    }
    else if (index == 1)
    {

    }
    else if (index == 2)
    {

    }
}
void MainWindow::generateTableWidget1()
{
    ui.tableWidget->clear();
    ui.tableWidget->setRowCount(5);
    ui.tableWidget->setColumnCount(4);
    ui.tableWidget->setAlternatingRowColors(true);
    ui.tableWidget->setColumnWidth(0, 50);
    ui.tableWidget->setColumnWidth(1, 250);
    ui.tableWidget->setColumnWidth(2, 100);
    ui.tableWidget->setColumnWidth(3, 85);
    ui.tableWidget->setStyleSheet("background-color: #eee; alternate-background-color: #fff;");
    QStringList hLabels;
    hLabels << "ID" << "Name" << "Game" << "Actions";
    ui.tableWidget->setHorizontalHeaderLabels(hLabels);
    for (int i = 0; i < ui.tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item;
        for (int j = 0; j < ui.tableWidget->columnCount(); j++)
        {
            item = new QTableWidgetItem();
            item->setText("TalhaTalha");
            if (j == 3)
            {
                QPushButton* btn_rem = new QPushButton();
                btn_rem->setText("Remove");
                btn_rem->setStyleSheet("background-color: red; color: #fff; font-weight: 700");
                connect(btn_rem, &QPushButton::clicked, this, &MainWindow::onTableWidget1RemClicked);
                ui.tableWidget->setCellWidget(i, j, btn_rem);
            }
            else
            {
                ui.tableWidget->setItem(i, j, item);
            }
        }
    }
}
void MainWindow::generateTableWidget2()
{
    Invitation invites;
    int count = 0;
    DB.establishConnection();
    InviteList* list = invites.getInvites(this->player.getId(), &count);
    ui.tableWidget2->clear();
    ui.tableWidget2->setRowCount(count);
    ui.tableWidget2->setColumnCount(4);
    ui.tableWidget2->setAlternatingRowColors(true);
    ui.tableWidget2->setColumnWidth(0, 50);
    ui.tableWidget2->setColumnWidth(1, 240);
    ui.tableWidget2->setColumnWidth(2, 90);
    ui.tableWidget2->setColumnWidth(3, 90);
    ui.tableWidget2->setStyleSheet("background-color: #eee; alternate-background-color: #fff;");
    QStringList hLabels;
    hLabels << "ID" << "Team Name" << "Action" << "Action";
    ui.tableWidget2->setHorizontalHeaderLabels(hLabels);
    for (int i = 0; i < ui.tableWidget2->rowCount(); i++)
    {
        QTableWidgetItem* item;
        for (int j = 0; j < ui.tableWidget2->columnCount(); j++)
        {
            item = new QTableWidgetItem();
            if (j == 0)
            {
                item->setText(QString::fromStdString(std::to_string(list[i].inviteID)));
                ui.tableWidget2->setItem(i, j, item);
            }
            if (j == 1)
            {
                item->setText(QString::fromStdString(list[i].teamName));
                ui.tableWidget2->setItem(i, j, item);
            }
            if (j == 2)
            {
                QPushButton* btn_ack = new QPushButton();
                btn_ack->setText("Accept");
                btn_ack->setStyleSheet("background-color: #32CD32; color: #fff; font-weight: 700");
                connect(btn_ack, &QPushButton::clicked, this, &MainWindow::onTableWidget2AckClicked);
                ui.tableWidget2->setCellWidget(i, j, btn_ack);
            }
            else if (j == 3)
            {
                QPushButton* btn_rej = new QPushButton();
                btn_rej->setText("Reject");
                btn_rej->setStyleSheet("background-color: red; color: #fff; font-weight: 700");
                connect(btn_rej, &QPushButton::clicked, this, &MainWindow::onTableWidget2RejClicked);
                ui.tableWidget2->setCellWidget(i, j, btn_rej);
            }
        }
    }
}
void MainWindow::onTableWidget1RemClicked()
{
    QWidget* w = qobject_cast<QWidget*>(sender()->parent());
    if (w) {
        int row = ui.tableWidget->indexAt(w->pos()).row();
        ui.tableWidget->removeRow(row);
        ui.tableWidget->setCurrentCell(0, 0);
    }
}
void MainWindow::onTableWidget2AckClicked()
{
    QWidget* w = qobject_cast<QWidget*>(sender()->parent());
    if (w) {
        int row = ui.tableWidget2->indexAt(w->pos()).row();
        QString id_s = ui.tableWidget2->item(row, 0)->text();
        int id = id_s.toInt();
        ui.tableWidget2->removeRow(row);
        ui.tableWidget2->setCurrentCell(0, 0);
        DB.establishConnection();
        Invitation invite;
        invite.acceptInvite(id);
    }
}
void MainWindow::onTableWidget2RejClicked()
{
    QWidget* w = qobject_cast<QWidget*>(sender()->parent());
    if (w) {
        int row = ui.tableWidget2->indexAt(w->pos()).row();
        QString id_s = ui.tableWidget2->item(row, 0)->text();
        int id = id_s.toInt();
        ui.tableWidget2->removeRow(row);
        ui.tableWidget2->setCurrentCell(0, 0);
        DB.establishConnection();
        Invitation invite;
        invite.rejectInvite(id);
    }
}
void MainWindow::createTournament()
{
    ui.createTournamentBtn->setText(" Wait...");
    Tournament tournament;
    QString title = ui.inpTorTitle->text();
    int game_id = ui.inpTorGame->currentIndex() + 1;
    QString prize = ui.inpTorPrize->text();
    int totalTeams = ui.inpTorTeams->value();
    DB.establishConnection();
    if (title != "" && game_id >= 1 && totalTeams >= 1 && tournament.addTournament(title.toStdString(), game_id, prize.toStdString(), totalTeams, 1) == true)
    {
        QMessageBox successBox;
        successBox.information(this, "Tournament Created", "The tournament was created successfully! Now you can schedule and add matches for this tournament.");
        ui.inpTorTitle->setText("");
        ui.inpTorGame->setCurrentIndex(0);
        ui.inpTorPrize->setText("");
        ui.inpTorTeams->setValue(0);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Input", "Failed to create the tournament! Please try again with valid input.");
    }
    ui.createTournamentBtn->setText(" Create");
    ui.stackedWidget->setCurrentWidget(ui.Tournaments);
}
void MainWindow::createTeam()
{
    ui.createTeamBtn->setText(" Wait...");
    Team team;
    QString name = ui.inpTeamName->text();
    int totalPlayers = ui.inpTeamPlayers->value();
    DB.establishConnection();
    if (name != "" && totalPlayers >= 1 && team.createTeam(this->player.getId(), name.toStdString(), totalPlayers) == true)
    {
        QMessageBox successBox;
        successBox.information(this, "Team Created", "The team was created successfully! Now you can invite other players to your team.");
        ui.inpTeamName->setText("");
        ui.inpTeamPlayers->setValue(0);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Input", "Failed to create the team! Please try again with valid input.");
    }
    ui.createTeamBtn->setText(" Create");
    ui.stackedWidget->setCurrentWidget(ui.Teams);
}
void MainWindow::createMatch()
{
    ui.createMatchBtn->setText("    Wait...");
    Tournament tournament;
    int tId = ui.inpMatchTournament->value();
    int team_1 = ui.inpMatchTeam1->value();
    int team_2 = ui.inpMatchTeam2->value();
    QDateTime date = ui.inpMatchDate->dateTime();
    QString dateStr = date.toString("yyyy") + "-" + date.toString("MM") + "-" + date.toString("dd") + " " + date.toString("hh") + ":" + date.toString("mm") + ":" + date.toString("ss");
    DB.establishConnection();
    if (tId > 0 && team_1 > 0 && team_2 > 0 && team_1 != team_2 && tournament.addMatch(team_1, team_2, tId, dateStr.toStdString()) == true)
    {
        QMessageBox successBox;
        successBox.information(this, "Match Created", "The match was created successfully.");
        ui.inpMatchTournament->setValue(0);
        ui.inpMatchTeam1->setValue(0);
        ui.inpMatchTeam2->setValue(0);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Input", "Failed to create the match! Please try again with valid input.");
    }
    ui.createMatchBtn->setText(" Create");
}
void MainWindow::sendInvite()
{
    ui.sendInviteBtn->setText(" Wait...");
    Invitation invite;
    QString email = ui.inpInviteEmail->text();
    int teamId= ui.inpInviteTeam->value();
    DB.establishConnection();
    if (email != "" && teamId >= 1 && invite.sendInvite(this->player.getId(), email.toStdString(), teamId) == true)
    {
        QMessageBox successBox;
        successBox.information(this, "Invite Send", "The invite was sent successfully! The player will be added to your team when they accept the invite.");
        ui.inpInviteEmail->setText("");
        ui.inpInviteTeam->setValue(0);
    }
    else
    {
        QMessageBox errorBox;
        errorBox.critical(this, "Invalid Input", "Failed to send the invite! Please try again with valid input.");
    }
    ui.sendInviteBtn->setText(" Send");
    ui.stackedWidget->setCurrentWidget(ui.Teams);
}