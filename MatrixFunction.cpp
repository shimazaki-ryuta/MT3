//#include "MatrixFunction.h"
#include <math.h>
#include <Novice.h>
/*
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
	for (int row=0;row<size;row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = m1.m[row][column]+ m2.m[row][column];
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
	int m2Row = Row(m2);
	assert(m1Column != m2Row);//
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = 0;
			for (int i=0;i<size;i++)
			{
				result.m[row][column] += m1.m[row][i] * m2.m[i][column];
			}
		}
	}
	return result;
}

template<typename MatrixSize>
MatrixSize Scalar(float k, MatrixSize m)
{
	MatrixSize result;
	int size = ColumnSize(m);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = k* m.m[row][column];
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
	Matrix2x2 ans;
	for (int i = 0; i < size; i++)
	{
		float k = m.m[i][0];
		k *= powf(-1.0f, float((i + 1) + 1));
		int row2 = 0;
		int column2 = 0;
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column < size; column++)
			{
				if (row != i && column != 0)
				{
					result[i].m[row2][column2] = m.m[row][column];
					row2++;
					if (row2 >= size - 1)
					{
						row2 = 0;
						column2++;
					}
				}
			}
		}
		result[i] = Scalar(k, result[i]);
	}
	ans = result[0];
	for (int i = 1; i < size; i++)
	{
		ans = Add(ans, result[i]);
	}

	//if (size == 2)
	{
		//return ans;
	}
	return CofactorExpansion(ans);

}


auto CofactorExpansion(Matrix4x4 m)
{
	int size = ColumnSize(m);
	Matrix3x3 result[4];
	Matrix3x3 ans;
	for (int i=0;i<size;i++)
	{
		float k = m.m[i][0];
		k *= powf(-1.0f, float((i + 1) + 1));
		int row2 = 0;
		int column2 = 0;
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column < size; column++)
			{
				if (row!=i && column!=0)
				{
					result[i].m[row2][column2] = m.m[row][column];
					row2++;
					if (row2>=size-1)
					{
						row2 = 0;
						column2++;
					}
				}
			}
		}
		result[i] = Scalar(k,result[i]);
	}
	ans = result[0];
	for (int i=1;i<size;i++)
	{
		ans = Add(ans,result[i]);
	}
	
	if (size==2)
	{
		//return ans;
	}
	return CofactorExpansion(ans);

}


Matrix4x4 Adjoint(Matrix4x4 m)
{
	int size = ColumnSize(m);
	Matrix4x4 result;
	Matrix3x3 matrix = {0};
	for (int rowRes = 0; rowRes < size; rowRes++)
	{
		for (int columnRes = 0; columnRes < size; columnRes++)
		{
			float k = m.m[rowRes][0];
			k *= powf(-1.0f, float((rowRes + 1) + 1));
			int row2 = 0;
			int column2 = 0;
			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					if (row != rowRes && column != 0)
					{
						matrix.m[row2][column2] = m.m[row][column];
						row2++;
						if (row2 >= size - 1)
						{
							row2 = 0;
							column2++;
						}
					}

				}
			}
			float res = CofactorExpansion(matrix);
			result.m[rowRes][columnRes] = k * res;
		}

	}
	
	return result;
}

template<typename MatrixSize>
MatrixSize Inverse(MatrixSize m)
{
	int size = ColumnSize(m);
	MatrixSize result;
	Matrix2x2 matrix = CofactorExpansion(m);
	float determinant = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
	MatrixSize adjugateMatrix = Adjoint(m);


	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			result.m[row][column] = (1.0f / determinant) * adjugateMatrix.m[row][column];
		}
	}
	return result;
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

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	int size = ColumnSize(matrix);
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			Novice::ScreenPrintf(x+column*kColumnWidth,y+row*kRowHeight,"%6.02f",matrix.m[row][column]);
		}
	}
}
*/
