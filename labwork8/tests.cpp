#include <iostream>
#include <cmath>
#include <sstream>
#include "../labwork4/array2d.h"
#include "../labwork4/real_matrix.h"
#include "../labwork4/complex_array.h"
#include "../labwork5/fourier_params.h"

static const double EPS = 1e-9;

static bool near(double a, double b) { return std::fabs(a - b) < EPS; }

// --- Array2D tests ---

bool test_array2d_resize()
{
    Array2D<double> a;
    if (!a.IsEmpty()) return false;

    a.Resize(3, 4);
    if (a.GetRows() != 3 || a.GetCols() != 4) return false;
    if (a.IsSquare()) return false;

    a.Resize(5);
    if (a.GetRows() != 5 || a.GetCols() != 5) return false;
    if (!a.IsSquare()) return false;

    // zero size
    a.Resize(0, 0);
    if (!a.IsEmpty()) return false;

    // negative size throws
    try { a.Resize(-1); return false; }
    catch (const std::invalid_argument&) {}

    return true;
}

bool test_array2d_operators()
{
    Array2D<double> a;
    a.Resize(2, 3);
    a.SetAll(2.0);
    if (!near(a(0, 0), 2.0) || !near(a(1, 2), 2.0)) return false;
    if (!near(a.FindMax(), 2.0)) return false;

    // scalar +=
    a += 3.0;
    if (!near(a(0, 0), 5.0)) return false;

    // scalar *=
    a *= 2.0;
    if (!near(a(0, 0), 10.0)) return false;

    // scalar /=
    a /= 5.0;
    if (!near(a(0, 0), 2.0)) return false;

    // division by zero
    try { a /= 0.0; return false; }
    catch (const std::invalid_argument&) {}

    // array +=
    Array2D<double> b;
    b.Resize(2, 3);
    b.SetAll(1.0);
    a += b;
    if (!near(a(0, 0), 3.0)) return false;

    // array -=
    a -= b;
    if (!near(a(0, 0), 2.0)) return false;

    // array *= (element-wise)
    b.SetAll(3.0);
    a *= b;
    if (!near(a(0, 0), 6.0)) return false;

    // array /= (element-wise)
    b.SetAll(2.0);
    a /= b;
    if (!near(a(0, 0), 3.0)) return false;

    // size mismatch
    Array2D<double> c;
    c.Resize(1, 1);
    try { a += c; return false; }
    catch (const std::invalid_argument&) {}

    // out of range
    try { a(10, 10); return false; }
    catch (const std::out_of_range&) {}

    return true;
}

bool test_array2d_save_load()
{
    Array2D<double> a;
    a.Resize(2, 3);
    a(0, 0) = 1.5; a(0, 1) = 2.5; a(0, 2) = 3.5;
    a(1, 0) = 4.5; a(1, 1) = 5.5; a(1, 2) = 6.5;

    std::stringstream ss;
    a.Save(ss);

    Array2D<double> b;
    b.Load(ss);

    if (b.GetRows() != 2 || b.GetCols() != 3) return false;
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 3; ++c)
            if (!near(a(r, c), b(r, c))) return false;

    return true;
}

// --- RealMatrix tests ---

bool test_realmatrix_identity()
{
    RealMatrix m;
    m.Resize(3);
    m.MakeIdentity();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (!near(m(i, j), (i == j) ? 1.0 : 0.0)) return false;

    // 1x1 identity
    RealMatrix s;
    s.Resize(1);
    s.MakeIdentity();
    if (!near(s(0, 0), 1.0)) return false;

    // non-square throws
    RealMatrix ns;
    ns.Resize(2, 3);
    try { ns.MakeIdentity(); return false; }
    catch (const std::logic_error&) {}

    return true;
}

bool test_realmatrix_multiply()
{
    // I * M = M
    RealMatrix id;
    id.Resize(3);
    id.MakeIdentity();

    RealMatrix m;
    m.Resize(3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    m(2, 0) = 7; m(2, 1) = 8; m(2, 2) = 9;

    RealMatrix res = id * m;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (!near(res(i, j), m(i, j))) return false;

    // M * I = M
    res = m * id;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (!near(res(i, j), m(i, j))) return false;

    // incompatible dimensions
    RealMatrix a, b;
    a.Resize(2, 3);
    b.Resize(4, 2);
    try { auto r = a * b; (void)r; return false; }
    catch (const std::invalid_argument&) {}

    return true;
}

bool test_realmatrix_transpose()
{
    RealMatrix m;
    m.Resize(2, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;

    RealMatrix t = ~m;
    if (t.GetRows() != 3 || t.GetCols() != 2) return false;
    if (!near(t(0, 0), 1) || !near(t(1, 0), 2) || !near(t(2, 0), 3)) return false;
    if (!near(t(0, 1), 4) || !near(t(1, 1), 5) || !near(t(2, 1), 6)) return false;

    // transpose of transpose = original
    RealMatrix tt = ~t;
    if (tt.GetRows() != 2 || tt.GetCols() != 3) return false;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            if (!near(tt(i, j), m(i, j))) return false;

    return true;
}

bool test_realmatrix_throws()
{
    RealMatrix a, b;
    a.Resize(2);
    b.Resize(2);

    // operator*= throws
    try { a *= b; return false; }
    catch (const std::runtime_error&) {}

    // operator/= throws
    try { a /= b; return false; }
    catch (const std::runtime_error&) {}

    return true;
}

// --- ComplexArray tests ---

bool test_complex_amplitude()
{
    ComplexArray ca(2);
    ca(0, 0) = {3.0, 4.0};
    ca(0, 1) = {0.0, 1.0};
    ca(1, 0) = {1.0, 0.0};
    ca(1, 1) = {-3.0, -4.0};

    auto amp = ca.Amplitude();
    if (!near(amp(0, 0), 5.0)) return false;
    if (!near(amp(0, 1), 1.0)) return false;
    if (!near(amp(1, 0), 1.0)) return false;
    if (!near(amp(1, 1), 5.0)) return false;

    auto phase = ca.Phase();
    if (!near(phase(0, 0), std::atan2(4.0, 3.0))) return false;
    if (!near(phase(1, 0), 0.0)) return false;

    return true;
}

bool test_complex_intensity()
{
    ComplexArray ca(2);
    ca(0, 0) = {3.0, 4.0};
    ca(0, 1) = {1.0, 1.0};
    ca(1, 0) = {0.0, 0.0};
    ca(1, 1) = {2.0, 0.0};

    auto inten = ca.Intensity();
    // std::norm returns |z|^2
    if (!near(inten(0, 0), 25.0)) return false;
    if (!near(inten(0, 1), 2.0)) return false;
    if (!near(inten(1, 0), 0.0)) return false;
    if (!near(inten(1, 1), 4.0)) return false;

    return true;
}

bool test_complex_roundtrip()
{
    Array2D<double> src;
    src.Resize(3, 3);
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            src(r, c) = r * 3.0 + c + 0.5;

    ComplexArray ca;
    ca.FromReal(src);

    auto back = ca.ToReal();
    if (back.GetRows() != 3 || back.GetCols() != 3) return false;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (!near(back(r, c), src(r, c))) return false;

    // verify imaginary parts are zero after FromReal
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (!near(ca(r, c).imag(), 0.0)) return false;

    return true;
}

// --- FourierParams tests ---

bool test_params_linked()
{
    FourierParams p;

    // defaults: N=512, stepX=0.001, stepFreq=1/(512*0.001)
    if (p.gridSize() != 512) return false;
    if (!near(p.stepX(), 0.001)) return false;
    if (!near(p.stepFreq(), 1.0 / (512 * 0.001))) return false;

    // setStepX recalculates stepFreq
    p.setStepX(0.02);
    if (!near(p.stepX(), 0.02)) return false;
    double expected = 1.0 / (512 * 0.02);
    if (!near(p.stepFreq(), expected)) return false;

    // setStepFreq recalculates stepX
    p.setStepFreq(10.0);
    if (!near(p.stepFreq(), 10.0)) return false;
    expected = 1.0 / (512 * 10.0);
    if (!near(p.stepX(), expected)) return false;

    // linked relationship: stepX * stepFreq * N = 1
    double product = p.stepX() * p.stepFreq() * p.gridSize();
    if (!near(product, 1.0)) return false;

    // setGridSize recalculates stepFreq
    p.setStepX(0.01);
    p.setGridSize(1024);
    if (p.gridSize() != 1024) return false;
    if (!near(p.stepFreq(), 1.0 / (1024 * 0.01))) return false;

    // reset restores defaults
    p.reset();
    if (p.gridSize() != 512) return false;
    if (!near(p.stepX(), 0.001)) return false;
    if (!near(p.m_funcDiameter, 2.0)) return false;
    if (!p.m_isCircular) return false;

    // invalid values are ignored
    p.setStepX(-1.0);
    if (!near(p.stepX(), 0.001)) return false;
    p.setStepFreq(0.0);
    if (!near(p.stepFreq(), 1.0 / (512 * 0.001))) return false;
    p.setGridSize(0);
    if (p.gridSize() != 512) return false;

    return true;
}

int main()
{
    struct { const char* name; bool (*fn)(); } tests[] = {
        {"Array2D resize",           test_array2d_resize},
        {"Array2D operators",        test_array2d_operators},
        {"Array2D save/load",        test_array2d_save_load},
        {"RealMatrix identity",      test_realmatrix_identity},
        {"RealMatrix multiply",      test_realmatrix_multiply},
        {"RealMatrix transpose",     test_realmatrix_transpose},
        {"RealMatrix throws",        test_realmatrix_throws},
        {"ComplexArray amplitude",   test_complex_amplitude},
        {"ComplexArray intensity",   test_complex_intensity},
        {"ComplexArray roundtrip",   test_complex_roundtrip},
        {"FourierParams linked",     test_params_linked},
    };

    int passed = 0, failed = 0;
    for (auto& t : tests)
    {
        bool ok = false;
        try { ok = t.fn(); }
        catch (const std::exception& e) {
            std::cerr << "  exception: " << e.what() << "\n";
        }
        std::cout << (ok ? "[PASS]" : "[FAIL]") << " " << t.name << "\n";
        if (ok) ++passed; else ++failed;
    }
    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed;
}
