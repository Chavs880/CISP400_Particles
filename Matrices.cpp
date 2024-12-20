#include "Matrices.h"
#include <iomanip>

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols) {
		a.resize(_rows);
		for (int i = 0; i < _rows; i++) {
			a[i].resize(_cols);
			for (int j = 0; j < _cols; j++) {
				a.at(i).at(j) = 0;
			}
		}
		rows = _rows;
		cols = _cols;
	}

	Matrix operator+(const Matrix& a, const Matrix& b) {
		Matrix c(a.getRows(), a.getCols());
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			throw runtime_error("Error: dimensions must agree");
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				c(i, j) = a(i, j) + b(i, j);
			}			
		}
		
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b) {
		Matrix c(a.getRows(), b.getCols());

		if (a.getCols() != b.getRows()) {
			throw runtime_error("Error: dimensions must agree");
		}
		else {
			for (int k = 0; k < b.getCols(); k++) {
				for (int i = 0; i < a.getRows(); i++) {
					double runningSum = 0;
					for (int j = 0; j < a.getCols(); j++) {
						runningSum += a(i, j) * b(j, k);
					}
					c(i, k) = runningSum;
					
				}
			}
		}

		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b) {
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			return false;
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) > 0.001) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const Matrix& a, const Matrix& b) {
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Matrix& a) {
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				cout << setw(10) << a(i, j);
			}
			cout << '\n';
		}
		return os;
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
		(*this)(0, 0) = cos(theta);
		(*this)(0, 1) = -sin(theta);
		(*this)(1, 0) = sin(theta);
		(*this)(1, 1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
		(*this)(0, 0) = scale;
		(*this)(1, 1) = scale;

		(*this)(0, 1) = 0;
		(*this)(1, 0) = 0;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
		for (int i = 0; i < nCols; i++) {
			(*this)(0, i) = xShift;
			(*this)(1, i) = yShift;
		}
	}
}