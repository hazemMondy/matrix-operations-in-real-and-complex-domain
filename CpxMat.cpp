#include "CpxMat.h"

#include<iostream>
#include<string>
#include<math.h>
#include <cstdlib>
#include <sstream>





namespace CpxMat {
#include <cstdlib>
#include<string>

#pragma region Reading


	static int read_cpxMat( cpx** cmx,const std::string& input, int& row, int& column)
	{
#pragma region attributes and intializing


		int y = 0, x, c, m = 0, n = 0, k;
		int no_col = std::count(input.begin(), input.end(), ';') + 1;
		int j = 1;	std::string value;
		float** mcplx;
		float** _mtrx;
		_mtrx = new float* [no_col];
		mcplx = new float* [no_col];


		for (int o = 0; o < no_col; o++) {
			mcplx[o] = new float[no_col];
			_mtrx[o] = new float[no_col];
			for (int u = 0; u < no_col; u++)
				cmx[o][u].scpx(0);
		}
#pragma endregion

#pragma region Routine


		for (int i = 1; i <= input.length(); i++)
		{

			y++;
			if (input[i] == ']') break;
			if (input[i] == ' ')
			{

				y = 1;
				column++;
				j = i + 1;
			}
			if (input[i] == '+' || input[i] == '-') {
				k = i; c = 1; if (input[i] == '+') n = 1;
				if (input[k + 1] == 'i')
				{
					mcplx[row][column] = 1;
					cmx[row][column].scpx(mcplx[row][column]);
					continue;
				}
				while (i <= input.length())
				{
					i++;
					if (input[i] == 'i')
					{
						value = input.substr(k, c);
						mcplx[row][column] = atof(value.c_str());
						cmx[row][column].scpx(mcplx[row][column]);
						i++;
						break;
					}
					c++;
					if (input[i] == ';')
					{
						row++;
						column = 0;
						y = 1;
						j = i + 1;
						break;
					}
					if (input[i] == ' ')
					{
						y = 1;
						column++;
						j = i + 1; break;
					}
				}
			}
			if (input[i] == ';')
			{
				row++;
				column = 0;
				y = 1;
				j = i + 1;
			}
			for (int l = 1; l <= y; l++) { value = input.substr(j, l); }
			_mtrx[row][column] = atof(value.c_str());
			cmx[row][column].srl(_mtrx[row][column]);
		}
#pragma endregion
		return 0;
	}
	static int read_realMat( float** _mtrx,const std::string& input, int& row, int& column)
	{
#pragma region attributes and intializing
		int x, y = 0;	int j = 1;	std::string value;



		int n = std::count(input.begin(), input.end(), ';') + 1;

		float** m;
		m = new float* [n];
#pragma endregion

#pragma region Routine
		for (int i = 1; i <= input.length(); i++)
		{
			m[i] = new float[n];

			y++;
			if (input[i] == ']') break;
			if (input[i] == ' ')
			{
				y = 1;	column++;	j = i + 1;
			}
			if (input[i] == ';')
			{
				if (row == 0) { x = column; }
				if (x != column) { cout << "ERROR"; exit(0); }
				row++;	column = 0;		y = 1;		j = i + 1;
			}
			value = input.substr(j, y);
			//for (int l = 1; l <= y; l++) {	value = in.substr(j, l);	}
			_mtrx[row][column] = atof(value.c_str());
		}
#pragma endregion
		return 0;
	}
#pragma endregion


#pragma region Printing

	static void cout_cpxMat(cpx** matZ, int column, int row) {
		cout << "[";
		for (int c = 0; c <= row; c++)
		{
			for (int q = 0; q <= column; q++)
			{
				cout << matZ[c][q].grl();
				if (matZ[c][q].gcpx() != 0)
				{
					if (matZ[c][q].gcpx() < 0) { cout << matZ[c][q].gcpx() << "i"; }
					else { cout << "+" << matZ[c][q].gcpx() << "i"; }
				}
				if (q != column) cout << " ";
			}
			if (c != row)cout << ";";
		}
		cout << "]";
	}
	static void cout_realMat(float** matZ, int column, int row) {
		cout << "[";
		for (int c = 0; c <= row; c++)
		{
			for (int q = 0; q <= column; q++)
			{
				cout << matZ[c][q];
				if (q != column) cout << " ";
			}
			if (c != row)cout << ";";
		}
		cout << "]";
	}
#pragma endregion


#pragma region Adding Subtracting

	static void sum_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column1, int column2) {
		for (int i = 0; i <= row1; i++)
		{
			for (int j = 0; j <= column1; j++)
				matZ[i][j] = matX[i][j] + matY[i][j];
		}
	}
	static void sum_cpxMat(cpx** matX, cpx **matY, cpx** matZ, int row, int row1, int column1, int column2) {
		float b, c;
		for (int i = 0; i <= row1; i++)
		{
			for (int j = 0; j <= column1; j++) {
				b = matX[i][j].grl() + matY[i][j].grl();
				matZ[i][j].srl(b);
				c = matX[i][j].gcpx() + matY[i][j].gcpx();
				matZ[i][j].scpx(c);
			}
		}
	}

	static void sub_cpxMat(cpx** matX, cpx** matY, cpx** matZ, int row, int row1, int column1, int column2) {
		float b, c;
		for (int i = 0; i <= row; i++)
		{
			for (int j = 0; j <= column1; j++)
			{
				b = matX[i][j].grl() - matY[i][j].grl();
				matZ[i][j].srl(b);
				c = matX[i][j].gcpx() - matY[i][j].gcpx();
				matZ[i][j].scpx(c);
			}
		}
	}
	static void sub_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column1, int column2) {
		for (int i = 0; i <= row; i++)
		{
			for (int j = 0; j <= column1; j++)
			{
				matZ[i][j] = matX[i][j] - matY[i][j];
			}
		}
	}
#pragma endregion

#pragma region Multiplying

	static void mul_cpxMat(cpx** matX, cpx** matY, cpx** matZ, int row, int row1, int column, int column2) {
		float b = 0, c = 0;
		for (int v = 0; v <= row; ++v) {
			for (int m = 0; m <= column2; ++m) {
				matZ[v][m].srl(0); matZ[v][m].scpx(0); b = 0; c = 0;
				for (int k = 0; k <= column; ++k) {
					b += matX[v][k].grl() * matY[k][m].grl() - matX[v][k].gcpx() * matY[k][m].gcpx();
					matZ[v][m].scpx(b);
					c += matX[v][k].grl() * matY[k][m].gcpx() + matX[v][k].gcpx() * matY[k][m].grl();
					matZ[v][m].scpx(c);
				}
			}
		}
	}
	static void mul_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column, int column2) {
		for (int v = 0; v <= row; ++v) {
			for (int m = 0; m <= column2; ++m) {
				matZ[v][m] = 0;
				for (int k = 0; k <= column; ++k)
					matZ[v][m] += matX[v][k] * matY[k][m];
			}
		}
	}
	static void power(float** matX, float** matZ, int row, int column, int n) {
		float** b = new float*[row];

		for (int x = 0; x < row; x++) {
			b[x] = new float[row];
			for (int y = 0; y < row; y++) {
				b[x][y] = matX[x][y];
				matZ[x][y] = 0;
			}
		}
		for (int i = 1; i < n; i++)
		{
			mul_realMat(b, matX, matZ, row, column, row, column);
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < row; y++) {
					b[x][y] = matZ[x][y];
				}
			}
		}
	}

#pragma endregion

#pragma region Higher operations


	static void transpose(float** _mtrx, float** _mtrxs, int row, int cl)
	{
		for (int k = 0; k <= row; k++){
			for (int p = 0; p <= cl; p++)
				_mtrxs[p][k] = _mtrx[k][p];
		}
	}
	static void determinant (float** _mtrx, float& det, int row) {
		float b, n, v, r = 1; int k = 0;
		for (int h = 0; h <= row; h++)
		{
			for (int i = h + 1; i <= row; i++) {
				for (int j = 0; j <= row; j++) {
					if (j == 0) b = _mtrx[i][h] / _mtrx[h][h];
					_mtrx[i][j] -= _mtrx[h][j] * b;
				}
			}
			if (_mtrx[h][h] == 0)
			{
				k = h; for (int c = 0; c <= row; c++)
				{
					n = _mtrx[k][c];
					v = _mtrx[k][c + 1];
					_mtrx[k][c + 1] = n;
					_mtrx[k][c] = v;
					k++;
				}
			}
			else	r *= _mtrx[h][h];
		}
		det = r;
	}
	static void inverse(float** _mtrx, float** matZ, int row) {
#pragma region attributes and intializing
		float** smtrx; float** bte5a; float** a5era;

		smtrx = new float* [row];
		bte5a = new float* [row];
		a5era = new float* [row];

		for (size_t i = 0; i < row; i++)
		{
			smtrx[i] = new float[row];
			bte5a[i] = new float[row];
			a5era[i] = new float[row];
		}

		float d, t; int m, y, n;
#pragma endregion

#pragma region Routine
		if (row == 1) {
			smtrx[0][0] = _mtrx[1][1];		smtrx[0][1] = -_mtrx[1][0];
			smtrx[1][0] = -_mtrx[0][1];		smtrx[1][1] = _mtrx[0][0];
			determinant (_mtrx, t, row);
			if (t == 0) { cout << "ERROR"; exit(0); }
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < row; j++) {
					matZ[i][j] = (1 / t) * smtrx[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i <= row; i++)
			{
				for (int j = 0; j <= row; j++)
				{
					y = n = m = 0;
					for (int k = 0; k <= row; k++)
					{
						n = 0;
						for (int l = 0; l <= row; l++)
						{
							if (k != i && l != j) {
								smtrx[m][n] = _mtrx[k][l];
								n++;
								if (n == row)
								{
									m++; n = 0;
								}
							}
						}
						// if (k == row) { m = 0;  }
					}
					determinant (smtrx, d, row - 1);
					bte5a[i][j] = pow(-1, i + j) * d;
				}
			}
			transpose(bte5a, a5era, row, row);
			determinant (_mtrx, t, row);
			if (t == 0) { cout << "ERROR"; exit(0); }
			for (int i = 0; i <= row; i++)
			{
				for (int j = 0; j <= row; j++) {
					matZ[i][j] = (1 / t) * a5era[i][j];
				}
			}
		}
#pragma endregion
	}

#pragma endregion


	int main() {
		std::string in; std::string _op; std::string om;
		cpx** m;//int n;



		int columnX = 0; int rowX = 0; int columnY = 0; int rowY = 0;

		float** _mtrxX;
		float** _mtrxY;
		float** matZ;
		float** _mtrxz;

		float t = 0; int no;
		cpx** _mtrxXa;
		cpx** _mtrxXb;
		cpx** _mtrxXc;
		getline(cin, in);
		read_realMat( _mtrxX, in, rowX, columnX);
		//read_cpxMat(in, _mtrxXa, rowX, columnX/*,n*/);
		//cout_cpxMat(_mtrxXa, columnX, rowX/*,n*/);
		//read_cpxMat(on, _mtrxXb, rowY, columnY/*,n*/);
		//cout_cpxMat(_mtrxXb, columnY, rowY/*,n*/);
		/*
		mul_cpxMat(_mtrxXa[100][100], _mtrxXb[100][100],_mtrxXc[100][100],rowX,rowY, columnX, columnY);
		sub_cpxMat(_mtrxXa[100][100],_mtrxXb[100][100],_mtrxXc[100][100],rowX,rowY, columnX, columnY);
		sum_cpxMat(_mtrxXa[100][100], _mtrxXb[100][100],_mtrxXc[100][100],rowX,rowY,  columnX, columnY);
		cout_cpxMat(_mtrxXc, columnY, rowX/*,n*/ /*);
		*/
		getline(cin, _op);
		if (_op == "^")
		{
			cin >> no;  if (no < 0) { cout << "ERROR";  return 0; }
			if (rowX != columnX)
			{
				cout << "ERROR";  return 0;
			}
			power(_mtrxX, matZ, rowX, columnX, no);
			cout_realMat(matZ, columnX, rowX);
			return 0;
		}
		if (_op == "D")
		{
			if (rowX != columnX) { cout << "ERROR"; }
			determinant (_mtrxX, t, rowX);
			cout << t;
			return 0;
		}
		if (_op == "T") {
			transpose(_mtrxX, matZ, rowX, columnX);
			//if (rowX != columnX) { cout << "ERROR"; }
			cout_realMat(matZ, rowX, columnX);	return 0;
		}
		if (_op == "I")
		{
			if (rowX != columnX) { cout << "ERROR"; return 0; }
			inverse(_mtrxX, matZ, rowX);
			cout_realMat(matZ, columnX, rowX);
			return 0;
		}
		getline(cin, om);
		read_realMat( _mtrxY, om, rowY, columnY);
		if (_op == "/")
		{
			if (rowY != columnY) { cout << "ERROR"; return 0; }

			inverse(_mtrxY, _mtrxz, rowX);
			mul_realMat(_mtrxX, _mtrxz, matZ, rowX, rowX, columnX, columnY);
		}
		if (_op == "+") {
			if (rowX != rowY || columnX != columnY) { cout << "ERROR";	return 0; }
			sum_realMat(_mtrxX, _mtrxY, matZ, rowX, rowY, columnX, columnY);
		}
		if (_op == "-") {
			if (rowX != rowY || columnX != columnY) { cout << "ERROR";	return 0; }
			sub_realMat(_mtrxX, _mtrxY, matZ, rowX, rowY, columnX, columnY);
		}
		if (_op == "*") {
			if (rowY != columnX) { cout << "ERROR"; return 0; }
			mul_realMat(_mtrxX, _mtrxY, matZ, rowX, rowY, columnX, columnY);
		}
		cout_realMat(matZ, columnY, rowX);
		return 0;
	}//[1 2+i 3;2 2i -5i]


}