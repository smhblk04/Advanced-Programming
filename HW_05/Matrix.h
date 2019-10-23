//Semih Balki - 19010
#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
	Matrix();//Default constructore
	Matrix(int rowNum, int columnNum, int init);//Constructor with parameters
	Matrix(const Matrix&);//Deep copy constructor
	~Matrix();//destructor
	void print();
	int getRowNumber() const;
	int getColumnNumber() const;
	int getElementAt(int row, int col) const;
	void setElementAt(int row, int col, int value);
	const Matrix& operator =(const Matrix&);
	Matrix operator -(const Matrix&) const;
	Matrix operator +(const Matrix&)const;
	bool operator ==(const Matrix&) const;
	Matrix operator !();
private:
	int **data;
	int rowNumber;
	int columnNumber;
};
#endif