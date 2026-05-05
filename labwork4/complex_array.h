#pragma once
#include "array2d.h"
#include <complex>
#include <string>

class ComplexArray : public Array2D<std::complex<double>>
{
public:
    ComplexArray() = default;
    explicit ComplexArray(int n);
    ~ComplexArray() override = default;

    Array2D<double> Amplitude() const;
    Array2D<double> Phase() const;
    Array2D<double> Intensity() const;
    Array2D<double> ToReal() const;

    void FromReal(const Array2D<double>& src);

    void WriteAmplitude(const std::string& path) const;
    void WritePhase(const std::string& path) const;
    void WriteIntensity(const std::string& path) const;
    void WriteReal(const std::string& path) const;
    void WriteImag(const std::string& path) const;
};
