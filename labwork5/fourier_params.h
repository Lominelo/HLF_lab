#ifndef FOURIER_PARAMS_H
#define FOURIER_PARAMS_H

class FourierParams
{
    double m_stepX;      // spatial domain step (mm)
    double m_stepFreq;   // frequency domain step (1/mm)
    int    m_gridSize;   // sample count N

public:
    double m_funcDiameter; // diameter (circle) or side length (square), mm
    bool   m_isCircular;   // true = circle, false = square

    FourierParams();
    ~FourierParams() = default;

    void reset();

    // setting one step recalculates the other via: stepX = 1/(N * stepFreq)
    void setStepX(double val, int size);
    void setStepX(double val);
    void setStepFreq(double val, int size);
    void setStepFreq(double val);
    void setGridSize(int n);

    double stepX() const;
    double stepFreq() const;
    int    gridSize() const;
};

#endif // FOURIER_PARAMS_H
