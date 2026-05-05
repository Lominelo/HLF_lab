#include "fft_processor.h"
#include <cmath>
#include "fftw3.h"

void FFTProcessor::buildFunction(const FourierParams& p, Array2D<double>& func)
{
    int N = p.gridSize();
    double dx = p.stepX();
    double radius = p.m_funcDiameter / 2.0;
    double half = N / 2.0;

    func.Resize(N);
    func.SetAll(0.0);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            double x = (i - half) * dx;
            double y = (j - half) * dx;

            if (p.m_isCircular)
            {
                if (x * x + y * y <= radius * radius)
                    func(i, j) = 1.0;
            }
            else
            {
                if (std::fabs(x) <= radius && std::fabs(y) <= radius)
                    func(i, j) = 1.0;
            }
        }
    }
}

void FFTProcessor::computeFFT(ComplexArray& data)
{
    int N = data.GetRows();
    auto* ptr = reinterpret_cast<fftw_complex*>(data.RawPtr());

    fftw_plan plan = fftw_plan_dft_2d(N, N, ptr, ptr,
                                       FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

void FFTProcessor::shiftQuadrants(ComplexArray& data)
{
    int N = data.GetRows();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            data(i, j) *= sign;
        }
}

void FFTProcessor::run(const FourierParams& p,
                       Array2D<double>& func,
                       Array2D<double>& spectrum)
{
    int N = p.gridSize();

    buildFunction(p, func);

    ComplexArray cdata;
    cdata.FromReal(func);

    shiftQuadrants(cdata);
    computeFFT(cdata);
    shiftQuadrants(cdata);

    spectrum = cdata.Intensity();

    double mx = spectrum.FindMax();
    if (mx > 0.0)
        spectrum /= mx;
}
