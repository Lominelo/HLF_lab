#ifndef PARAM_WINDOW_H
#define PARAM_WINDOW_H

#include <QMainWindow>
#include "fourier_params.h"

namespace Ui { class ParamWindow; }

class ParamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParamWindow(QWidget *parent = nullptr);
    ~ParamWindow();

private slots:
    void onStepXEdited();
    void onStepFreqEdited();
    void onGridSizeChanged(int index);
    void onShapeToggled();
    void onDiameterEdited();
    void onResetClicked();

private:
    void syncUIFromParams();

    Ui::ParamWindow *ui;
    FourierParams m_params;
    bool m_updating;
};

#endif // PARAM_WINDOW_H
