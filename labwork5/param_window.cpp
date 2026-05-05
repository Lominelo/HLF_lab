#include "param_window.h"
#include "ui_param_window.h"

#include <QDoubleValidator>

ParamWindow::ParamWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParamWindow)
    , m_updating(false)
{
    ui->setupUi(this);
    ui->cbSize->setCurrentIndex(3); // 512

    auto *posValidator = new QDoubleValidator(0.0, 1e12, 10, this);
    posValidator->setNotation(QDoubleValidator::ScientificNotation);
    ui->edStepX->setValidator(posValidator);
    ui->edStepFreq->setValidator(posValidator);
    ui->edDiameter->setValidator(new QDoubleValidator(0.0, 1e12, 6, this));

    connect(ui->edStepX,    &QLineEdit::editingFinished, this, &ParamWindow::onStepXEdited);
    connect(ui->edStepFreq, &QLineEdit::editingFinished, this, &ParamWindow::onStepFreqEdited);
    connect(ui->cbSize, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ParamWindow::onGridSizeChanged);
    connect(ui->rbCircle, &QRadioButton::toggled, this, &ParamWindow::onShapeToggled);
    connect(ui->edDiameter, &QLineEdit::editingFinished, this, &ParamWindow::onDiameterEdited);
    connect(ui->btnReset, &QPushButton::clicked, this, &ParamWindow::onResetClicked);

    syncUIFromParams();
}

ParamWindow::~ParamWindow()
{
    delete ui;
}

void ParamWindow::syncUIFromParams()
{
    m_updating = true;

    ui->edStepX->setText(QString::number(m_params.stepX(), 'g', 6));
    ui->edStepFreq->setText(QString::number(m_params.stepFreq(), 'g', 6));
    ui->edDiameter->setText(QString::number(m_params.m_funcDiameter, 'g', 6));

    int idx = ui->cbSize->findText(QString::number(m_params.gridSize()));
    if (idx >= 0)
        ui->cbSize->setCurrentIndex(idx);

    ui->rbCircle->setChecked(m_params.m_isCircular);
    ui->rbSquare->setChecked(!m_params.m_isCircular);

    m_updating = false;
}

void ParamWindow::onStepXEdited()
{
    if (m_updating) return;
    bool ok = false;
    double v = ui->edStepX->text().toDouble(&ok);
    if (!ok || v <= 0.0) return;
    int n = ui->cbSize->currentText().toInt();
    m_params.setStepX(v, n);
    syncUIFromParams();
}

void ParamWindow::onStepFreqEdited()
{
    if (m_updating) return;
    bool ok = false;
    double v = ui->edStepFreq->text().toDouble(&ok);
    if (!ok || v <= 0.0) return;
    int n = ui->cbSize->currentText().toInt();
    m_params.setStepFreq(v, n);
    syncUIFromParams();
}

void ParamWindow::onGridSizeChanged(int /*index*/)
{
    if (m_updating) return;
    int n = ui->cbSize->currentText().toInt();
    if (n <= 0) return;
    m_params.setGridSize(n);
    syncUIFromParams();
}

void ParamWindow::onShapeToggled()
{
    if (m_updating) return;
    m_params.m_isCircular = ui->rbCircle->isChecked();
}

void ParamWindow::onDiameterEdited()
{
    if (m_updating) return;
    bool ok = false;
    double v = ui->edDiameter->text().toDouble(&ok);
    if (ok && v >= 0.0)
        m_params.m_funcDiameter = v;
}

void ParamWindow::onResetClicked()
{
    m_params.reset();
    syncUIFromParams();
}
