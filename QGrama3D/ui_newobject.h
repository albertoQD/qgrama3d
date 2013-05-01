/********************************************************************************
** Form generated from reading UI file 'newobject.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWOBJECT_H
#define UI_NEWOBJECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newObjectDialog
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QDoubleSpinBox *spinBoxX;
    QLabel *label_2;
    QDoubleSpinBox *spinBoxY;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxZ;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_4;
    QSpinBox *spinBoxRed;
    QLabel *label_5;
    QSpinBox *spinBoxGreen;
    QLabel *label_6;
    QSpinBox *spinBoxBlue;
    QPushButton *pickColorBtn;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLineEdit *objectLabelEL;
    QGroupBox *groupBox_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QDoubleSpinBox *lengthXSB;
    QLabel *label_9;
    QDoubleSpinBox *lengthYSB;
    QLabel *label_10;
    QDoubleSpinBox *lengthZSB;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *newObjectDialog)
    {
        if (newObjectDialog->objectName().isEmpty())
            newObjectDialog->setObjectName(QString::fromUtf8("newObjectDialog"));
        newObjectDialog->setWindowModality(Qt::WindowModal);
        newObjectDialog->resize(480, 369);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newObjectDialog->sizePolicy().hasHeightForWidth());
        newObjectDialog->setSizePolicy(sizePolicy);
        newObjectDialog->setMinimumSize(QSize(480, 369));
        newObjectDialog->setMaximumSize(QSize(480, 369));
        gridLayout_5 = new QGridLayout(newObjectDialog);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(newObjectDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxX = new QDoubleSpinBox(groupBox);
        spinBoxX->setObjectName(QString::fromUtf8("spinBoxX"));
        spinBoxX->setDecimals(1);
        spinBoxX->setMinimum(-1000);
        spinBoxX->setMaximum(1000);

        horizontalLayout->addWidget(spinBoxX);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxY = new QDoubleSpinBox(groupBox);
        spinBoxY->setObjectName(QString::fromUtf8("spinBoxY"));
        spinBoxY->setDecimals(1);
        spinBoxY->setMinimum(-1000);
        spinBoxY->setMaximum(1000);

        horizontalLayout->addWidget(spinBoxY);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxZ = new QDoubleSpinBox(groupBox);
        spinBoxZ->setObjectName(QString::fromUtf8("spinBoxZ"));
        spinBoxZ->setDecimals(1);
        spinBoxZ->setMinimum(-1000);
        spinBoxZ->setMaximum(1000);

        horizontalLayout->addWidget(spinBoxZ);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(newObjectDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setAutoFillBackground(false);
        groupBox_3->setStyleSheet(QString::fromUtf8(""));
        groupBox_3->setFlat(false);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spinBoxRed = new QSpinBox(groupBox_3);
        spinBoxRed->setObjectName(QString::fromUtf8("spinBoxRed"));
        spinBoxRed->setMinimumSize(QSize(59, 31));
        spinBoxRed->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxRed);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        spinBoxGreen = new QSpinBox(groupBox_3);
        spinBoxGreen->setObjectName(QString::fromUtf8("spinBoxGreen"));
        spinBoxGreen->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxGreen);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        spinBoxBlue = new QSpinBox(groupBox_3);
        spinBoxBlue->setObjectName(QString::fromUtf8("spinBoxBlue"));
        spinBoxBlue->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxBlue);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        pickColorBtn = new QPushButton(groupBox_3);
        pickColorBtn->setObjectName(QString::fromUtf8("pickColorBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pickColorBtn->sizePolicy().hasHeightForWidth());
        pickColorBtn->setSizePolicy(sizePolicy1);
        pickColorBtn->setMinimumSize(QSize(41, 41));
        pickColorBtn->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(pickColorBtn);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(newObjectDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        objectLabelEL = new QLineEdit(groupBox_4);
        objectLabelEL->setObjectName(QString::fromUtf8("objectLabelEL"));
        objectLabelEL->setMaxLength(16);
        objectLabelEL->setFrame(true);

        horizontalLayout_4->addWidget(objectLabelEL);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_4->addWidget(groupBox_4, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(newObjectDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(17, 27, 442, 33));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        lengthXSB = new QDoubleSpinBox(widget);
        lengthXSB->setObjectName(QString::fromUtf8("lengthXSB"));
        lengthXSB->setDecimals(1);
        lengthXSB->setMinimum(1);

        horizontalLayout_5->addWidget(lengthXSB);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        lengthYSB = new QDoubleSpinBox(widget);
        lengthYSB->setObjectName(QString::fromUtf8("lengthYSB"));
        lengthYSB->setDecimals(1);
        lengthYSB->setMinimum(1);

        horizontalLayout_5->addWidget(lengthYSB);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        lengthZSB = new QDoubleSpinBox(widget);
        lengthZSB->setObjectName(QString::fromUtf8("lengthZSB"));
        lengthZSB->setDecimals(1);
        lengthZSB->setMinimum(1);

        horizontalLayout_5->addWidget(lengthZSB);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(newObjectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 4, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);


        retranslateUi(newObjectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), newObjectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newObjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(newObjectDialog);
    } // setupUi

    void retranslateUi(QDialog *newObjectDialog)
    {
        newObjectDialog->setWindowTitle(QApplication::translate("newObjectDialog", "New Cube Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("newObjectDialog", "Center Coordinates", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("newObjectDialog", "x: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("newObjectDialog", "y: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("newObjectDialog", "z: ", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("newObjectDialog", "Color of the cube", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("newObjectDialog", "Red", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("newObjectDialog", "Green", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("newObjectDialog", "Blue", 0, QApplication::UnicodeUTF8));
        pickColorBtn->setText(QApplication::translate("newObjectDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("newObjectDialog", "Object Label", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("newObjectDialog", "Label", 0, QApplication::UnicodeUTF8));
        objectLabelEL->setText(QApplication::translate("newObjectDialog", "New Object3D", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("newObjectDialog", "Size of the Cube", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("newObjectDialog", "Length (X)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("newObjectDialog", "Length (Y)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("newObjectDialog", "Length (Z)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newObjectDialog: public Ui_newObjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWOBJECT_H
