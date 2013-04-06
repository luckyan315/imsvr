#include <iostream>
#include <string>
#include <QMessageBox>
#include <QObject>
#include "LoginWindow.h"
#include <boost/shared_ptr.hpp>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent), m_parent(parent)
{
    setupUi(this);
    initialize();
}

void LoginWindow::initialize()
{
    //TODO: initialize widgets's flags
    btnLogin->setEnabled(true);

    //connect slots
    connect(btnLogin, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

void LoginWindow::on_pushButton_clicked()
{
    std::string strIp = textSvrIp->toPlainText().toLatin1().data();
    std::string strPort = textSvrPort->toPlainText().toLatin1().data();
    if(!isValidIpAddr(strIp.c_str(), strPort.c_str())){
        //QMessageBox::information(this,tr("hello"),tr("hello"));
        std::cout<<"Invalid ip addr ("<<strIp<<":"<<strPort<<")"<<std::endl;
        return;
    }

    //if login succeed
    this->hide();
    emit loginSuccessEvent(strIp.c_str(), strPort.c_str());


}

bool LoginWindow::isValidIpAddr(const std::string& ip, const std::string& port) const
{
    //TODO:
    std::cout<<"ip:"<<ip<<" port:" <<port<<std::endl;
    return true;
}
