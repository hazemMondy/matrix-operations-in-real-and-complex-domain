
#pragma once
namespace CpxMat {
	using namespace std;


	class cpx {
	private:	float	rl, mj;
	public:
		void scpx(float i) { mj = i; }	void srl(float r) { rl = r; } void scpx(float r, float i) { rl = r; mj = i; }
		float gcpx() { return mj; }	float grl() { return rl; }
	};

	static int read_cpxMat( cpx** cmx, const std::string& input, int& row, int& column);
	static int read_realMat( float** _mtrx,const std::string& input, int& row, int& column);

	static void cout_cpxMat(cpx** matZ, int column, int row);
	static void cout_realMat(float** matZ, int column, int row);

	static void sum_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column1, int column2);
	static void sum_cpxMat(cpx** matX, cpx** matY, cpx** matZ, int row, int row1, int column1, int column2);

	static void sub_cpxMat(cpx** matX, cpx** matY, cpx** matZ, int row, int row1, int column1, int column2);
	static void sub_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column1, int column2);

	static void mul_realMat(float** matX, float** matY, float** matZ, int row, int row1, int column, int column2);
	static void mul_cpxMat(cpx** matX, cpx** matY, cpx** matZ, int row, int row1, int column, int column2);

	static void power(float** matX, float** matZ, int row, int column, int n);
	static void transpose(float** _mtrx, float** _mtrxs, int row, int cl);
	static void determinant(float** _mtrx, float& det, int row);
	static void inverse(float** _mtrx, float** matZ, int row);



}




