#include "real_matrix.h"
#include "complex_array.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>

#ifdef FFTW_AVAILABLE
#include <fftw3.h>
#endif

#ifdef BOOST_AVAILABLE
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#endif

using std::cout;

void show_matrix(const RealMatrix& m, const char* label)
{
    cout << label << " [" << m.GetRows() << "x" << m.GetCols() << "]:\n";
    for (int r = 0; r < m.GetRows(); ++r)
    {
        for (int c = 0; c < m.GetCols(); ++c)
            cout << std::fixed << std::setprecision(2) << std::setw(8) << m(r, c);
        cout << "\n";
    }
}

void show_complex(const ComplexArray& m, const char* label)
{
    cout << label << " [" << m.GetRows() << "x" << m.GetCols() << "]:\n";
    for (int r = 0; r < m.GetRows(); ++r)
    {
        for (int c = 0; c < m.GetCols(); ++c)
        {
            auto v = m(r, c);
            cout << "(" << std::fixed << std::setprecision(2)
                 << v.real() << "," << v.imag() << ") ";
        }
        cout << "\n";
    }
}

void show_real_array(const Array2D<double>& a, const char* label)
{
    cout << label << ":\n";
    for (int r = 0; r < a.GetRows(); ++r)
    {
        for (int c = 0; c < a.GetCols(); ++c)
            cout << std::fixed << std::setprecision(4) << std::setw(10) << a(r, c);
        cout << "\n";
    }
}

int main()
{
    cout << "=== Lab 4: Inheritance ===\n\n";

    // 1. basic RealMatrix
    cout << "-- Test 1: create and fill matrix --\n";
    RealMatrix a;
    a.Resize(3, 3);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            a(i, j) = i * 3.0 + j + 1.0;
    show_matrix(a, "a");

    // 2. identity
    cout << "\n-- Test 2: identity matrix --\n";
    RealMatrix eye;
    eye.Resize(3);
    eye.MakeIdentity();
    show_matrix(eye, "eye");

    // 3. matrix multiply
    cout << "\n-- Test 3: matrix multiplication --\n";
    RealMatrix b;
    b.Resize(3, 3);
    b(0,0)=2; b(0,1)=0; b(0,2)=1;
    b(1,0)=0; b(1,1)=1; b(1,2)=0;
    b(2,0)=1; b(2,1)=0; b(2,2)=3;
    show_matrix(b, "b");
    RealMatrix ab = a * b;
    show_matrix(ab, "a*b");

    // 4. transpose
    cout << "\n-- Test 4: transpose --\n";
    RealMatrix rect;
    rect.Resize(2, 4);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 4; ++j)
            rect(i, j) = i * 4.0 + j;
    show_matrix(rect, "rect");
    RealMatrix rt = ~rect;
    show_matrix(rt, "~rect");

    // 5. scalar ops
    cout << "\n-- Test 5: scalar operations --\n";
    RealMatrix s;
    s.Resize(2);
    s.SetAll(5.0);
    show_matrix(s, "s (all 5)");
    static_cast<Array2D<double>&>(s) += 3.0;
    show_matrix(s, "s += 3");
    static_cast<Array2D<double>&>(s) *= 2.0;
    show_matrix(s, "s *= 2");

    // 6. element-wise add/sub
    cout << "\n-- Test 6: element-wise +=, -= --\n";
    RealMatrix p, q;
    p.Resize(2); q.Resize(2);
    p.SetAll(10.0); q.SetAll(3.0);
    p += q;
    show_matrix(p, "p after += q");
    p -= q;
    show_matrix(p, "p after -= q");

    // 7. override *= throws
    cout << "\n-- Test 7: operator*= override throws --\n";
    try
    {
        RealMatrix x, y;
        x.Resize(2); y.Resize(2);
        x *= y;
    }
    catch (const std::exception& e)
    {
        cout << "caught: " << e.what() << "\n";
    }

    // 8. save / load
    cout << "\n-- Test 8: save and load --\n";
    {
        std::stringstream ss;
        a.Save(ss);
        RealMatrix loaded;
        loaded.Load(ss);
        show_matrix(loaded, "loaded from stream");
    }

    // 9. ComplexArray basics
    cout << "\n-- Test 9: ComplexArray --\n";
    ComplexArray ca(3);
    ca(0,0) = {1, 2}; ca(0,1) = {3, 0}; ca(0,2) = {0, 1};
    ca(1,0) = {2, 1}; ca(1,1) = {0, 0}; ca(1,2) = {4, 3};
    ca(2,0) = {1, 1}; ca(2,1) = {2, 2}; ca(2,2) = {3, 4};
    show_complex(ca, "ca");

    // 10. amplitude, phase, intensity
    cout << "\n-- Test 10: amplitude / phase / intensity --\n";
    ComplexArray ca2(2);
    ca2(0,0) = {3, 4};
    ca2(0,1) = {1, 0};
    ca2(1,0) = {0, 2};
    ca2(1,1) = {1, 1};
    show_real_array(ca2.Amplitude(), "amplitude");
    show_real_array(ca2.Phase(), "phase");
    show_real_array(ca2.Intensity(), "intensity");

    // 11. ToReal / FromReal
    cout << "\n-- Test 11: ToReal / FromReal --\n";
    Array2D<double> re = ca2.ToReal();
    show_real_array(re, "real part of ca2");
    ComplexArray ca3;
    ca3.FromReal(re);
    show_complex(ca3, "ca3 from real");

    // 12. write files
    cout << "\n-- Test 12: write to files --\n";
    ca2.WriteAmplitude("amp.txt");
    ca2.WritePhase("phase.txt");
    ca2.WriteIntensity("intensity.txt");
    ca2.WriteReal("real.txt");
    ca2.WriteImag("imag.txt");
    cout << "files written: amp.txt phase.txt intensity.txt real.txt imag.txt\n";

    // 13. boost comparison
    cout << "\n-- Test 13: matrix multiply benchmark --\n";
    {
        const int N = 256;
        RealMatrix m1, m2;
        m1.Resize(N, N);
        m2.Resize(N, N);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                m1(i, j) = 1.0 + (i + j) % 7;
                m2(i, j) = 1.0 + (i * j) % 7;
            }

        auto t0 = std::chrono::high_resolution_clock::now();
        RealMatrix mr = m1 * m2;
        auto t1 = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(t1 - t0).count();
        cout << "custom " << N << "x" << N << " multiply: " << dt << " s\n";

#ifdef BOOST_AVAILABLE
        using namespace boost::numeric::ublas;
        matrix<double> bm1(N, N), bm2(N, N);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                bm1(i, j) = 1.0 + (i + j) % 7;
                bm2(i, j) = 1.0 + (i * j) % 7;
            }
        t0 = std::chrono::high_resolution_clock::now();
        matrix<double> br = prod(bm1, bm2);
        t1 = std::chrono::high_resolution_clock::now();
        double bt = std::chrono::duration<double>(t1 - t0).count();
        cout << "boost multiply: " << bt << " s\n";
#else
        cout << "boost not available\n";
#endif
    }

    // 14. FFTW
    cout << "\n-- Test 14: 2D FFT --\n";
#ifdef FFTW_AVAILABLE
    {
        const int SZ = 512;
        ComplexArray fin(SZ);
        fin.SetAll(std::complex<double>(1.0, 0.0));

        fftw_complex* in_ptr = reinterpret_cast<fftw_complex*>(fin.RawPtr());
        fftw_complex* out_ptr = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * SZ * SZ);
        fftw_plan plan = fftw_plan_dft_2d(SZ, SZ, in_ptr, out_ptr, FFTW_FORWARD, FFTW_ESTIMATE);

        auto t0 = std::chrono::high_resolution_clock::now();
        fftw_execute(plan);
        auto t1 = std::chrono::high_resolution_clock::now();
        double dt = std::chrono::duration<double>(t1 - t0).count();
        cout << "FFT " << SZ << "x" << SZ << ": " << dt << " s\n";
        cout << "DC component: " << out_ptr[0][0] << " + " << out_ptr[0][1] << "i\n";

        ComplexArray fout(SZ);
        for (int r = 0; r < SZ; ++r)
            for (int c = 0; c < SZ; ++c)
            {
                int idx = r * SZ + c;
                fout(r, c) = std::complex<double>(out_ptr[idx][0], out_ptr[idx][1]);
            }
        fout.WriteAmplitude("fft_result.txt");
        cout << "FFT amplitude written to fft_result.txt\n";

        fftw_destroy_plan(plan);
        fftw_free(out_ptr);
    }
#else
    cout << "fftw not available\n";
#endif

    cout << "\nAll tests done.\n";
    return 0;
}
