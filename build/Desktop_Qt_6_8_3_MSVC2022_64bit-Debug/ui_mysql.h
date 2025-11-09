/********************************************************************************
** Form generated from reading UI file 'mysql.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSQL_H
#define UI_MYSQL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mysql
{
public:
    QVBoxLayout *verticalLayout_4;
    QLabel *status;
    QTableWidget *datetable;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QDateTimeEdit *dateTimeON;
    QPushButton *inquire;
    QLabel *label_4;
    QDateTimeEdit *dateTimeOFF;
    QPushButton *nowtime;
    QPushButton *oneday;
    QPushButton *threeday;
    QPushButton *aweek;
    QVBoxLayout *verticalLayout_3;
    QPushButton *exit;
    QPushButton *deleteall;
    QPushButton *showall;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QPushButton *dateinquire;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QLineEdit *maxlineEdit;
    QLabel *label_8;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *Mysql)
    {
        if (Mysql->objectName().isEmpty())
            Mysql->setObjectName("Mysql");
        Mysql->resize(890, 665);
        verticalLayout_4 = new QVBoxLayout(Mysql);
        verticalLayout_4->setObjectName("verticalLayout_4");
        status = new QLabel(Mysql);
        status->setObjectName("status");
        status->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(status);

        datetable = new QTableWidget(Mysql);
        datetable->setObjectName("datetable");

        verticalLayout_4->addWidget(datetable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        frame = new QFrame(Mysql);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        dateTimeON = new QDateTimeEdit(frame);
        dateTimeON->setObjectName("dateTimeON");

        gridLayout->addWidget(dateTimeON, 0, 1, 1, 3);

        inquire = new QPushButton(frame);
        inquire->setObjectName("inquire");

        gridLayout->addWidget(inquire, 0, 4, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        dateTimeOFF = new QDateTimeEdit(frame);
        dateTimeOFF->setObjectName("dateTimeOFF");

        gridLayout->addWidget(dateTimeOFF, 1, 1, 1, 3);

        nowtime = new QPushButton(frame);
        nowtime->setObjectName("nowtime");

        gridLayout->addWidget(nowtime, 1, 4, 1, 1);

        oneday = new QPushButton(frame);
        oneday->setObjectName("oneday");

        gridLayout->addWidget(oneday, 2, 0, 1, 2);

        threeday = new QPushButton(frame);
        threeday->setObjectName("threeday");

        gridLayout->addWidget(threeday, 2, 2, 1, 1);

        aweek = new QPushButton(frame);
        aweek->setObjectName("aweek");

        gridLayout->addWidget(aweek, 2, 3, 1, 2);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addWidget(frame);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        exit = new QPushButton(Mysql);
        exit->setObjectName("exit");

        verticalLayout_3->addWidget(exit);

        deleteall = new QPushButton(Mysql);
        deleteall->setObjectName("deleteall");

        verticalLayout_3->addWidget(deleteall);

        showall = new QPushButton(Mysql);
        showall->setObjectName("showall");

        verticalLayout_3->addWidget(showall);


        horizontalLayout->addLayout(verticalLayout_3);

        frame_2 = new QFrame(Mysql);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName("gridLayout_2");
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        dateinquire = new QPushButton(frame_2);
        dateinquire->setObjectName("dateinquire");

        gridLayout_2->addWidget(dateinquire, 0, 1, 1, 1);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        comboBox = new QComboBox(frame_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout_2->addWidget(comboBox, 1, 1, 1, 1);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        maxlineEdit = new QLineEdit(frame_2);
        maxlineEdit->setObjectName("maxlineEdit");

        gridLayout_2->addWidget(maxlineEdit, 2, 1, 1, 1);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        lineEdit_2 = new QLineEdit(frame_2);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout_2->addWidget(lineEdit_2, 3, 1, 1, 1);


        horizontalLayout->addWidget(frame_2);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(Mysql);

        QMetaObject::connectSlotsByName(Mysql);
    } // setupUi

    void retranslateUi(QWidget *Mysql)
    {
        Mysql->setWindowTitle(QCoreApplication::translate("Mysql", "Form", nullptr));
        status->setText(QCoreApplication::translate("Mysql", "\346\225\260\346\215\256\345\272\223\347\256\241\347\220\206\345\271\263\345\217\260", nullptr));
        label_2->setText(QCoreApplication::translate("Mysql", "\346\227\245\346\234\237\346\237\245\350\257\242", nullptr));
        label_3->setText(QCoreApplication::translate("Mysql", "\345\274\200\345\247\213", nullptr));
        inquire->setText(QCoreApplication::translate("Mysql", "\346\237\245\350\257\242", nullptr));
        label_4->setText(QCoreApplication::translate("Mysql", "\347\273\223\346\235\237", nullptr));
        nowtime->setText(QCoreApplication::translate("Mysql", "\347\216\260\345\234\250\346\227\266\351\227\264", nullptr));
        oneday->setText(QCoreApplication::translate("Mysql", "\346\234\200\350\277\221\344\270\200\345\244\251", nullptr));
        threeday->setText(QCoreApplication::translate("Mysql", "\346\234\200\350\277\221\344\270\211\345\244\251", nullptr));
        aweek->setText(QCoreApplication::translate("Mysql", "\346\234\200\350\277\221\344\270\200\345\221\250", nullptr));
        exit->setText(QCoreApplication::translate("Mysql", "\351\200\200\345\207\272", nullptr));
        deleteall->setText(QCoreApplication::translate("Mysql", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        showall->setText(QCoreApplication::translate("Mysql", "\346\230\276\347\244\272\346\211\200\346\234\211\346\225\260\346\215\256", nullptr));
        label_5->setText(QCoreApplication::translate("Mysql", "\345\200\274\346\237\245\350\257\242", nullptr));
        dateinquire->setText(QCoreApplication::translate("Mysql", "\347\202\271\345\207\273\346\237\245\350\257\242", nullptr));
        label_6->setText(QCoreApplication::translate("Mysql", "\346\237\245\350\257\242\345\261\236\346\200\247", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Mysql", "\347\251\272\346\260\224\346\270\251\345\272\246", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Mysql", "\347\251\272\346\260\224\347\233\270\345\257\271\346\271\277\345\272\246", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Mysql", "\346\260\247\346\260\224\346\265\223\345\272\246", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Mysql", "\345\234\237\345\243\244\346\270\251\345\272\246", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Mysql", "\345\234\237\345\243\244\345\220\253\346\260\264\351\207\217", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Mysql", "\345\205\211\347\205\247\345\274\272\345\272\246", nullptr));

        label_7->setText(QCoreApplication::translate("Mysql", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("Mysql", "\346\234\200\345\244\247\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mysql: public Ui_Mysql {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSQL_H
