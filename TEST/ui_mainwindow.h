/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QScrollArea *centralwidget;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *videoLabel;
    QLineEdit *messageLineEdit;
    QPushButton *sendButton;
    QTextEdit *messagesTextEdit;
    QLineEdit *commandLineEdit;
    QPushButton *moveButton;
    QTextEdit *commandsTextEdit;
    QPushButton *fetchDataButton;
    QPushButton *captureScreenButton;
    QTextEdit *measurementsTextEdit;
    QLabel *commandLabel;
    QGroupBox *servoGroup;
    QVBoxLayout *vboxLayout;
    QSlider *servoSlider;
    QLabel *servoAngleLabel;
    QPushButton *sendServoButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QScrollArea(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videoLabel = new QLabel(scrollAreaWidgetContents);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        videoLabel->setMinimumSize(QSize(320, 240));
        videoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(videoLabel);

        messageLineEdit = new QLineEdit(scrollAreaWidgetContents);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        verticalLayout->addWidget(messageLineEdit);

        sendButton = new QPushButton(scrollAreaWidgetContents);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout->addWidget(sendButton);

        messagesTextEdit = new QTextEdit(scrollAreaWidgetContents);
        messagesTextEdit->setObjectName(QString::fromUtf8("messagesTextEdit"));
        messagesTextEdit->setReadOnly(true);

        verticalLayout->addWidget(messagesTextEdit);

        commandLineEdit = new QLineEdit(scrollAreaWidgetContents);
        commandLineEdit->setObjectName(QString::fromUtf8("commandLineEdit"));

        verticalLayout->addWidget(commandLineEdit);

        moveButton = new QPushButton(scrollAreaWidgetContents);
        moveButton->setObjectName(QString::fromUtf8("moveButton"));

        verticalLayout->addWidget(moveButton);

        commandsTextEdit = new QTextEdit(scrollAreaWidgetContents);
        commandsTextEdit->setObjectName(QString::fromUtf8("commandsTextEdit"));
        commandsTextEdit->setReadOnly(true);

        verticalLayout->addWidget(commandsTextEdit);

        fetchDataButton = new QPushButton(scrollAreaWidgetContents);
        fetchDataButton->setObjectName(QString::fromUtf8("fetchDataButton"));

        verticalLayout->addWidget(fetchDataButton);

        captureScreenButton = new QPushButton(scrollAreaWidgetContents);
        captureScreenButton->setObjectName(QString::fromUtf8("captureScreenButton"));

        verticalLayout->addWidget(captureScreenButton);

        measurementsTextEdit = new QTextEdit(scrollAreaWidgetContents);
        measurementsTextEdit->setObjectName(QString::fromUtf8("measurementsTextEdit"));
        measurementsTextEdit->setReadOnly(true);

        verticalLayout->addWidget(measurementsTextEdit);

        commandLabel = new QLabel(scrollAreaWidgetContents);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));

        verticalLayout->addWidget(commandLabel);

        servoGroup = new QGroupBox(scrollAreaWidgetContents);
        servoGroup->setObjectName(QString::fromUtf8("servoGroup"));
        vboxLayout = new QVBoxLayout(servoGroup);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        servoSlider = new QSlider(servoGroup);
        servoSlider->setObjectName(QString::fromUtf8("servoSlider"));
        servoSlider->setOrientation(Qt::Horizontal);
        servoSlider->setMinimum(0);
        servoSlider->setMaximum(180);
        servoSlider->setValue(90);

        vboxLayout->addWidget(servoSlider);

        servoAngleLabel = new QLabel(servoGroup);
        servoAngleLabel->setObjectName(QString::fromUtf8("servoAngleLabel"));

        vboxLayout->addWidget(servoAngleLabel);

        sendServoButton = new QPushButton(servoGroup);
        sendServoButton->setObjectName(QString::fromUtf8("sendServoButton"));

        vboxLayout->addWidget(sendServoButton);


        verticalLayout->addWidget(servoGroup);

        centralwidget->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mon Application", nullptr));
        videoLabel->setText(QCoreApplication::translate("MainWindow", "Flux Vid\303\251o", nullptr));
        messageLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre message ici", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Message", nullptr));
        commandLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre commande de mouvement ici", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Commande de Mouvement", nullptr));
        fetchDataButton->setText(QCoreApplication::translate("MainWindow", "R\303\251cup\303\251rer Donn\303\251es", nullptr));
        captureScreenButton->setText(QCoreApplication::translate("MainWindow", "Capturer \303\211cran", nullptr));
        commandLabel->setText(QCoreApplication::translate("MainWindow", "Q - Gauche, X - Stop, D - Droite, S - Reculer, A - Tourner, W - \342\206\231, C - \342\206\230", nullptr));
        servoGroup->setTitle(QCoreApplication::translate("MainWindow", "Contr\303\264le du Servomoteur", nullptr));
        servoAngleLabel->setText(QCoreApplication::translate("MainWindow", "Angle: 90\302\260", nullptr));
        sendServoButton->setText(QCoreApplication::translate("MainWindow", "Envoyer angle au servomoteur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
