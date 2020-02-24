#include "matrix.hpp"

Matrix::Matrix() {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            (i != j)  ? this->at(i,j) = 0.0
                                        : this->at(i,j) = 1.0;
        }
    }
}
Matrix::Matrix(double* _matrix) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i, j) = _matrix[i*MATRIX_COLUMNS+j];
        }
    }
}
Matrix::~Matrix() {

}
double& Matrix::at(std::uint8_t i, std::uint8_t j) {
    return _matrix[i*MATRIX_COLUMNS+j];
}
double Matrix::at(std::uint8_t i, std::uint8_t j) const {
    return _matrix[i*MATRIX_COLUMNS+j];
}
bool Matrix::operator==(const Matrix & other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            if(this->at(i,j) != other.at(i,j)) return false;
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix & other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            if(this->at(i,j) != other.at(i,j)) return true;
        }
    }
    return false;
}
Matrix& Matrix::operator+=(const Matrix & other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) += other.at(i,j);
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix & other) {
    Matrix sum(*this);
    return sum += other;
}

Matrix& Matrix::operator-=(const Matrix & other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) -= other.at(i,j);
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix & other) {
    Matrix difference(*this);
    return difference -= other;
}

Matrix& Matrix::operator*=(const Matrix & other) {
    /* to do */
    Matrix product;
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            double dot = 0.0;
            for(std::uint8_t k = 0; k < MATRIX_COLUMNS; k++) {
                dot+=this->at(i,k)*other.at(k,j);
            }
            product.at(i,j) = dot;
        }
    }
    *this = product;
    return *this;
}
Matrix Matrix::operator*(const Matrix & other) {
    Matrix product(*this);
    return product *= other;
}

Matrix Matrix::operator+(const double other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) += other;
        }
    }
    return *this;
}
Matrix Matrix::transpose() {
    Matrix transpose;
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            transpose.at(i,j) = this->at(j,i);
        }
    }
    *this = transpose;
    return *this;
}
Matrix Matrix::operator-(const double other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) -= other;
        }
    }
    return *this;
}
Matrix Matrix::operator*(const double other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) *= other;
        }
    }
    return *this;
}
Matrix Matrix::operator/(const double other) {
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            this->at(i,j) /= other;
        }
    }
    return *this;
}
double Matrix::trace() {
    double trace = 0.0;
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        trace+= this->at(i,i);
    }
    return trace;
}
std::string Matrix::to_string() const {
    std::string matrix = "";
    for(std::uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix += "[ ";
        for(std::uint8_t j = 0; j < MATRIX_COLUMNS; j++) {
            matrix += std::to_string(this->at(i,j))+" ";
        }
        matrix += "]\n";
    }
    return matrix;
}
