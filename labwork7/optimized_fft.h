#pragma once
#include "../labwork4/array2d.h"
#include "../labwork4/complex_array.h"
#include "../labwork5/fourier_params.h"
#include <fftw3.h>

class OptimizedFFT {
public:
    OptimizedFFT();
    ~OptimizedFFT();

    void execute(const FourierParams& par,
                 Array2D<double>& func,
                 Array2D<double>& spectrum);

private:
    void buildShape(const FourierParams& par, Array2D<double>& func);
    void forwardFFT(ComplexArray& data);
    void applyShift(ComplexArray& data);
    void ensurePlan(int n);

    fftw_plan m_plan = nullptr;
    int m_planSize = 0;
    ComplexArray m_work;
};
