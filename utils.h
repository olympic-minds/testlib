#ifndef UTILS_H_
#define UTILS_H_

#include "bits/stdc++.h"
#include <filesystem>

enum PrintFormat { Prompt, Solution };

// map for keeping the names of directories
// promptInputDirectory - directory for in files formatted for prompt
// promptInputDirectory - directory for in files formatted for the solution
const std::map<std::string, std::string> dirs = {{"promptInputDirectory", "in"},
                                                 {"solutionInputDirectory", "solution-in"}};

template <typename F, typename S>
std::ostream &operator<<(std::ostream &os, const std::pair<F, S> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "{";
    typename std::vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin()) {
            os << ", ";
        }
        os << *it;
    }
    return os << "}";
}

void println() { std::cout << '\n'; }
template <typename Head, typename... Tail>
void println(Head H, Tail... T) {
    std::cout << ' ' << H;
    println(T...);
}

void setupDirectories() {
    for (const auto &dir : dirs) {
        if (!std::filesystem::create_directory(dir.second)) {
            // Only warning, because you can fail to create a directory if it exists.
            std::cerr << "Warning: Could not create directory " << dir << std::endl;
        }
    }
}

template <typename T>
concept ConvertibleToLongLong = std::convertible_to<T, long long>;

template<ConvertibleToLongLong T>
long long changeVectorToLongLong(std::vector<T> v) {
    long long result = 0;
    for (long long i = 0; i < v.size(); i++) {
        result += (i + 1LL) * v[i];
    }
    return result;
}

template<typename T>
void printMatrix(std::vector<std::vector<T>> v) {
    for (size_t i=0;i< v.size();i++) {
        for (size_t j=0;j<v[i].size();j++) {
            std::cout<< v[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

template<ConvertibleToLongLong T>
long long calculateMatrixTrace(std::vector<std::vector<T>> v) {
    long long result = 0;
    for (size_t i = 0; i < v.size(); i++) {
        result += v[i][i];
    }
    return result;
}

// Function to get the cofactor matrix (minor matrix)
template<ConvertibleToLongLong T>
std::vector<std::vector<T>> getCofactor(std::vector<std::vector<T>> &mat, size_t delrow, size_t delcol) {
    size_t i = 0, j = 0;
    size_t n = mat.size();
    std::vector<std::vector<T>> temp(n-1, std::vector<int>(n-1)); 
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            if (row != delrow && col != delcol) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return std::move(temp);
}

template<ConvertibleToLongLong T>
long long calculateMatrixDeterminant(std::vector<std::vector<T>> &mat) {
    long long det = 0;
    size_t n = mat.size();
    if (n == 1) {
        return mat[0][0];
    }

    long long sign = 1;

    for (size_t f = 0; f < n; f++) {
        std::vector<std::vector<int>> temp = getCofactor(mat, 0, f);
        det += sign * mat[0][f] * calculateMatrixDeterminant(temp);
        sign = -sign;
    }

    return det;
}

#endif
