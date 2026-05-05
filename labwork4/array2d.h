#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>

template <typename T>
class Array2D
{
protected:
    int m_rows = 0;
    int m_cols = 0;
    std::vector<T> m_buf;

public:
    Array2D() = default;
    virtual ~Array2D() = default;

    void Resize(int n)
    {
        if (n < 0)
            throw std::invalid_argument("negative size");
        m_rows = n;
        m_cols = n;
        m_buf.assign(n * n, T{});
    }

    void Resize(int rows, int cols)
    {
        if (rows < 0 || cols < 0)
            throw std::invalid_argument("negative size");
        m_rows = rows;
        m_cols = cols;
        m_buf.assign(rows * cols, T{});
    }

    int GetRows() const { return m_rows; }
    int GetCols() const { return m_cols; }

    T& operator()(int r, int c)
    {
        if (r < 0 || r >= m_rows || c < 0 || c >= m_cols)
            throw std::out_of_range("index out of bounds");
        return m_buf[r * m_cols + c];
    }

    const T& operator()(int r, int c) const
    {
        if (r < 0 || r >= m_rows || c < 0 || c >= m_cols)
            throw std::out_of_range("index out of bounds");
        return m_buf[r * m_cols + c];
    }

    bool IsSquare() const { return m_rows == m_cols && m_rows > 0; }
    bool IsEmpty() const { return m_rows == 0 || m_cols == 0; }

    bool SameSize(const Array2D<T>& other) const
    {
        return m_rows == other.m_rows && m_cols == other.m_cols;
    }

    void SetAll(T val)
    {
        std::fill(m_buf.begin(), m_buf.end(), val);
    }

    T* RawPtr() { return m_buf.data(); }

    T FindMax() const
    {
        if (m_buf.empty())
            throw std::runtime_error("empty array");
        return *std::max_element(m_buf.begin(), m_buf.end());
    }

    // scalar operations
    Array2D<T>& operator+=(T val)
    {
        for (auto& x : m_buf) x += val;
        return *this;
    }

    Array2D<T>& operator*=(T val)
    {
        for (auto& x : m_buf) x *= val;
        return *this;
    }

    Array2D<T>& operator/=(T val)
    {
        if (val == T{})
            throw std::invalid_argument("division by zero");
        for (auto& x : m_buf) x /= val;
        return *this;
    }

    // array operations
    Array2D<T>& operator=(const Array2D<T>& other)
    {
        if (this != &other)
        {
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_buf = other.m_buf;
        }
        return *this;
    }

    Array2D<T>& operator+=(const Array2D<T>& other)
    {
        if (!SameSize(other))
            throw std::invalid_argument("size mismatch");
        for (size_t i = 0; i < m_buf.size(); ++i)
            m_buf[i] += other.m_buf[i];
        return *this;
    }

    Array2D<T>& operator-=(const Array2D<T>& other)
    {
        if (!SameSize(other))
            throw std::invalid_argument("size mismatch");
        for (size_t i = 0; i < m_buf.size(); ++i)
            m_buf[i] -= other.m_buf[i];
        return *this;
    }

    virtual Array2D<T>& operator*=(const Array2D<T>& other)
    {
        if (!SameSize(other))
            throw std::invalid_argument("size mismatch");
        for (size_t i = 0; i < m_buf.size(); ++i)
            m_buf[i] *= other.m_buf[i];
        return *this;
    }

    virtual Array2D<T>& operator/=(const Array2D<T>& other)
    {
        if (!SameSize(other))
            throw std::invalid_argument("size mismatch");
        for (size_t i = 0; i < m_buf.size(); ++i)
            m_buf[i] /= other.m_buf[i];
        return *this;
    }

    std::ostream& Save(std::ostream& os) const
    {
        os << m_rows << " " << m_cols << "\n";
        for (int r = 0; r < m_rows; ++r)
        {
            for (int c = 0; c < m_cols; ++c)
            {
                if (c > 0) os << " ";
                os << std::fixed << std::setprecision(4) << m_buf[r * m_cols + c];
            }
            os << "\n";
        }
        return os;
    }

    std::istream& Load(std::istream& is)
    {
        int r, c;
        is >> r >> c;
        Resize(r, c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                is >> (*this)(i, j);
        return is;
    }
};
