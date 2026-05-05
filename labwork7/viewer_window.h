#pragma once
#include <QMainWindow>
#include "../labwork5/fourier_params.h"
#include "../labwork4/array2d.h"
#include "optimized_fft.h"

class QCustomPlot;

namespace Ui { class ViewerWindow; }

class ViewerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ViewerWindow(QWidget* parent = nullptr);
    ~ViewerWindow();

private slots:
    void onCompute();
    void onReset();

private:
    void drawColorMap(const Array2D<double>& data, QCustomPlot* plot,
                      double step, const QString& title, bool logScale);
    void drawSections(const Array2D<double>& data);

    Ui::ViewerWindow *ui;
    FourierParams m_params;
    OptimizedFFT  m_fft;
};
