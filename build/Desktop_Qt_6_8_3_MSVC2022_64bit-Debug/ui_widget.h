/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QToolButton *openbtn;
    QPushButton *lightbtn;
    QPushButton *waterbtn;
    QPushButton *autobtn;
    QPushButton *mysqlbtn;
    QPushButton *debugbtn;
    QPushButton *exitbtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *iplineEdit;
    QLabel *label_3;
    QLineEdit *portlineEdit;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *modebtn;
    QLabel *patternlab;
    QFrame *line_2;
    QLabel *connectlab;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_16;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *ray;
    QLabel *airwater;
    QLabel *oxygen;
    QLabel *label_4;
    QLabel *airtem;
    QFrame *line;
    QLabel *label_6;
    QLabel *soilwater;
    QLabel *soiltem;
    QLabel *label_12;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_23;
    QGridLayout *gridLayout_3;
    QCheckBox *airtemcb;
    QLineEdit *airtemLE;
    QLabel *label_17;
    QCheckBox *airwatercb;
    QLineEdit *airwaterLE;
    QLabel *label_18;
    QCheckBox *oxygencb;
    QLineEdit *oxygenLE;
    QLabel *label_19;
    QCheckBox *soiltemcb;
    QLineEdit *soiltemLE;
    QLabel *label_20;
    QCheckBox *soilwatercb;
    QLineEdit *soilwaterLE;
    QLabel *label_21;
    QCheckBox *raycb;
    QLineEdit *rayLE;
    QLabel *label_22;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_24;
    QSlider *raySlider;
    QLabel *raylabel;
    QGridLayout *gridLayout_4;
    QLabel *label_28;
    QSpinBox *waterspinBox;
    QLabel *label_29;
    QVBoxLayout *verticalLayout_9;
    QFrame *charFrame1;
    QFrame *charFrame2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(1089, 714);
        Widget->setMinimumSize(QSize(700, 600));
        verticalLayout_7 = new QVBoxLayout(Widget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        openbtn = new QToolButton(Widget);
        openbtn->setObjectName("openbtn");
        openbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(openbtn);

        lightbtn = new QPushButton(Widget);
        lightbtn->setObjectName("lightbtn");
        lightbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(lightbtn);

        waterbtn = new QPushButton(Widget);
        waterbtn->setObjectName("waterbtn");
        waterbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(waterbtn);

        autobtn = new QPushButton(Widget);
        autobtn->setObjectName("autobtn");
        autobtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(autobtn);

        mysqlbtn = new QPushButton(Widget);
        mysqlbtn->setObjectName("mysqlbtn");
        mysqlbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(mysqlbtn);

        debugbtn = new QPushButton(Widget);
        debugbtn->setObjectName("debugbtn");
        debugbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(debugbtn);

        exitbtn = new QPushButton(Widget);
        exitbtn->setObjectName("exitbtn");
        exitbtn->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(exitbtn);


        verticalLayout_3->addLayout(horizontalLayout);

        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        verticalLayout_10 = new QVBoxLayout(widget);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setMaximumSize(QSize(80, 30));

        verticalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        iplineEdit = new QLineEdit(frame);
        iplineEdit->setObjectName("iplineEdit");

        gridLayout->addWidget(iplineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        portlineEdit = new QLineEdit(frame);
        portlineEdit->setObjectName("portlineEdit");

        gridLayout->addWidget(portlineEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        modebtn = new QToolButton(frame);
        modebtn->setObjectName("modebtn");

        horizontalLayout_2->addWidget(modebtn);

        patternlab = new QLabel(frame);
        patternlab->setObjectName("patternlab");

        horizontalLayout_2->addWidget(patternlab);

        line_2 = new QFrame(frame);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_2);

        connectlab = new QLabel(frame);
        connectlab->setObjectName("connectlab");

        horizontalLayout_2->addWidget(connectlab);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_8->addWidget(frame);

        frame_2 = new QFrame(widget);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_16 = new QLabel(frame_2);
        label_16->setObjectName("label_16");
        label_16->setEnabled(true);
        label_16->setMaximumSize(QSize(125, 36));

        verticalLayout_2->addWidget(label_16);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");

        gridLayout_2->addWidget(label_10, 3, 0, 1, 1);

        label_11 = new QLabel(frame_2);
        label_11->setObjectName("label_11");

        gridLayout_2->addWidget(label_11, 3, 1, 1, 1);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        ray = new QLabel(frame_2);
        ray->setObjectName("ray");

        gridLayout_2->addWidget(ray, 4, 2, 1, 1);

        airwater = new QLabel(frame_2);
        airwater->setObjectName("airwater");

        gridLayout_2->addWidget(airwater, 1, 1, 1, 1);

        oxygen = new QLabel(frame_2);
        oxygen->setObjectName("oxygen");

        gridLayout_2->addWidget(oxygen, 1, 2, 1, 1);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        airtem = new QLabel(frame_2);
        airtem->setObjectName("airtem");

        gridLayout_2->addWidget(airtem, 1, 0, 1, 1);

        line = new QFrame(frame_2);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_2->addWidget(line, 2, 0, 1, 3);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        soilwater = new QLabel(frame_2);
        soilwater->setObjectName("soilwater");

        gridLayout_2->addWidget(soilwater, 4, 1, 1, 1);

        soiltem = new QLabel(frame_2);
        soiltem->setObjectName("soiltem");

        gridLayout_2->addWidget(soiltem, 4, 0, 1, 1);

        label_12 = new QLabel(frame_2);
        label_12->setObjectName("label_12");

        gridLayout_2->addWidget(label_12, 3, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_8->addWidget(frame_2);

        frame_3 = new QFrame(widget);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_23 = new QLabel(frame_3);
        label_23->setObjectName("label_23");

        verticalLayout_4->addWidget(label_23);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        airtemcb = new QCheckBox(frame_3);
        airtemcb->setObjectName("airtemcb");

        gridLayout_3->addWidget(airtemcb, 0, 0, 1, 1);

        airtemLE = new QLineEdit(frame_3);
        airtemLE->setObjectName("airtemLE");

        gridLayout_3->addWidget(airtemLE, 0, 1, 1, 1);

        label_17 = new QLabel(frame_3);
        label_17->setObjectName("label_17");

        gridLayout_3->addWidget(label_17, 0, 2, 1, 1);

        airwatercb = new QCheckBox(frame_3);
        airwatercb->setObjectName("airwatercb");

        gridLayout_3->addWidget(airwatercb, 1, 0, 1, 1);

        airwaterLE = new QLineEdit(frame_3);
        airwaterLE->setObjectName("airwaterLE");

        gridLayout_3->addWidget(airwaterLE, 1, 1, 1, 1);

        label_18 = new QLabel(frame_3);
        label_18->setObjectName("label_18");

        gridLayout_3->addWidget(label_18, 1, 2, 1, 1);

        oxygencb = new QCheckBox(frame_3);
        oxygencb->setObjectName("oxygencb");

        gridLayout_3->addWidget(oxygencb, 2, 0, 1, 1);

        oxygenLE = new QLineEdit(frame_3);
        oxygenLE->setObjectName("oxygenLE");

        gridLayout_3->addWidget(oxygenLE, 2, 1, 1, 1);

        label_19 = new QLabel(frame_3);
        label_19->setObjectName("label_19");

        gridLayout_3->addWidget(label_19, 2, 2, 1, 1);

        soiltemcb = new QCheckBox(frame_3);
        soiltemcb->setObjectName("soiltemcb");

        gridLayout_3->addWidget(soiltemcb, 3, 0, 1, 1);

        soiltemLE = new QLineEdit(frame_3);
        soiltemLE->setObjectName("soiltemLE");

        gridLayout_3->addWidget(soiltemLE, 3, 1, 1, 1);

        label_20 = new QLabel(frame_3);
        label_20->setObjectName("label_20");

        gridLayout_3->addWidget(label_20, 3, 2, 1, 1);

        soilwatercb = new QCheckBox(frame_3);
        soilwatercb->setObjectName("soilwatercb");

        gridLayout_3->addWidget(soilwatercb, 4, 0, 1, 1);

        soilwaterLE = new QLineEdit(frame_3);
        soilwaterLE->setObjectName("soilwaterLE");

        gridLayout_3->addWidget(soilwaterLE, 4, 1, 1, 1);

        label_21 = new QLabel(frame_3);
        label_21->setObjectName("label_21");

        gridLayout_3->addWidget(label_21, 4, 2, 1, 1);

        raycb = new QCheckBox(frame_3);
        raycb->setObjectName("raycb");

        gridLayout_3->addWidget(raycb, 5, 0, 1, 1);

        rayLE = new QLineEdit(frame_3);
        rayLE->setObjectName("rayLE");

        gridLayout_3->addWidget(rayLE, 5, 1, 1, 1);

        label_22 = new QLabel(frame_3);
        label_22->setObjectName("label_22");

        gridLayout_3->addWidget(label_22, 5, 2, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_8->addWidget(frame_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_24 = new QLabel(widget);
        label_24->setObjectName("label_24");
        label_24->setMinimumSize(QSize(0, 30));
        label_24->setMaximumSize(QSize(16777215, 30));
        label_24->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_24);

        raySlider = new QSlider(widget);
        raySlider->setObjectName("raySlider");
        raySlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_5->addWidget(raySlider);

        raylabel = new QLabel(widget);
        raylabel->setObjectName("raylabel");
        raylabel->setMinimumSize(QSize(0, 30));
        raylabel->setMaximumSize(QSize(16777215, 30));
        raylabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(raylabel);


        horizontalLayout_3->addLayout(verticalLayout_5);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        label_28 = new QLabel(widget);
        label_28->setObjectName("label_28");
        label_28->setMinimumSize(QSize(150, 0));
        label_28->setMaximumSize(QSize(16777215, 30));

        gridLayout_4->addWidget(label_28, 0, 0, 1, 2);

        waterspinBox = new QSpinBox(widget);
        waterspinBox->setObjectName("waterspinBox");
        waterspinBox->setMinimumSize(QSize(100, 0));
        waterspinBox->setMaximumSize(QSize(16777215, 60));
        waterspinBox->setMaximum(100000);

        gridLayout_4->addWidget(waterspinBox, 1, 0, 1, 1);

        label_29 = new QLabel(widget);
        label_29->setObjectName("label_29");
        label_29->setMaximumSize(QSize(16777215, 60));

        gridLayout_4->addWidget(label_29, 1, 1, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_4);


        verticalLayout_8->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        charFrame1 = new QFrame(widget);
        charFrame1->setObjectName("charFrame1");
        charFrame1->setMinimumSize(QSize(800, 300));
        charFrame1->setMaximumSize(QSize(800, 300));
        charFrame1->setFrameShape(QFrame::Shape::StyledPanel);
        charFrame1->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_9->addWidget(charFrame1);

        charFrame2 = new QFrame(widget);
        charFrame2->setObjectName("charFrame2");
        charFrame2->setMinimumSize(QSize(800, 300));
        charFrame2->setMaximumSize(QSize(800, 300));
        charFrame2->setFrameShape(QFrame::Shape::StyledPanel);
        charFrame2->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_9->addWidget(charFrame2);


        horizontalLayout_4->addLayout(verticalLayout_9);


        verticalLayout_10->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(widget);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 10);

        verticalLayout_7->addLayout(verticalLayout_3);

        QWidget::setTabOrder(lightbtn, waterbtn);
        QWidget::setTabOrder(waterbtn, mysqlbtn);
        QWidget::setTabOrder(mysqlbtn, debugbtn);
        QWidget::setTabOrder(debugbtn, exitbtn);
        QWidget::setTabOrder(exitbtn, airtemcb);
        QWidget::setTabOrder(airtemcb, airtemLE);
        QWidget::setTabOrder(airtemLE, airwatercb);
        QWidget::setTabOrder(airwatercb, airwaterLE);
        QWidget::setTabOrder(airwaterLE, oxygencb);
        QWidget::setTabOrder(oxygencb, oxygenLE);
        QWidget::setTabOrder(oxygenLE, soiltemcb);
        QWidget::setTabOrder(soiltemcb, soiltemLE);
        QWidget::setTabOrder(soiltemLE, soilwatercb);
        QWidget::setTabOrder(soilwatercb, soilwaterLE);
        QWidget::setTabOrder(soilwaterLE, raycb);
        QWidget::setTabOrder(raycb, rayLE);
        QWidget::setTabOrder(rayLE, iplineEdit);
        QWidget::setTabOrder(iplineEdit, portlineEdit);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        openbtn->setText(QCoreApplication::translate("Widget", "\345\274\200\345\220\257\345\205\263\351\227\255", nullptr));
        lightbtn->setText(QCoreApplication::translate("Widget", "\345\274\200\347\201\257", nullptr));
        waterbtn->setText(QCoreApplication::translate("Widget", "\346\265\207\346\260\264", nullptr));
        autobtn->setText(QCoreApplication::translate("Widget", "\350\207\252\345\212\250\357\274\210\345\256\242\346\234\272\346\250\241\345\274\217\357\274\211", nullptr));
        mysqlbtn->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\345\272\223", nullptr));
        debugbtn->setText(QCoreApplication::translate("Widget", "\350\260\203\350\257\225", nullptr));
        exitbtn->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "IP\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", nullptr));
        portlineEdit->setText(QCoreApplication::translate("Widget", "1210", nullptr));
        modebtn->setText(QCoreApplication::translate("Widget", ".....", nullptr));
        patternlab->setText(QCoreApplication::translate("Widget", "\344\270\273\346\234\272\346\250\241\345\274\217", nullptr));
        connectlab->setText(QCoreApplication::translate("Widget", "\346\234\252\350\277\236\346\216\245", nullptr));
        label_16->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\347\233\221\346\216\247", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "\345\234\237\345\243\244\346\270\251\345\272\246", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "\345\234\237\345\243\244\345\220\253\346\260\264\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\347\251\272\346\260\224\347\233\270\345\257\271\346\271\277\345\272\246", nullptr));
        ray->setText(QCoreApplication::translate("Widget", "0%", nullptr));
        airwater->setText(QCoreApplication::translate("Widget", "0%", nullptr));
        oxygen->setText(QCoreApplication::translate("Widget", "0%", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\347\251\272\346\260\224\346\270\251\345\272\246", nullptr));
        airtem->setText(QCoreApplication::translate("Widget", "0\302\260C", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\346\260\247\346\260\224\346\265\223\345\272\246", nullptr));
        soilwater->setText(QCoreApplication::translate("Widget", "0%", nullptr));
        soiltem->setText(QCoreApplication::translate("Widget", "0\302\260C", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", "\345\205\211\347\205\247\345\274\272\345\272\246", nullptr));
        label_23->setText(QCoreApplication::translate("Widget", "\346\212\245\350\255\246\351\230\210\345\200\274", nullptr));
        airtemcb->setText(QCoreApplication::translate("Widget", "\347\251\272\346\260\224\346\270\251\345\272\246", nullptr));
        label_17->setText(QCoreApplication::translate("Widget", "\302\260C", nullptr));
        airwatercb->setText(QCoreApplication::translate("Widget", "\347\251\272\346\260\224\347\233\270\345\257\271\346\271\277\345\272\246", nullptr));
        label_18->setText(QCoreApplication::translate("Widget", "%", nullptr));
        oxygencb->setText(QCoreApplication::translate("Widget", "\346\260\247\346\260\224\346\265\223\345\272\246", nullptr));
        label_19->setText(QCoreApplication::translate("Widget", "%", nullptr));
        soiltemcb->setText(QCoreApplication::translate("Widget", "\345\234\237\345\243\244\346\270\251\345\272\246", nullptr));
        label_20->setText(QCoreApplication::translate("Widget", "\302\260C", nullptr));
        soilwatercb->setText(QCoreApplication::translate("Widget", "\345\234\237\345\243\244\345\220\253\346\260\264\351\207\217", nullptr));
        label_21->setText(QCoreApplication::translate("Widget", "%", nullptr));
        raycb->setText(QCoreApplication::translate("Widget", "\345\205\211\347\205\247\345\274\272\345\272\246", nullptr));
        label_22->setText(QCoreApplication::translate("Widget", "%", nullptr));
        label_24->setText(QCoreApplication::translate("Widget", "\345\205\211\347\205\247\345\274\272\345\272\246", nullptr));
        raylabel->setText(QCoreApplication::translate("Widget", "%", nullptr));
        label_28->setText(QCoreApplication::translate("Widget", "\345\226\267\346\260\264\346\227\266\351\227\264", nullptr));
        label_29->setText(QCoreApplication::translate("Widget", "S", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
