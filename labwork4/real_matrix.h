#pragma once
#include "array2d.h"

class RealMatrix : public Array2D<double>
{
public:
    RealMatrix() = default;
    ~RealMatrix() override = default;

    void MakeIdentity();

    RealMatrix operator*(const RealMatrix& rhs) const;
    RealMatrix operator~() const;

    Array2D<double>& operator*=(const Array2D<double>& other) override;
    Array2D<double>& operator/=(const Array2D<double>& other) override;

    void CheckMultiplyCompat(const RealMatrix& rhs) const;
};
