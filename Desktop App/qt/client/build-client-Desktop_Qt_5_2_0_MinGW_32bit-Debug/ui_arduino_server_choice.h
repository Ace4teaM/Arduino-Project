/********************************************************************************
** Form generated from reading UI file 'arduino_server_choice.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARDUINO_SERVER_CHOICE_H
#define UI_ARDUINO_SERVER_CHOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArduinoServerChoice
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QTextEdit *textServerIP;
    QLabel *label_2;

    void setupUi(QDialog *ArduinoServerChoice)
    {
        if (ArduinoServerChoice->objectName().isEmpty())
            ArduinoServerChoice->setObjectName(QStringLiteral("ArduinoServerChoice"));
        ArduinoServerChoice->resize(400, 99);
        buttonBox = new QDialogButtonBox(ArduinoServerChoice);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 60, 381, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(ArduinoServerChoice);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 30, 381, 21));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        textServerIP = new QTextEdit(formLayoutWidget);
        textServerIP->setObjectName(QStringLiteral("textServerIP"));

        formLayout->setWidget(0, QFormLayout::FieldRole, textServerIP);

        label_2 = new QLabel(ArduinoServerChoice);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 221, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        retranslateUi(ArduinoServerChoice);
        QObject::connect(buttonBox, SIGNAL(accepted()), ArduinoServerChoice, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ArduinoServerChoice, SLOT(reject()));

        QMetaObject::connectSlotsByName(ArduinoServerChoice);
    } // setupUi

    void retranslateUi(QDialog *ArduinoServerChoice)
    {
        ArduinoServerChoice->setWindowTitle(QApplication::translate("ArduinoServerChoice", "Dialog", 0));
        label->setText(QApplication::translate("ArduinoServerChoice", "Adresse IP", 0));
        label_2->setText(QApplication::translate("ArduinoServerChoice", "Entrez l'adresse du serveur Arduino", 0));
    } // retranslateUi

};

namespace Ui {
    class ArduinoServerChoice: public Ui_ArduinoServerChoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARDUINO_SERVER_CHOICE_H
