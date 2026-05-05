#include "real_matrix.h"

void RealMatrix::MakeIdentity()
{
    if (!IsSquare())
        throw std::logic_error("must be square for identity");
    SetAll(0.0);
    for (int i = 0; i < m_rows; ++i)
        (*this)(i, i) = 1.0;
}

void RealMatrix::CheckMultiplyCompat(const RealMatrix& rhs) const
{
    if (m_cols != rhs.m_rows)
        throw std::invalid_argument("incompatible dimensions for multiplication");
}

RealMatrix RealMatrix::operator*(const RealMatrix& rhs) const
{
    CheckMultiplyCompat(rhs);
    RealMatrix res;
    res.Resize(m_rows, rhs.m_cols);
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < rhs.m_cols; ++j)
        {
            double s = 0.0;
            for (int k = 0; k < m_cols; ++k)
                s += (*this)(i, k) * rhs(k, j);
            res(i, j) = s;
        }
    return res;
}

RealMatrix RealMatrix::operator~() const
{
    RealMatrix res;
    res.Resize(m_cols, m_rows);
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_cols; ++j)
            res(j, i) = (*this)(i, j);
    return res;
}

Array2D<double>& RealMatrix::operator*=(const Array2D<double>&)
{
    throw std::runtime_error("element-wise *= forbidden for RealMatrix, use operator* instead");
}

Array2D<double>& RealMatrix::operator/=(const Array2D<double>&)
{
    throw std::runtime_error("element-wise /= forbidden for RealMatrix");
}
