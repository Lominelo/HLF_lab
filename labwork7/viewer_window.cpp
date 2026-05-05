#include "viewer_window.h"
#include "ui_viewer_window.h"
#include "qcustomplot.h"
#include <QElapsedTimer>
#include <cmath>

ViewerWindow::ViewerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewerWindow)
{
    ui->setupUi(this);
    ui->cbSize->setCurrentIndex(3); // 512

    connect(ui->btnCompute, &QPushButton::clicked, this, &ViewerWindow::onCompute);
    connect(ui->btnReset,   &QPushButton::clicked, this, &ViewerWindow::onReset);

    onReset();
}

ViewerWindow::~ViewerWindow()
{
    delete ui;
}

void ViewerWindow::onReset()
{
    m_params.reset();
    ui->rbCircle->setChecked(m_params.m_isCircular);
    ui->rbSquare->setChecked(!m_params.m_isCircular);
    ui->cbSize->setCurrentText(QString::number(m_params.gridSize()));
    ui->edStepX->setText(QString::number(m_params.stepX()));
    ui->edStepFreq->setText(QString::number(m_params.stepFreq()));
    ui->edDiameter->setText(QString::number(m_params.m_funcDiameter));
    ui->chkLogScale->setChecked(false);
    ui->lblTime->setText("Время: —");

    ui->plotFunc->clearPlottables();
    ui->plotFunc->replot();
    ui->plotSpectrum->clearPlottables();
    ui->plotSpectrum->replot();
    ui->plotSections->clearGraphs();
    ui->plotSections->replot();
}

void ViewerWindow::onCompute()
{
    m_params.m_isCircular = ui->rbCircle->isChecked();
    int n = ui->cbSize->currentText().toInt();
    double dx = ui->edStepX->text().toDouble();
    m_params.setStepX(dx, n);
    m_params.m_funcDiameter = ui->edDiameter->text().toDouble();

    ui->edStepFreq->setText(QString::number(m_params.stepFreq()));

    Array2D<double> func;
    Array2D<double> spectrum;

    QElapsedTimer timer;
    timer.start();
    m_fft.execute(m_params, func, spectrum);
    qint64 elapsed = timer.elapsed();

    ui->lblTime->setText(QString("Время: %1 мс").arg(elapsed));

    bool useLog = ui->chkLogScale->isChecked();
    drawColorMap(func, ui->plotFunc, m_params.stepX(), "Function", false);
    drawColorMap(spectrum, ui->plotSpectrum, m_params.stepFreq(), "Spectrum", useLog);
    drawSections(spectrum);
}

void ViewerWindow::drawColorMap(const Array2D<double>& data,
                                QCustomPlot* plot,
                                double step,
                                const QString& title,
                                bool logScale)
{
    plot->clearPlottables();

    // Remove old title if present (row 0 is title, row 1 is axis rect when title exists)
    if (plot->plotLayout()->rowCount() > 1) {
        plot->plotLayout()->remove(plot->plotLayout()->element(0, 0));
        plot->plotLayout()->simplify();
    }

    int N = data.GetRows();
    double halfRange = N * step / 2.0;

    auto* colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
    colorMap->data()->setSize(N, N);
    colorMap->data()->setRange(QCPRange(-halfRange, halfRange),
                               QCPRange(-halfRange, halfRange));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            double val = data(i, j);
            if (logScale)
                val = std::log10(1.0 + val * 100.0) / std::log10(101.0);
            colorMap->data()->setCell(i, j, val);
        }

    colorMap->setGradient(QCPColorGradient::gpJet);
    colorMap->rescaleDataRange(true);

    plot->rescaleAxes();
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0,
        new QCPTextElement(plot, title, QFont("sans", 10, QFont::Bold)));
    plot->replot();
}

void ViewerWindow::drawSections(const Array2D<double>& data)
{
    ui->plotSections->clearGraphs();

    int N = data.GetRows();
    int mid = N / 2;
    double df = m_params.stepFreq();
    double halfRange = N * df / 2.0;

    bool useLog = ui->chkLogScale->isChecked();

    QVector<double> freq(N), secX(N), secY(N);
    for (int k = 0; k < N; ++k)
    {
        freq[k] = -halfRange + k * df;
        double vx = data(mid, k);
        double vy = data(k, mid);
        if (useLog)
        {
            vx = std::log10(1.0 + vx * 100.0) / std::log10(101.0);
            vy = std::log10(1.0 + vy * 100.0) / std::log10(101.0);
        }
        secX[k] = vx;
        secY[k] = vy;
    }

    auto* gX = ui->plotSections->addGraph();
    gX->setData(freq, secX);
    gX->setPen(QPen(Qt::blue));
    gX->setName("X section");

    auto* gY = ui->plotSections->addGraph();
    gY->setData(freq, secY);
    gY->setPen(QPen(Qt::red));
    gY->setName("Y section");

    ui->plotSections->xAxis->setLabel("Frequency (1/mm)");
    ui->plotSections->yAxis->setLabel("Intensity");
    ui->plotSections->legend->setVisible(true);
    ui->plotSections->rescaleAxes();
    ui->plotSections->replot();
}
