/********************************************************************************
** Form generated from reading UI file 'viewer_window.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_WINDOW_H
#define UI_VIEWER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ViewerWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QWidget *ctrlPanel;
    QVBoxLayout *ctrlLayout;
    QGroupBox *groupShape;
    QHBoxLayout *shapeLayout;
    QRadioButton *rbCircle;
    QRadioButton *rbSquare;
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
    QLabel *labelDiameter;
    QLineEdit *edDiameter;
    QCheckBox *chkLogScale;
    QPushButton *btnCompute;
    QPushButton *btnReset;
    QLabel *lblTime;
    QSpacerItem *ctrlSpacer;
    QGridLayout *plotGrid;
    QCustomPlot *plotFunc;
    QCustomPlot *plotSpectrum;
    QCustomPlot *plotSections;

    void setupUi(QMainWindow *ViewerWindow)
    {
        if (ViewerWindow->objectName().isEmpty())
            ViewerWindow->setObjectName("ViewerWindow");
        ViewerWindow->resize(1100, 700);
        centralwidget = new QWidget(ViewerWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        ctrlPanel = new QWidget(centralwidget);
        ctrlPanel->setObjectName("ctrlPanel");
        ctrlPanel->setMinimumSize(QSize(250, 0));
        ctrlPanel->setMaximumSize(QSize(250, 16777215));
        ctrlLayout = new QVBoxLayout(ctrlPanel);
        ctrlLayout->setObjectName("ctrlLayout");
        ctrlLayout->setContentsMargins(0, 0, 0, 0);
        groupShape = new QGroupBox(ctrlPanel);
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


        ctrlLayout->addWidget(groupShape);

        groupGrid = new QGroupBox(ctrlPanel);
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


        ctrlLayout->addWidget(groupGrid);

        groupSteps = new QGroupBox(ctrlPanel);
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


        ctrlLayout->addWidget(groupSteps);

        diameterFormLayout = new QFormLayout();
        diameterFormLayout->setObjectName("diameterFormLayout");
        labelDiameter = new QLabel(ctrlPanel);
        labelDiameter->setObjectName("labelDiameter");

        diameterFormLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelDiameter);

        edDiameter = new QLineEdit(ctrlPanel);
        edDiameter->setObjectName("edDiameter");

        diameterFormLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, edDiameter);


        ctrlLayout->addLayout(diameterFormLayout);

        chkLogScale = new QCheckBox(ctrlPanel);
        chkLogScale->setObjectName("chkLogScale");

        ctrlLayout->addWidget(chkLogScale);

        btnCompute = new QPushButton(ctrlPanel);
        btnCompute->setObjectName("btnCompute");

        ctrlLayout->addWidget(btnCompute);

        btnReset = new QPushButton(ctrlPanel);
        btnReset->setObjectName("btnReset");

        ctrlLayout->addWidget(btnReset);

        lblTime = new QLabel(ctrlPanel);
        lblTime->setObjectName("lblTime");

        ctrlLayout->addWidget(lblTime);

        ctrlSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        ctrlLayout->addItem(ctrlSpacer);


        mainLayout->addWidget(ctrlPanel);

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


        mainLayout->addLayout(plotGrid);

        ViewerWindow->setCentralWidget(centralwidget);

        retranslateUi(ViewerWindow);

        QMetaObject::connectSlotsByName(ViewerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ViewerWindow)
    {
        ViewerWindow->setWindowTitle(QCoreApplication::translate("ViewerWindow", "Lab 7 \342\200\224 Optimized FFT Spectrum", nullptr));
        groupShape->setTitle(QCoreApplication::translate("ViewerWindow", "\320\244\320\276\321\200\320\274\320\260", nullptr));
        rbCircle->setText(QCoreApplication::translate("ViewerWindow", "\320\232\321\200\321\203\320\263", nullptr));
        rbSquare->setText(QCoreApplication::translate("ViewerWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202", nullptr));
        groupGrid->setTitle(QCoreApplication::translate("ViewerWindow", "\320\241\320\265\321\202\320\272\320\260", nullptr));
        cbSize->setItemText(0, QCoreApplication::translate("ViewerWindow", "64", nullptr));
        cbSize->setItemText(1, QCoreApplication::translate("ViewerWindow", "128", nullptr));
        cbSize->setItemText(2, QCoreApplication::translate("ViewerWindow", "256", nullptr));
        cbSize->setItemText(3, QCoreApplication::translate("ViewerWindow", "512", nullptr));
        cbSize->setItemText(4, QCoreApplication::translate("ViewerWindow", "1024", nullptr));

        groupSteps->setTitle(QCoreApplication::translate("ViewerWindow", "\320\250\320\260\320\263\320\270", nullptr));
        labelStepX->setText(QCoreApplication::translate("ViewerWindow", "\320\250\320\260\320\263 X (\320\274\320\274):", nullptr));
        labelStepFreq->setText(QCoreApplication::translate("ViewerWindow", "\320\250\320\260\320\263 \321\207\320\260\321\201\321\202\320\276\321\202\321\213 (1/\320\274\320\274):", nullptr));
        labelDiameter->setText(QCoreApplication::translate("ViewerWindow", "\320\224\320\270\320\260\320\274\320\265\321\202\321\200 (\320\274\320\274):", nullptr));
        chkLogScale->setText(QCoreApplication::translate("ViewerWindow", "\320\233\320\276\320\263. \321\210\320\272\320\260\320\273\320\260", nullptr));
        btnCompute->setText(QCoreApplication::translate("ViewerWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        btnReset->setText(QCoreApplication::translate("ViewerWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        lblTime->setText(QCoreApplication::translate("ViewerWindow", "\320\222\321\200\320\265\320\274\321\217: \342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewerWindow: public Ui_ViewerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_WINDOW_H
