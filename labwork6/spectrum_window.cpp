#include "spectrum_window.h"
#include "ui_spectrum_window.h"
#include "qcustomplot.h"

SpectrumWindow::SpectrumWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SpectrumWindow)
{
    ui->setupUi(this);
    ui->cbSize->setCurrentIndex(3); // 512

    connect(ui->btnCompute, &QPushButton::clicked, this, &SpectrumWindow::onCompute);
    connect(ui->btnReset,   &QPushButton::clicked, this, &SpectrumWindow::onReset);

    onReset();
}

SpectrumWindow::~SpectrumWindow()
{
    delete ui;
}

void SpectrumWindow::onReset()
{
    m_params.reset();
    ui->rbCircle->setChecked(m_params.m_isCircular);
    ui->rbSquare->setChecked(!m_params.m_isCircular);
    ui->cbSize->setCurrentText(QString::number(m_params.gridSize()));
    ui->edStepX->setText(QString::number(m_params.stepX()));
    ui->edStepFreq->setText(QString::number(m_params.stepFreq()));
    ui->edDiameter->setText(QString::number(m_params.m_funcDiameter));

    ui->plotFunc->clearPlottables();
    ui->plotFunc->replot();
    ui->plotSpectrum->clearPlottables();
    ui->plotSpectrum->replot();
    ui->plotSections->clearGraphs();
    ui->plotSections->replot();
}

void SpectrumWindow::onCompute()
{
    m_params.m_isCircular = ui->rbCircle->isChecked();
    m_params.setGridSize(ui->cbSize->currentText().toInt());
    m_params.setStepX(ui->edStepX->text().toDouble());
    m_params.m_funcDiameter = ui->edDiameter->text().toDouble();

    ui->edStepFreq->setText(QString::number(m_params.stepFreq()));

    Array2D<double> func;
    Array2D<double> spectrum;
    m_fft.run(m_params, func, spectrum);

    drawColorMap(func, ui->plotFunc, m_params.stepX(), "Function");
    drawColorMap(spectrum, ui->plotSpectrum, m_params.stepFreq(), "Spectrum");
    drawSections(spectrum);
}

void SpectrumWindow::drawColorMap(const Array2D<double>& data,
                                  QCustomPlot* plot,
                                  double step,
                                  const QString& title)
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
            colorMap->data()->setCell(i, j, data(i, j));

    colorMap->setGradient(QCPColorGradient::gpJet);
    colorMap->rescaleDataRange(true);

    plot->rescaleAxes();
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0,
        new QCPTextElement(plot, title, QFont("sans", 10, QFont::Bold)));
    plot->replot();
}

void SpectrumWindow::drawSections(const Array2D<double>& data)
{
    ui->plotSections->clearGraphs();

    int N = data.GetRows();
    int mid = N / 2;
    double df = m_params.stepFreq();
    double halfRange = N * df / 2.0;

    QVector<double> freq(N), secX(N), secY(N);
    for (int k = 0; k < N; ++k)
    {
        freq[k] = -halfRange + k * df;
        secX[k] = data(mid, k);
        secY[k] = data(k, mid);
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
