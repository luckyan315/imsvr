#include <iostream>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoginWindow.h"
#include "Client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_pLogin = new LoginWindow(this);
    m_pLogin->show();

    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pLogin;
    delete m_pClient;
}

void MainWindow::initialize()
{
    //TODO: init widgets
    connect(m_pLogin, SIGNAL(loginSuccessEvent(std::string, std::string)),
            this, SLOT(onLoginSuccess(std::string, std::string)));
}

void MainWindow::onLoginSuccess(const std::string ip, const std::string port)
{
    std::cout<<"login success!"<<std::endl;
    std::cout<<"ip:"<<ip<<" port:" <<port<<std::endl;
    this->show();
    //TODO: create client
    m_pClient = new Client(ip.c_str(), port.c_str());
}


void MainWindow::on_btnSend_clicked()
{
    std::string strSend = ui->textInput->toPlainText().toLocal8Bit();
    m_pClient->send(strSend.c_str());
}
