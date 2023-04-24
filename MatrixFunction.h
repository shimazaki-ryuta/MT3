#pragma once
#include "matrix.h"
#include <Matrix4x4.h>
#include <math.h>
#include <assert.h>
#include <Novice.h>
#include <assert.h>
#include <cmath>

/*
template<typename MatrixSize>
MatrixSize Add(MatrixSize matrix1, MatrixSize matrix2);
template<typename MatrixSize>
MatrixSize Subtract(MatrixSize matrix1, MatrixSize matrix2);
template<typename MatrixSize>
MatrixSize Multiply(MatrixSize matrix1, MatrixSize matrix2);
template<typename MatrixSize>
MatrixSize Inverse(MatrixSize matrix);
template<typename MatrixSize>
MatrixSize Transpose(MatrixSize matrix);
template<typename MatrixSize>
MatrixSize Scalar(double k, MatrixSize matrix);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);
*/
template<typename MatrixSize>
int ColumnSize(MatrixSize m)
{
	return sizeof(m.m[0]) / sizeof(int);
}
template<typename MatrixSize>
int RowSize(MatrixSize m)
{
	return sizeof(m.m) / sizeof(m.m[0]);
}
template<typename MatrixSize>
MatrixSize Add(MatrixSize m1, MatrixSize m2)
{
	MatrixSize result;
	int size = ColumnSize(m1);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = m1.m[row][column] + m2.m[row][column];
		}
	}
	return result;
}

template<typename MatrixSize>
MatrixSize Subtract(MatrixSize m1, MatrixSize m2)
{
	MatrixSize result;
	int size = ColumnSize(m1);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = m1.m[row][column] - m2.m[row][column];
		}
	}
	return result;
}

template<typename MatrixSize>
MatrixSize Multiply(MatrixSize m1, MatrixSize m2)
{
	MatrixSize result;
	int size = ColumnSize(m1);
	int m1Column = ColumnSize(m1);
	int m2Row = RowSize(m2);
	assert(m1Column == m2Row);//
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = 0;
			for (int i = 0; i < size; i++)
			{
				result.m[row][column] += m1.m[row][i] * m2.m[i][column];
			}
		}
	}
	return result;
}

template<typename MatrixSize>
MatrixSize Scalar(double k, MatrixSize m)
{
	MatrixSize result;
	int size = ColumnSize(m);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = k * m.m[row][column];
		}
	}
	return result;
}
auto CofactorExpansion(Matrix2x2 m)
{
	return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
}
auto CofactorExpansion(Matrix3x3 m)
{
	int size = ColumnSize(m);
	Matrix2x2 result[4];
	//Matrix2x2 ans;
	double ans = 0.0f;
	for (int i = 0; i < size; i++)
	{
		double k = m.m[i][0];
		k *= pow(-1.0, double((i + 1) + 1));
		int row2 = 0;
		int column2 = 0;
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column < size; column++)
			{
				if (row != i && column != 0)
				{
					result[i].m[row2][column2] = m.m[row][column];
					column2++;
					if (column2 >= size - 1)
					{
						column2 = 0;
						row2++;
					}
				}
			}
		}
		//result[i] = Scalar(k, result[i]);
		ans += k * CofactorExpansion(result[i]);
	}
	/*ans = result[0];
	for (int i = 1; i < size; i++)
	{
		ans = Add(ans, result[i]);
	}

	if (size == 2)
	{
		//return ans;
	}
	for (int i = 0; i < size; i++)
	{
		ans = Add(ans, result[i]);
	}
	return CofactorExpansion(ans);
	*/
	return ans;
}


double CofactorExpansion(Matrix4x4 m)
{
	int size = ColumnSize(m);
	Matrix3x3 result[4];
	//Matrix3x3 ans;
	double ans = 0.0f;
	for (int i = 0; i < size; i++)
	{
		double k = m.m[i][0];
		k *= pow(-1.0f, double((i + 1) + 1));
		int row2 = 0;
		int column2 = 0;
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column < size; column++)
			{
				if (row != i && column != 0)
				{
					result[i].m[row2][column2] = m.m[row][column];
					column2++;
					if (column2 >= size - 1)
					{
						column2 = 0;
						row2++;
					}
				}
			}
		}
		//result[i] = Scalar(k, result[i]);
		ans += k * CofactorExpansion(result[i]);
	}
	/*ans = result[0];
	for (int i = 1; i < size; i++)
	{
		ans = Add(ans, result[i]);
	}

	if (size == 2)
	{
		//return ans;
	}
	for (int i = 0; i < size; i++)
	{
		ans = Add(ans, result[i]);
	}
	return CofactorExpansion(ans);
	*/
	return ans;
}

template<typename MatrixSize>
MatrixSize Transpose(MatrixSize m)
{
	MatrixSize result;
	int size = ColumnSize(m);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = m.m[column][row];
		}
	}
	return result;
}

Matrix4x4 Adjoint(Matrix4x4 m)
{
	int size = ColumnSize(m);
	Matrix4x4 result = {0};
	Matrix3x3 matrix = { 0 };
	for (int rowRes = 0; rowRes < size; rowRes++)
	{
		for (int columnRes = 0; columnRes < size; columnRes++)
		{
			double k = m.m[rowRes][columnRes];
			k = pow(-1.0, double((rowRes + 1) + double(columnRes+1)));
			int row2 = 0;
			int column2 = 0;
			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					if (row != rowRes && column != columnRes)
					{
						matrix.m[row2][column2] = m.m[row][column];
						column2++;
						if (column2 >= size - 1)
						{
							column2 = 0;
							row2++;
						}
					}

				}
			}
			double res = CofactorExpansion(matrix);
			result.m[rowRes][columnRes] = float(k * res);
		}

	}
	result = Transpose(result);
	return result;
}
Matrix3x3 Adjoint(Matrix3x3 m)
{
	int size = ColumnSize(m);
	Matrix3x3 result = { 0 };
	Matrix2x2 matrix = { 0 };
	for (int rowRes = 0; rowRes < size; rowRes++)
	{
		for (int columnRes = 0; columnRes < size; columnRes++)
		{
			double k = m.m[rowRes][columnRes];
			k = pow(-1.0, double((rowRes + 1) + double(columnRes + 1)));
			int row2 = 0;
			int column2 = 0;
			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					if (row != rowRes && column != columnRes)
					{
						matrix.m[row2][column2] = m.m[row][column];
						column2++;
						if (column2 >= size - 1)
						{
							column2 = 0;
							row2++;
						}
					}

				}
			}
			double res = CofactorExpansion(matrix);
			result.m[rowRes][columnRes] = float(k * res);
		}

	}
	result = Transpose(result);
	return result;
}
Matrix2x2 Adjoint(Matrix2x2 m)
{
	int size = ColumnSize(m);
	Matrix2x2 result = { 0 };
	float matrix = { 0 };
	for (int rowRes = 0; rowRes < size; rowRes++)
	{
		for (int columnRes = 0; columnRes < size; columnRes++)
		{
			double k = m.m[rowRes][columnRes];
			k = pow(-1.0, double((rowRes + 1) + double(columnRes + 1)));
			int row2 = 0;
			int column2 = 0;
			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					if (row != rowRes && column != columnRes)
					{
						matrix = m.m[row][column];
						column2++;
						if (column2 >= size - 1)
						{
							column2 = 0;
							row2++;
						}
					}

				}
			}
			//double res = CofactorExpansion(matrix);
			result.m[rowRes][columnRes] = float(k * matrix);
		}

	}
	result = Transpose(result);
	return result;
}

template<typename MatrixSize>
MatrixSize Inverse(MatrixSize m)
{
	int size = ColumnSize(m);
	MatrixSize result;
	Matrix2x2 matrix = { 0 };
	double determinant = CofactorExpansion(m);
	/*if (size>2)
	{
		matrix = CofactorExpansion(m);
		determinant = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
	}
	else
	{
		determinant = (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
	}*/
	//double determinant = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
	MatrixSize adjugateMatrix = Adjoint(m);


	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = float(1.0 / determinant) * adjugateMatrix.m[row][column];
		}
	}
	return result;
}

Matrix4x4 MakeIdentity4x4()
{
	Matrix4x4 result;
	int size = 4;
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			if (row==column)
			{
				result.m[row][column] = 1;
			}
			else
			{
				result.m[row][column] = 0;
			}
		}
	}
	return result;
}

//アフィン変換関係

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 translateMatrix = MakeIdentity4x4();
	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;
	return translateMatrix;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 scaleMatrix = MakeIdentity4x4();
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;
	return scaleMatrix;
}

Vector3 Transform(const Vector3& vector,const Matrix4x4& matrix)
{
	Vector3 transform;
	float transformMatrix[4];
	float matrix1x4[4] = {vector.x,vector.y,vector.z ,1.0f};
	for (int column = 0; column < 4; column++)
	{
		transformMatrix[column] = 0.0f;
		for (int i = 0; i < 4; i++)
		{
			transformMatrix[column] += matrix1x4[i] * matrix.m[i][column];
		}
	}
	float w = transformMatrix[3];
	assert(w != 0.0f);
	transform.x = transformMatrix[0] / w;
	transform.y = transformMatrix[1] / w;
	transform.z = transformMatrix[2] / w;
	return transform;
}

Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotate = MakeIdentity4x4();
	rotate.m[1][1] = std::cos(radian);
	rotate.m[1][2] = std::sin(radian);
	rotate.m[2][1] = -std::sin(radian);
	rotate.m[2][2] = std::cos(radian);

	return rotate;
}

Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotate = MakeIdentity4x4();
	rotate.m[0][0] = std::cos(radian);
	rotate.m[2][0] = std::sin(radian);
	rotate.m[0][2] = -std::sin(radian);
	rotate.m[2][2] = std::cos(radian);

	return rotate;
}
Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotate = MakeIdentity4x4();
	rotate.m[0][0] = std::cos(radian);
	rotate.m[0][1] = std::sin(radian);
	rotate.m[1][0] = -std::sin(radian);
	rotate.m[1][1] = std::cos(radian);

	return rotate;
}
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	int size = ColumnSize(matrix);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
