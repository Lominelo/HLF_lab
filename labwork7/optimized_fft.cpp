#include "optimized_fft.h"
#include <cmath>
#include <complex>

OptimizedFFT::OptimizedFFT() = default;

OptimizedFFT::~OptimizedFFT()
{
    if (m_plan)
        fftw_destroy_plan(m_plan);
}

// Optimization 1: cache FFTW plan, recreate only when size changes.
// Uses FFTW_MEASURE instead of FFTW_ESTIMATE for better kernel selection.
void OptimizedFFT::ensurePlan(int n)
{
    if (m_planSize == n && m_plan)
        return;

    if (m_plan)
        fftw_destroy_plan(m_plan);

    // Optimization 2: pre-allocate work buffer, reuse across calls
    m_work.Resize(n);
    auto* ptr = reinterpret_cast<fftw_complex*>(m_work.RawPtr());
    m_plan = fftw_plan_dft_2d(n, n, ptr, ptr, FFTW_FORWARD, FFTW_MEASURE);
    m_planSize = n;
}

// Optimization 3: pre-compute r_sq outside loop, use integer distance squared,
// exploit quadrant symmetry for circular shape
void OptimizedFFT::buildShape(const FourierParams& par, Array2D<double>& func)
{
    int N = par.gridSize();
    double dx = par.stepX();
    double radius = par.m_funcDiameter / 2.0;

    func.Resize(N);
    func.SetAll(0.0);

    int half = N / 2;

    if (par.m_isCircular)
    {
        double r_sq = radius * radius;
        double dx_sq = dx * dx;

        // Only iterate over one quadrant, mirror to the other three
        for (int di = 0; di <= half; ++di)
        {
            int di_sq = di * di;
            for (int dj = 0; dj <= half; ++dj)
            {
                double dist_sq = (di_sq + dj * dj) * dx_sq;
                if (dist_sq <= r_sq)
                {
                    int r0 = half - di, r1 = half + di;
                    int c0 = half - dj, c1 = half + dj;

                    if (r0 >= 0 && r0 < N && c0 >= 0 && c0 < N) func(r0, c0) = 1.0;
                    if (r0 >= 0 && r0 < N && c1 >= 0 && c1 < N) func(r0, c1) = 1.0;
                    if (r1 >= 0 && r1 < N && c0 >= 0 && c0 < N) func(r1, c0) = 1.0;
                    if (r1 >= 0 && r1 < N && c1 >= 0 && c1 < N) func(r1, c1) = 1.0;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            double x = (i - half) * dx;
            if (std::fabs(x) > radius) continue;
            for (int j = 0; j < N; ++j)
            {
                double y = (j - half) * dx;
                if (std::fabs(y) <= radius)
                    func(i, j) = 1.0;
            }
        }
    }
}

void OptimizedFFT::applyShift(ComplexArray& data)
{
    int N = data.GetRows();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            double sign = ((i + j) & 1) ? -1.0 : 1.0;
            data(i, j) *= sign;
        }
}

void OptimizedFFT::forwardFFT(ComplexArray& data)
{
    fftw_execute(m_plan);
}

void OptimizedFFT::execute(const FourierParams& par,
                           Array2D<double>& func,
                           Array2D<double>& spectrum)
{
    int N = par.gridSize();

    ensurePlan(N);
    buildShape(par, func);

    // Fill work buffer from func (reuse pre-allocated m_work)
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            m_work(r, c) = std::complex<double>(func(r, c), 0.0);

    applyShift(m_work);
    forwardFFT(m_work);
    applyShift(m_work);

    // Optimization 5: use std::norm() directly (avoids sqrt inside std::abs)
    spectrum.Resize(N);
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            spectrum(r, c) = std::norm(m_work(r, c));

    double mx = spectrum.FindMax();
    if (mx > 0.0)
        spectrum /= mx;
}
