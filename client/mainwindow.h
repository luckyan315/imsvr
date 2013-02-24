#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LoginWindow;
class Client;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected slots:
    void onLoginSuccess(const std::string ip, const std::string port);

private slots:
    void on_btnSend_clicked();

private:
    void initialize();

private:
    Ui::MainWindow *ui;
    LoginWindow * m_pLogin;
    Client      * m_pClient;
};

#endif // MAINWINDOW_H
