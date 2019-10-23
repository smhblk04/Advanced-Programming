//Semih Balki - 19010
#include "Matrix.h"
#include <iostream>
using namespace std;
Matrix::Matrix()
{
	rowNumber = 0;
	columnNumber = 0;
	data = new int*[0];
	data[0] = new int[0];
}
Matrix::Matrix(int rowNum, int columnNum, int init)
{
	if (rowNum < 0 || columnNum < 0)
	{
		rowNumber = 0;
		columnNumber = 0;
		data = new int*[0];
		data[0] = new int[0];
	}
	else
	{
		rowNumber = rowNum;
		columnNumber = columnNum;
		data = new int*[rowNum];
		for (int i = 0; i < rowNum; i++)
			data[i] = new int[columnNum];
		for (int i = 0; i < rowNumber; i++)
			for (int j = 0; j < columnNumber; j++)
				data[i][j] = init;
	}
}
Matrix::Matrix(const Matrix& copy)
{
	rowNumber = copy.getRowNumber();
	columnNumber = copy.getColumnNumber();
	//Matrix lhs(rowNumber, columnNumber, 0);
	data = new int*[rowNumber];
	for (int i = 0; i < rowNumber; i++)
		data[i] = new int[columnNumber];
	for (int i = 0; i < rowNumber; i++)
		for (int j = 0; j < columnNumber; j++)
			data[i][j] = copy.data[i][j];
}
Matrix::~Matrix()
{
	for (int i = 0; i < rowNumber; i++)
		delete [] data[i];
	delete[] data;
}
int Matrix::getRowNumber() const
{	
	return rowNumber;
}
int Matrix::getColumnNumber() const
{
	return columnNumber;
}
int Matrix::getElementAt(int row, int col) const
{
	return data[row][col];
}
void Matrix::setElementAt(int row, int col, int value)
{
	data[row][col] = value;
}
void Matrix::print()
{
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < columnNumber; j++)
			cout << data[i][j] << " ";
		cout << endl;
	}
}
const Matrix& Matrix::operator =(const Matrix &rhs)
{
	if (this != &rhs)
	{
		rowNumber = rhs.rowNumber;
		columnNumber = rhs.columnNumber;
		data = new int*[rowNumber];
		for (int i = 0; i < rowNumber; i++)
			data[i] = new int[columnNumber];
		for (int i = 0; i < rowNumber; i++)
			for (int j = 0; j < columnNumber; j++)
				data[i][j] = rhs.data[i][j];
	}
	return *this;
}
Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix lhs(rowNumber, columnNumber, 0);
	for (int i = 0; i < rhs.getRowNumber(); i++)
		for (int j = 0; j < rhs.getColumnNumber(); j++)
			lhs.data[i][j] = data[i][j] - rhs.data[i][j];
	return lhs;
}
Matrix Matrix::operator +(const Matrix& rhs) const
{
	Matrix lhs(rowNumber, columnNumber, 0);
	for (int i = 0; i < rhs.getRowNumber(); i++)
		for (int j = 0; j < rhs.getColumnNumber(); j++)
			lhs.data[i][j] = data[i][j] + rhs.data[i][j];
	return lhs;
}
bool Matrix::operator ==(const Matrix& rhs) const
{
	if (rhs.getRowNumber() != rowNumber || rhs.getColumnNumber() != columnNumber)
		return false;
	else
	{
		for (int i = 0; i < rhs.getRowNumber(); i++)
		{
			for (int j = 0; j < rhs.getColumnNumber(); j++)
			{
				if (data[i][j] != rhs.getElementAt(i, j))
				{
					return false;
				}
			}
		}
	}
	return true;
}
Matrix Matrix::operator !() 
{
	Matrix rhs(columnNumber, rowNumber, 0);//Create dummy matrix to assign private values
	for (int i = 0; i < rowNumber; i++)
		for (int j = 0; j < columnNumber; j++)
			rhs.data[j][i] = data[i][j];
	for (int i = 0; i < rowNumber; i++)
		delete[] data[i];
	delete[] data;
	int temp = columnNumber;
	columnNumber = rowNumber;
	rowNumber = temp;
	data = new int*[rowNumber];
	for (int i = 0; i < rowNumber; i++)
		data[i] = new int[columnNumber];
	for (int i = 0; i < rowNumber; i++)
		for (int j = 0; j < columnNumber; j++)
			data[i][j] = rhs.data[i][j];
	return *this;
}