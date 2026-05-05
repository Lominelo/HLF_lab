#include "complex_array.h"
#include <fstream>
#include <cmath>

ComplexArray::ComplexArray(int n)
{
    Resize(n);
}

Array2D<double> ComplexArray::Amplitude() const
{
    Array2D<double> out;
    out.Resize(m_rows, m_cols);
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            out(r, c) = std::abs((*this)(r, c));
    return out;
}

Array2D<double> ComplexArray::Phase() const
{
    Array2D<double> out;
    out.Resize(m_rows, m_cols);
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            out(r, c) = std::arg((*this)(r, c));
    return out;
}

Array2D<double> ComplexArray::Intensity() const
{
    Array2D<double> out;
    out.Resize(m_rows, m_cols);
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            out(r, c) = std::norm((*this)(r, c));
    return out;
}

Array2D<double> ComplexArray::ToReal() const
{
    Array2D<double> out;
    out.Resize(m_rows, m_cols);
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            out(r, c) = (*this)(r, c).real();
    return out;
}

void ComplexArray::FromReal(const Array2D<double>& src)
{
    Resize(src.GetRows(), src.GetCols());
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            (*this)(r, c) = std::complex<double>(src(r, c), 0.0);
}

static void dump_real_array(const Array2D<double>& arr, const std::string& path)
{
    std::ofstream f(path);
    arr.Save(f);
}

void ComplexArray::WriteAmplitude(const std::string& path) const
{
    dump_real_array(Amplitude(), path);
}

void ComplexArray::WritePhase(const std::string& path) const
{
    dump_real_array(Phase(), path);
}

void ComplexArray::WriteIntensity(const std::string& path) const
{
    dump_real_array(Intensity(), path);
}

void ComplexArray::WriteReal(const std::string& path) const
{
    dump_real_array(ToReal(), path);
}

void ComplexArray::WriteImag(const std::string& path) const
{
    Array2D<double> out;
    out.Resize(m_rows, m_cols);
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            out(r, c) = (*this)(r, c).imag();
    dump_real_array(out, path);
}
