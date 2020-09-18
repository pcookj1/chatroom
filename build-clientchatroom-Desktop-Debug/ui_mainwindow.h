/********************************************************************************
** Form generated from reading UI file 'chatroom.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatRoom
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *serverNameLabel;
    QLineEdit *inputServerName;
    QLabel *usernameLabel;
    QLineEdit *inputUsername;
    QPushButton *submitLoginInput;
    QLabel *loginErrorLabel;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QWidget *chatPage;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QTextEdit *chatWindow;
    QLabel *chatWindowLabel;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *userMsgInput;
    QLabel *usersTableLabel;
    QPushButton *submitMsgButton;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *userList;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ChatRoom)
    {
        if (ChatRoom->objectName().isEmpty())
            ChatRoom->setObjectName(QStringLiteral("ChatRoom"));
        ChatRoom->resize(550, 400);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChatRoom->sizePolicy().hasHeightForWidth());
        ChatRoom->setSizePolicy(sizePolicy);
        ChatRoom->setMinimumSize(QSize(550, 400));
        ChatRoom->setMaximumSize(QSize(700, 500));
        centralWidget = new QWidget(ChatRoom);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        loginPage = new QWidget();
        loginPage->setObjectName(QStringLiteral("loginPage"));
        horizontalLayout = new QHBoxLayout(loginPage);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(153, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        serverNameLabel = new QLabel(loginPage);
        serverNameLabel->setObjectName(QStringLiteral("serverNameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serverNameLabel->sizePolicy().hasHeightForWidth());
        serverNameLabel->setSizePolicy(sizePolicy1);
        serverNameLabel->setMinimumSize(QSize(220, 0));
        serverNameLabel->setMaximumSize(QSize(220, 16777215));
        serverNameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(serverNameLabel);

        inputServerName = new QLineEdit(loginPage);
        inputServerName->setObjectName(QStringLiteral("inputServerName"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(inputServerName->sizePolicy().hasHeightForWidth());
        inputServerName->setSizePolicy(sizePolicy2);
        inputServerName->setMinimumSize(QSize(220, 0));
        inputServerName->setMaximumSize(QSize(220, 16777215));

        verticalLayout->addWidget(inputServerName);

        usernameLabel = new QLabel(loginPage);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        sizePolicy1.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy1);
        usernameLabel->setMinimumSize(QSize(220, 0));
        usernameLabel->setMaximumSize(QSize(220, 16777215));
        usernameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(usernameLabel);

        inputUsername = new QLineEdit(loginPage);
        inputUsername->setObjectName(QStringLiteral("inputUsername"));
        sizePolicy2.setHeightForWidth(inputUsername->sizePolicy().hasHeightForWidth());
        inputUsername->setSizePolicy(sizePolicy2);
        inputUsername->setMinimumSize(QSize(220, 0));
        inputUsername->setMaximumSize(QSize(220, 16777215));

        verticalLayout->addWidget(inputUsername);

        submitLoginInput = new QPushButton(loginPage);
        submitLoginInput->setObjectName(QStringLiteral("submitLoginInput"));
        sizePolicy2.setHeightForWidth(submitLoginInput->sizePolicy().hasHeightForWidth());
        submitLoginInput->setSizePolicy(sizePolicy2);
        submitLoginInput->setMinimumSize(QSize(220, 0));
        submitLoginInput->setMaximumSize(QSize(220, 16777215));

        verticalLayout->addWidget(submitLoginInput);

        loginErrorLabel = new QLabel(loginPage);
        loginErrorLabel->setObjectName(QStringLiteral("loginErrorLabel"));
        loginErrorLabel->setMinimumSize(QSize(220, 0));
        loginErrorLabel->setMaximumSize(QSize(220, 16777215));
        loginErrorLabel->setStyleSheet(QStringLiteral("color: #FF0000"));
        loginErrorLabel->setAlignment(Qt::AlignCenter);
        loginErrorLabel->setWordWrap(true);

        verticalLayout->addWidget(loginErrorLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(loginPage);
        chatPage = new QWidget();
        chatPage->setObjectName(QStringLiteral("chatPage"));
        verticalLayout_2 = new QVBoxLayout(chatPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(4);
        chatWindow = new QTextEdit(chatPage);
        chatWindow->setObjectName(QStringLiteral("chatWindow"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(chatWindow->sizePolicy().hasHeightForWidth());
        chatWindow->setSizePolicy(sizePolicy3);
        chatWindow->setMinimumSize(QSize(300, 0));
        chatWindow->setReadOnly(true);

        gridLayout->addWidget(chatWindow, 1, 0, 1, 1);

        chatWindowLabel = new QLabel(chatPage);
        chatWindowLabel->setObjectName(QStringLiteral("chatWindowLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(chatWindowLabel->sizePolicy().hasHeightForWidth());
        chatWindowLabel->setSizePolicy(sizePolicy4);
        chatWindowLabel->setMinimumSize(QSize(300, 0));
        chatWindowLabel->setMaximumSize(QSize(16777215, 20));
        chatWindowLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(chatWindowLabel, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 2, 0, 1, 1);

        userMsgInput = new QLineEdit(chatPage);
        userMsgInput->setObjectName(QStringLiteral("userMsgInput"));

        gridLayout->addWidget(userMsgInput, 3, 0, 1, 1);

        usersTableLabel = new QLabel(chatPage);
        usersTableLabel->setObjectName(QStringLiteral("usersTableLabel"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(usersTableLabel->sizePolicy().hasHeightForWidth());
        usersTableLabel->setSizePolicy(sizePolicy5);
        usersTableLabel->setMinimumSize(QSize(150, 0));
        usersTableLabel->setMaximumSize(QSize(150, 20));
        usersTableLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(usersTableLabel, 0, 2, 1, 1);

        submitMsgButton = new QPushButton(chatPage);
        submitMsgButton->setObjectName(QStringLiteral("submitMsgButton"));
        submitMsgButton->setMinimumSize(QSize(100, 0));
        submitMsgButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(submitMsgButton, 3, 2, 1, 1, Qt::AlignHCenter);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        userList = new QListWidget(chatPage);
        userList->setObjectName(QStringLiteral("userList"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(userList->sizePolicy().hasHeightForWidth());
        userList->setSizePolicy(sizePolicy6);
        userList->setMinimumSize(QSize(150, 0));
        userList->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(userList, 1, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        stackedWidget->addWidget(chatPage);

        verticalLayout_5->addWidget(stackedWidget);

        ChatRoom->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ChatRoom);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 17));
        ChatRoom->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChatRoom);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChatRoom->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ChatRoom);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatRoom->setStatusBar(statusBar);
        toolBar = new QToolBar(ChatRoom);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        ChatRoom->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(ChatRoom);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatRoom);
    } // setupUi

    void retranslateUi(QMainWindow *ChatRoom)
    {
        ChatRoom->setWindowTitle(QApplication::translate("ChatRoom", "MainWindow", Q_NULLPTR));
        serverNameLabel->setText(QApplication::translate("ChatRoom", "Server", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("ChatRoom", "Username", Q_NULLPTR));
        submitLoginInput->setText(QApplication::translate("ChatRoom", "Submit", Q_NULLPTR));
        loginErrorLabel->setText(QString());
        chatWindowLabel->setText(QApplication::translate("ChatRoom", "$Server", Q_NULLPTR));
        usersTableLabel->setText(QApplication::translate("ChatRoom", "Users", Q_NULLPTR));
        submitMsgButton->setText(QApplication::translate("ChatRoom", "Submit", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("ChatRoom", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatRoom: public Ui_ChatRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
