#pragma once
#include "../labwork4/array2d.h"
#include "../labwork4/complex_array.h"
#include "../labwork5/fourier_params.h"

class FFTProcessor
{
public:
    void buildFunction(const FourierParams& p, Array2D<double>& func);
    void computeFFT(ComplexArray& data);
    void shiftQuadrants(ComplexArray& data);
    void run(const FourierParams& p,
             Array2D<double>& func,
             Array2D<double>& spectrum);
};
