/********************************************************************************
** Form generated from reading UI file 'newmodel.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMODEL_H
#define UI_NEWMODEL_H

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

QT_BEGIN_NAMESPACE

class Ui_newModelDialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *filenameLE;
    QPushButton *openFileBtn;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QDoubleSpinBox *spinBoxX;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxY;
    QLabel *label_4;
    QDoubleSpinBox *spinBoxZ;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_5;
    QSpinBox *spinBoxRed;
    QLabel *label_6;
    QSpinBox *spinBoxGreen;
    QLabel *label_7;
    QSpinBox *spinBoxBlue;
    QPushButton *pickColorBtn;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *objectLabelEL;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *newModelDialog)
    {
        if (newModelDialog->objectName().isEmpty())
            newModelDialog->setObjectName(QString::fromUtf8("newModelDialog"));
        newModelDialog->resize(404, 369);
        newModelDialog->setMinimumSize(QSize(404, 369));
        newModelDialog->setMaximumSize(QSize(404, 369));
        gridLayout_4 = new QGridLayout(newModelDialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(newModelDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        filenameLE = new QLineEdit(groupBox);
        filenameLE->setObjectName(QString::fromUtf8("filenameLE"));
        filenameLE->setReadOnly(true);

        horizontalLayout->addWidget(filenameLE);

        openFileBtn = new QPushButton(groupBox);
        openFileBtn->setObjectName(QString::fromUtf8("openFileBtn"));
        openFileBtn->setMinimumSize(QSize(41, 41));
        openFileBtn->setMaximumSize(QSize(41, 41));

        horizontalLayout->addWidget(openFileBtn);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(newModelDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFlat(false);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBoxX = new QDoubleSpinBox(groupBox_2);
        spinBoxX->setObjectName(QString::fromUtf8("spinBoxX"));
        spinBoxX->setDecimals(1);
        spinBoxX->setMinimum(-1000);
        spinBoxX->setMaximum(1000);

        horizontalLayout_2->addWidget(spinBoxX);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBoxY = new QDoubleSpinBox(groupBox_2);
        spinBoxY->setObjectName(QString::fromUtf8("spinBoxY"));
        spinBoxY->setDecimals(1);
        spinBoxY->setMinimum(-1000);
        spinBoxY->setMaximum(1000);

        horizontalLayout_2->addWidget(spinBoxY);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spinBoxZ = new QDoubleSpinBox(groupBox_2);
        spinBoxZ->setObjectName(QString::fromUtf8("spinBoxZ"));
        spinBoxZ->setDecimals(1);
        spinBoxZ->setMinimum(-1000);
        spinBoxZ->setMaximum(1000);

        horizontalLayout_2->addWidget(spinBoxZ);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(newModelDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setAutoFillBackground(false);
        groupBox_3->setStyleSheet(QString::fromUtf8(""));
        groupBox_3->setFlat(false);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        spinBoxRed = new QSpinBox(groupBox_3);
        spinBoxRed->setObjectName(QString::fromUtf8("spinBoxRed"));
        spinBoxRed->setMinimumSize(QSize(59, 31));
        spinBoxRed->setMaximum(255);

        horizontalLayout_4->addWidget(spinBoxRed);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        spinBoxGreen = new QSpinBox(groupBox_3);
        spinBoxGreen->setObjectName(QString::fromUtf8("spinBoxGreen"));
        spinBoxGreen->setMaximum(255);

        horizontalLayout_4->addWidget(spinBoxGreen);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        spinBoxBlue = new QSpinBox(groupBox_3);
        spinBoxBlue->setObjectName(QString::fromUtf8("spinBoxBlue"));
        spinBoxBlue->setMaximum(255);

        horizontalLayout_4->addWidget(spinBoxBlue);


        horizontalLayout_3->addLayout(horizontalLayout_4);

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

        groupBox_4 = new QGroupBox(newModelDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        objectLabelEL = new QLineEdit(groupBox_4);
        objectLabelEL->setObjectName(QString::fromUtf8("objectLabelEL"));
        objectLabelEL->setMaxLength(16);
        objectLabelEL->setFrame(true);

        horizontalLayout_5->addWidget(objectLabelEL);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout_4->addWidget(groupBox_4, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(newModelDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 4, 0, 1, 1);


        retranslateUi(newModelDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), newModelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newModelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(newModelDialog);
    } // setupUi

    void retranslateUi(QDialog *newModelDialog)
    {
        newModelDialog->setWindowTitle(QApplication::translate("newModelDialog", "New 3D Model", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("newModelDialog", "Model file", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("newModelDialog", "File", 0, QApplication::UnicodeUTF8));
        openFileBtn->setText(QApplication::translate("newModelDialog", "..", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("newModelDialog", "Center Coordinates", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("newModelDialog", "x: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("newModelDialog", "y: ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("newModelDialog", "z: ", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("newModelDialog", "Color of the object", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("newModelDialog", "Red", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("newModelDialog", "Green", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("newModelDialog", "Blue", 0, QApplication::UnicodeUTF8));
        pickColorBtn->setText(QApplication::translate("newModelDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("newModelDialog", "Object Label", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("newModelDialog", "Label", 0, QApplication::UnicodeUTF8));
        objectLabelEL->setText(QApplication::translate("newModelDialog", "New Object3D", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newModelDialog: public Ui_newModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMODEL_H
