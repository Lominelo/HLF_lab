#pragma once
#include <QMainWindow>
#include "../labwork5/fourier_params.h"
#include "../labwork4/array2d.h"
#include "fft_processor.h"

class QCustomPlot;

namespace Ui { class SpectrumWindow; }

class SpectrumWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpectrumWindow(QWidget* parent = nullptr);
    ~SpectrumWindow();

private slots:
    void onCompute();
    void onReset();

private:
    void drawColorMap(const Array2D<double>& data, QCustomPlot* plot,
                      double step, const QString& title);
    void drawSections(const Array2D<double>& data);

    Ui::SpectrumWindow *ui;
    FourierParams m_params;
    FFTProcessor  m_fft;
};
