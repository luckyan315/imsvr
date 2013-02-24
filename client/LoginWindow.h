#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include "ui_logindialog.h"

class QWidget;
class LoginWindow : public QDialog , public Ui::LoginDialog{
Q_OBJECT

public:
    LoginWindow(QWidget * parent = NULL);

private:
    void initialize();
    bool isValidIpAddr(const std::string& ip, const std::string& port) const;

signals:
    void loginSuccessEvent(const std::string& ip, const std::string& port);
    void loginWindowDestroy();

private slots:
    void on_pushButton_clicked();

    void on_LoginDialog_destroyed();

private:
    QWidget*     m_parent;
};
#endif // LOGINWINDOW_H
