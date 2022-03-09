#include "vobo_math.h"

namespace vobo
{

uint numberDigits(double number, int precision) {
    std::ostringstream digits;
    /* Set the number of precision */
    digits.precision(precision);
    digits << number;
    return digits.str().size();
}

/* Could probably make this a general glm print */
std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix) {
    /* Initialize the column width at 4 */
    uint maxDigitsPerColum = 4;
    /* Get the maximum number of digits in matrix */
    for (int i = 0; i < matrix.length(); i++) {
        for (int j = 0; j < matrix.length(); j++) {
            auto matrixEntry = matrix[i][j];
            maxDigitsPerColum =
                std::max(numberDigits(matrixEntry), maxDigitsPerColum);
        }
    }

    /* Now print the matrix with the appropriate spacing */
    for (int i = 0; i < matrix.length(); i++) {
        for (int j = 0; j < matrix.length(); j++) {
            auto matrixEntry = matrix[i][j];
            /* Need to add 2 for padding from last number */
            os << std::setw(maxDigitsPerColum + 2) << matrixEntry;
        }
        os << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& vector) {
    int length = vector.length();
    os << "[";
    for (int i=0 ;i < length; i++) {
        os << vector[i] << (i == length-1 ? "]": ", ");
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const glm::vec3& vector) {
    int length = vector.length();
    os << "[";
    for (int i=0 ;i < length; i++) {
        os << vector[i] << (i == (length-1) ? "]": ", ");
    }
    return os;
}
} // namespace vobo