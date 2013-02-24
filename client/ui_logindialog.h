/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created: Sun Feb 24 17:30:58 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *btnLogin;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QTextEdit *textSvrIp;
    QLabel *label_4;
    QTextEdit *textSvrPort;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textUserId;
    QTextEdit *textPasswd;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(329, 149);
        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(180, 120, 141, 23));
        horizontalLayoutWidget = new QWidget(LoginDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 311, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        textSvrIp = new QTextEdit(horizontalLayoutWidget);
        textSvrIp->setObjectName(QString::fromUtf8("textSvrIp"));

        horizontalLayout_4->addWidget(textSvrIp);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        textSvrPort = new QTextEdit(horizontalLayoutWidget);
        textSvrPort->setObjectName(QString::fromUtf8("textSvrPort"));

        horizontalLayout_4->addWidget(textSvrPort);

        verticalLayoutWidget = new QWidget(LoginDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 50, 61, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        verticalLayoutWidget_2 = new QWidget(LoginDialog);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(70, 50, 251, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textUserId = new QTextEdit(verticalLayoutWidget_2);
        textUserId->setObjectName(QString::fromUtf8("textUserId"));

        verticalLayout_2->addWidget(textUserId);

        textPasswd = new QTextEdit(verticalLayoutWidget_2);
        textPasswd->setObjectName(QString::fromUtf8("textPasswd"));

        verticalLayout_2->addWidget(textPasswd);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnLogin->setText(QApplication::translate("LoginDialog", "Login", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LoginDialog", "Server IP:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("LoginDialog", "Port:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LoginDialog", "UserId:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("LoginDialog", "Password:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
