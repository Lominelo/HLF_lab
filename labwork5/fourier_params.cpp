#include "fourier_params.h"

FourierParams::FourierParams()
{
    reset();
}

void FourierParams::reset()
{
    m_gridSize     = 512;
    m_stepX        = 0.001;                         // mm
    m_stepFreq     = 1.0 / (m_gridSize * m_stepX);  // 1/mm
    m_funcDiameter = 2.0;
    m_isCircular   = true;
}

void FourierParams::setStepX(double val, int size)
{
    if (val <= 0.0 || size <= 0)
        return;
    m_gridSize = size;
    m_stepX    = val;
    m_stepFreq = 1.0 / (m_gridSize * m_stepX);
}

void FourierParams::setStepX(double val)
{
    setStepX(val, m_gridSize);
}

void FourierParams::setStepFreq(double val, int size)
{
    if (val <= 0.0 || size <= 0)
        return;
    m_gridSize = size;
    m_stepFreq = val;
    m_stepX    = 1.0 / (m_gridSize * m_stepFreq);
}

void FourierParams::setStepFreq(double val)
{
    setStepFreq(val, m_gridSize);
}

void FourierParams::setGridSize(int n)
{
    if (n <= 0)
        return;
    m_gridSize = n;
    m_stepFreq = 1.0 / (m_gridSize * m_stepX);
}

double FourierParams::stepX()    const { return m_stepX; }
double FourierParams::stepFreq() const { return m_stepFreq; }
int    FourierParams::gridSize() const { return m_gridSize; }
