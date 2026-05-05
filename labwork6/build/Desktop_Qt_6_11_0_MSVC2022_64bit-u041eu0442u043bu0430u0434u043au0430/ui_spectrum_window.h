/********************************************************************************
** Form generated from reading UI file 'spectrum_window.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECTRUM_WINDOW_H
#define UI_SPECTRUM_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_SpectrumWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupShape;
    QHBoxLayout *shapeLayout;
    QRadioButton *rbCircle;
    QRadioButton *rbSquare;
    QGridLayout *plotGrid;
    QCustomPlot *plotFunc;
    QCustomPlot *plotSpectrum;
    QCustomPlot *plotSections;
    QGroupBox *groupGrid;
    QVBoxLayout *gridLayout_2;
    QComboBox *cbSize;
    QGroupBox *groupSteps;
    QFormLayout *stepsFormLayout;
    QLabel *labelStepX;
    QLineEdit *edStepX;
    QLabel *labelStepFreq;
    QLineEdit *edStepFreq;
    QFormLayout *diameterFormLayout;
    QLineEdit *edDiameter;
    QLabel *labelDiameter;
    QPushButton *btnCompute;
    QPushButton *btnReset;
    QGroupBox *groupRendering;
    QRadioButton *rbMM;
    QRadioButton *rbPixels;
    QPushButton *btnRender;

    void setupUi(QMainWindow *SpectrumWindow)
    {
        if (SpectrumWindow->objectName().isEmpty())
            SpectrumWindow->setObjectName("SpectrumWindow");
        SpectrumWindow->resize(1100, 700);
        centralwidget = new QWidget(SpectrumWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        groupShape = new QGroupBox(centralwidget);
        groupShape->setObjectName("groupShape");
        shapeLayout = new QHBoxLayout(groupShape);
        shapeLayout->setObjectName("shapeLayout");
        rbCircle = new QRadioButton(groupShape);
        rbCircle->setObjectName("rbCircle");
        rbCircle->setChecked(true);

        shapeLayout->addWidget(rbCircle);

        rbSquare = new QRadioButton(groupShape);
        rbSquare->setObjectName("rbSquare");

        shapeLayout->addWidget(rbSquare);


        gridLayout->addWidget(groupShape, 0, 0, 1, 2);

        plotGrid = new QGridLayout();
        plotGrid->setObjectName("plotGrid");
        plotFunc = new QCustomPlot(centralwidget);
        plotFunc->setObjectName("plotFunc");
        plotFunc->setMinimumSize(QSize(300, 280));

        plotGrid->addWidget(plotFunc, 0, 0, 1, 1);

        plotSpectrum = new QCustomPlot(centralwidget);
        plotSpectrum->setObjectName("plotSpectrum");
        plotSpectrum->setMinimumSize(QSize(300, 280));

        plotGrid->addWidget(plotSpectrum, 0, 1, 1, 1);

        plotSections = new QCustomPlot(centralwidget);
        plotSections->setObjectName("plotSections");
        plotSections->setMinimumSize(QSize(620, 280));

        plotGrid->addWidget(plotSections, 1, 0, 1, 2);


        gridLayout->addLayout(plotGrid, 0, 2, 7, 1);

        groupGrid = new QGroupBox(centralwidget);
        groupGrid->setObjectName("groupGrid");
        gridLayout_2 = new QVBoxLayout(groupGrid);
        gridLayout_2->setObjectName("gridLayout_2");
        cbSize = new QComboBox(groupGrid);
        cbSize->addItem(QString());
        cbSize->addItem(QString());
        cbSize->addItem(QString());
        cbSize->addItem(QString());
        cbSize->addItem(QString());
        cbSize->setObjectName("cbSize");

        gridLayout_2->addWidget(cbSize);


        gridLayout->addWidget(groupGrid, 1, 0, 1, 1);

        groupSteps = new QGroupBox(centralwidget);
        groupSteps->setObjectName("groupSteps");
        stepsFormLayout = new QFormLayout(groupSteps);
        stepsFormLayout->setObjectName("stepsFormLayout");
        labelStepX = new QLabel(groupSteps);
        labelStepX->setObjectName("labelStepX");

        stepsFormLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelStepX);

        edStepX = new QLineEdit(groupSteps);
        edStepX->setObjectName("edStepX");

        stepsFormLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, edStepX);

        labelStepFreq = new QLabel(groupSteps);
        labelStepFreq->setObjectName("labelStepFreq");

        stepsFormLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelStepFreq);

        edStepFreq = new QLineEdit(groupSteps);
        edStepFreq->setObjectName("edStepFreq");
        edStepFreq->setReadOnly(true);

        stepsFormLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, edStepFreq);


        gridLayout->addWidget(groupSteps, 2, 0, 1, 2);

        diameterFormLayout = new QFormLayout();
        diameterFormLayout->setObjectName("diameterFormLayout");
        edDiameter = new QLineEdit(centralwidget);
        edDiameter->setObjectName("edDiameter");

        diameterFormLayout->setWidget(1, QFormLayout::ItemRole::SpanningRole, edDiameter);

        labelDiameter = new QLabel(centralwidget);
        labelDiameter->setObjectName("labelDiameter");

        diameterFormLayout->setWidget(0, QFormLayout::ItemRole::SpanningRole, labelDiameter);


        gridLayout->addLayout(diameterFormLayout, 3, 0, 1, 2);

        btnCompute = new QPushButton(centralwidget);
        btnCompute->setObjectName("btnCompute");

        gridLayout->addWidget(btnCompute, 4, 0, 1, 1);

        btnReset = new QPushButton(centralwidget);
        btnReset->setObjectName("btnReset");

        gridLayout->addWidget(btnReset, 4, 1, 1, 1);

        groupRendering = new QGroupBox(centralwidget);
        groupRendering->setObjectName("groupRendering");
        rbMM = new QRadioButton(groupRendering);
        rbMM->setObjectName("rbMM");
        rbMM->setGeometry(QRect(10, 30, 110, 24));
        rbMM->setChecked(true);
        rbPixels = new QRadioButton(groupRendering);
        rbPixels->setObjectName("rbPixels");
        rbPixels->setGeometry(QRect(130, 30, 110, 24));

        gridLayout->addWidget(groupRendering, 5, 0, 1, 2);

        btnRender = new QPushButton(centralwidget);
        btnRender->setObjectName("btnRender");

        gridLayout->addWidget(btnRender, 6, 0, 1, 2);

        SpectrumWindow->setCentralWidget(centralwidget);

        retranslateUi(SpectrumWindow);

        QMetaObject::connectSlotsByName(SpectrumWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SpectrumWindow)
    {
        SpectrumWindow->setWindowTitle(QCoreApplication::translate("SpectrumWindow", "Lab 6 \342\200\224 FFT Spectrum", nullptr));
        groupShape->setTitle(QCoreApplication::translate("SpectrumWindow", "\320\244\320\276\321\200\320\274\320\260", nullptr));
        rbCircle->setText(QCoreApplication::translate("SpectrumWindow", "\320\232\321\200\321\203\320\263", nullptr));
        rbSquare->setText(QCoreApplication::translate("SpectrumWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202", nullptr));
        groupGrid->setTitle(QCoreApplication::translate("SpectrumWindow", "\320\241\320\265\321\202\320\272\320\260", nullptr));
        cbSize->setItemText(0, QCoreApplication::translate("SpectrumWindow", "64", nullptr));
        cbSize->setItemText(1, QCoreApplication::translate("SpectrumWindow", "128", nullptr));
        cbSize->setItemText(2, QCoreApplication::translate("SpectrumWindow", "256", nullptr));
        cbSize->setItemText(3, QCoreApplication::translate("SpectrumWindow", "512", nullptr));
        cbSize->setItemText(4, QCoreApplication::translate("SpectrumWindow", "1024", nullptr));

        groupSteps->setTitle(QCoreApplication::translate("SpectrumWindow", "\320\250\320\260\320\263\320\270", nullptr));
        labelStepX->setText(QCoreApplication::translate("SpectrumWindow", "\320\250\320\260\320\263 X (\320\274\320\274):", nullptr));
        labelStepFreq->setText(QCoreApplication::translate("SpectrumWindow", "\320\250\320\260\320\263 \321\207\320\260\321\201\321\202\320\276\321\202\321\213 (1/\320\274\320\274):", nullptr));
        labelDiameter->setText(QCoreApplication::translate("SpectrumWindow", "\320\224\320\270\320\260\320\274\320\265\321\202\321\200 \320\272\321\200\321\203\320\263\320\260/\n"
"\320\241\321\202\320\276\321\200\320\276\320\275\320\260 \320\272\320\262\320\260\320\264\321\200\320\260\321\202\320\260 (\320\274\320\274):", nullptr));
        btnCompute->setText(QCoreApplication::translate("SpectrumWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        btnReset->setText(QCoreApplication::translate("SpectrumWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        groupRendering->setTitle(QCoreApplication::translate("SpectrumWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        rbMM->setText(QCoreApplication::translate("SpectrumWindow", "\320\274\320\274", nullptr));
        rbPixels->setText(QCoreApplication::translate("SpectrumWindow", "\320\277\320\270\320\272\321\201\320\265\320\273\320\270", nullptr));
        btnRender->setText(QCoreApplication::translate("SpectrumWindow", "\320\237\320\265\321\200\320\265\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpectrumWindow: public Ui_SpectrumWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECTRUM_WINDOW_H
