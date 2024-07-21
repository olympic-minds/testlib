#ifndef MATRIX_H_
#define MATRIX_H_

#include "utils.h"

template <ConvertibleToLongLong T>
class Matrix {
public:
    std::pair<size_t, size_t> size;
    bool isSquare;
    std::vector<std::vector<T>> matrix;

private:
    void printForPromptTo(std::ostream &outputStream) const {
        outputStream << "{";
        for (int i = 0; i < size.first; ++i) {
            outputStream << "{";
            for (int j = 0; j < size.second; ++j) {
                outputStream << matrix[i][j];
                if (j != size.second - 1) {
                    outputStream << ",";
                }
            }
            outputStream << "}";
            if (i != size.first - 1) {
                outputStream << ",";
            }
        }
        outputStream << "}\n";
    }

    void printForSolutionTo(std::ostream &outputStream) const {
        outputStream << size.first << " " << size.second << "\n";
        for (int i = 0; i < size.first; ++i) {
            for (int j = 0; j < size.second; ++j) {
                outputStream << matrix[i][j];
                if (j != size.second - 1) {
                    outputStream << " ";
                }
            }
            outputStream << "\n";
        }
    }

    bool vectorForMatrixValidator(std::vector<std::vector<T>> mat){
        if(mat.size() == 0){
            return false;
        }
        int rowSize = mat[0].size();

        for(row : mat){
            if(row.size() != rowSize){
                return false;
            }
        }

        return true;
    }

public:
    Matrix(std::vector<std::vector<T>> mat){
        size = {mat.size(), mat[0].size()};
        isSquare = size.first == size.second;
        matrix = mat;

        assert(vectorForMatrixValidator(mat));
    }

    bool operator==(const Matrix &other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size.first; ++i) {
            for (int j = 0; j < size.second; ++j) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    operator std::vector<std::vector<T>>() const { return matrix; }

    void printTo(std::ostream &outputStream, PrintFormat format) const {
        switch (format) {
            case Prompt:
                printForPromptTo(outputStream);
                break;
            case Solution:
                printForSolutionTo(outputStream);
                break;
        }
    }

    static Matrix readMatrix(std::istream &inputStream) {
        std::pair<size_t, size_t> size;
        inputStream >> size.first >> size.second;
        std::vector<std::vector<long long>> matrix(size.first, std::vector<long long>(size.second));
        for (int i = 0; i < size.first; i++) {
            for (int j = 0; j < size.second; j++) {
                inputStream >> matrix[i][j];
            }
        }
        return Matrix(matrix);
    }

    static Matrix constructIdentityMatrix(int size) {
        std::vector<std::vector<long long>> matrix(size, std::vector<long long>(size, 0));
        for (int i = 0; i < size; i++) {
            matrix[i][i] = 1;
        }
        return Matrix(matrix);
    }

    // Function to get the cofactor matrix (minor matrix)
    Matrix getCofactor(size_t delrow, size_t delcol) {
        size_t i = 0, j = 0;
        std::vector<std::vector<T>> temp(size.first-1, std::vector<int>(size.second-1)); 
        for (size_t row = 0; row < size.first; row++) {
            for (size_t col = 0; col < size.second; col++) {
                if (row != delrow && col != delcol) {
                    temp[i][j++] = mat[row][col];
                    if (j == size.second - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return std::move(temp);
    }

    long long getTrace() {
        long long result = 0;
        for (size_t i = 0; i < size.first; i++) {
            result += matrix[i][i];
        }
        return result;
    }

    long long getDeterminant() {
        assert(isSquare);
        
        long long det = 0;
        if (size.first == 1) {
            return mat[0][0];
        }

        long long sign = 1;

        for (size_t f = 0; f < size.first; f++) {
            Matrix<T> temp = getCofactor(matrix, 0, f);
            det += sign * matrix[0][f] * getDeterminant(temp);
            sign = -sign;
        }

        return det;
    }
};

#endif
