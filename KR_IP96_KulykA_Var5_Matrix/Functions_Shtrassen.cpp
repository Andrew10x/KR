#include "Header.h"
using namespace std;

void Shtrassen::multiply()
{
	multiply1(A, B, C, n3);
	final_change_C();
	cout << "final Shrassen: " << endl;

	output(C, n3, m3);
	//output(A, m3, n3);
	//output(B, m3, m3);
	//cout << "n3=" << n3 << "m3=" << m3 << endl;
}

void Shtrassen::multiply1(int** a, int** b, int**& c, int h)
{
	if (h <= 2)
	{
		c = normal_mult(a, b, h);
	}
	else
	{
		int new_h = h / 2;
		int** A11 = copy(a, 0, 0, new_h);
		int** A12 = copy(a, 0, new_h, new_h);
		int** A21 = copy(a, new_h, 0, new_h);
		int** A22 = copy(a, new_h, new_h, new_h);

		int** B11 = copy(b, 0, 0, new_h);
		int** B12 = copy(b, 0, new_h, new_h);
		int** B21 = copy(b, new_h, 0, new_h);
		int** B22 = copy(b, new_h, new_h, new_h);

		int** S1 = plus1(A11, A22, new_h);
		int** S2 = plus1(B11, B22, new_h);
		int** S3 = plus1(A21, A22, new_h);
		int** S4 = minus1(B12, B22, new_h);
		int** S5 = minus1(B21, B11, new_h);
		int** S6 = plus1(A11, A12, new_h);
		int** S7 = minus1(A21, A11, new_h);
		int** S8 = plus1(B11, B12, new_h);
		int** S9 = minus1(A12, A22, new_h);
		int** S10 = plus1(B21, B22, new_h);
		sum0 += 10;
		int** P1 = create_matr(new_h, new_h);
		multiply1(S1, S2, P1, new_h);
		int** P2 = create_matr(new_h, new_h);
		multiply1(S3, B11, P2, new_h);
		int** P3 = create_matr(new_h, new_h);
		multiply1(A11, S4, P3, new_h);
		int** P4 = create_matr(new_h, new_h);
		multiply1(A22, S5, P4, new_h);
		int** P5 = create_matr(new_h, new_h);
		multiply1(S6, B22, P5, new_h);
		int** P6 = create_matr(new_h, new_h);
		multiply1(S7, S8, P6, new_h);
		int** P7 = create_matr(new_h, new_h);
		multiply1(S9, S10, P7, new_h);
		mult0 += 7;
		int** C11 = plus1(P1, P4, new_h);
		C11 = minus1(C11, P5, new_h);
		C11 = plus1(C11, P7, new_h);

		int** C12 = plus1(P3, P5, new_h);
		
		int** C21 = plus1(P2, P4, new_h);

		int** C22 = minus1(P1, P2, new_h);
		C22 = plus1(C22, P3, new_h);
		C22 = plus1(C22, P6, new_h);
		sum0 += 8;
		copy_back(C11, 0, 0, new_h, c);
		copy_back(C12, 0, new_h, new_h, c);
		copy_back(C21, new_h, 0, new_h, c);
		copy_back(C22, new_h, new_h, new_h, c);
	}
}