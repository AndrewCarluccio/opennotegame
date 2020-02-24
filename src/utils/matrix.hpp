#ifndef MATRIX_INCLUDED_HPP
#define MATRIX_INCLUDED_HPP

#include <cstdint>
#include <string>

#define MATRIX_ROWS 3
#define MATRIX_COLUMNS 3

// uint8_t is an 8 bit unsigned integer
class Matrix {
  public:
    Matrix();
    Matrix(double* _matrix);
    ~Matrix();
    double& at(std::uint8_t i, std::uint8_t j);
    double at(std::uint8_t i, std::uint8_t j) const;
    //double operator[](std::uint8_t i) const;
    //Matrix& operator=(const Matrix & other);
    //Binary matrix operations
    bool operator==(const Matrix & other);
    bool operator!=(const Matrix & other);
    Matrix& operator+=(const Matrix & other);
    Matrix operator+(const Matrix & other);
    Matrix& operator-=(const Matrix & other);
    Matrix operator-(const Matrix & other);
    Matrix& operator*=(const Matrix & other);
    Matrix operator*(const Matrix & other);
    //Unary matrix operations
    Matrix transpose();
    //Unary scalar operations
    Matrix operator+(const double other);
    Matrix operator-(const double other);
    Matrix operator*(const double other);
    Matrix operator/(const double other);
    //Matrix property computations
    double trace();
    //Matrix representation conversions
    std::string to_string() const;
  private:
    double _matrix[9];
};

#endif /* end of include guard: MATRIX_INCLUDED_HPP */
