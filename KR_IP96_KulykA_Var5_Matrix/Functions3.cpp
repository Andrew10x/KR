#include "Header.h"
using namespace std;
int get_size(int);

void Winograd_Shtrassen::C_fill()
{
	fill_A();
	fill_B();
	change_A_B();
}

void Winograd_Shtrassen::C_random()
{
	fill_A_B_random();
	change_A_B();
}

void Winograd_Shtrassen::change_A_B()
{
	start_n3 = n1;
	start_m3 = m2;
	if (n1 > m1) n3 = n1;
	else n3 = m1;
	if (n2 > m2) m3 = n2;
	else m3 = m2;
	if (m3 > n3)
	{
		m3 = get_size(m3);
		n3 = m3;
	}
	else
	{
		n3 = get_size(n3);
		m3 = n3;
	}

	C = create_matr(m3, n3);
	if (!(n3 == n1 && m3 == m1))
	{
		A = increase_matr(A, n1, m1, n3);
		n1 = n3;
		m1 = m3;
	}
	if (!(n3 == n2 && m3 == m2))
	{
		B = increase_matr(B, n2, m2, n3);
		n1 = n3;
		m1 = m3;
	}
}

void Winograd_Shtrassen::C_from_file(string file_name)
{
	fill_A_B_from_file(file_name);
	change_A_B();
	//output(A, n1, m1);
}

void Winograd_Shtrassen::multiply()
{
	multiply1(A, B, C, n3);
	final_change_C();
	cout << "final: " << endl;
	output(C, n3, m3);
}

void Winograd_Shtrassen::multiply1(int** a, int** b, int**&c, int h)
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

		int** S1 = plus1(A21, A22, new_h);
		int** S2 = minus1(S1, A11, new_h);
		int** S3 = minus1(A11, A21, new_h);
		int** S4 = minus1(A12, S2, new_h);
		int** S5 = minus1(B12, B11, new_h);
		int** S6 = minus1(B22, S5, new_h);
		int** S7 = minus1(B22, B12, new_h);
		int** S8 = minus1(S6, B21, new_h);
		sum0 += 8;
		int** P1 = create_matr(new_h, new_h);
	    multiply1(S2, S6, P1, new_h);
		int** P2 = create_matr(new_h, new_h);
		multiply1(A11, B11, P2, new_h);
		int** P3 = create_matr(new_h, new_h);
		multiply1(A12, B21, P3, new_h);
		int** P4 = create_matr(new_h, new_h);
		multiply1(S3, S7, P4, new_h);
		int** P5 = create_matr(new_h, new_h);
		multiply1(S1, S5, P5, new_h);
		int** P6 = create_matr(new_h, new_h);
		multiply1(S4, B22, P6, new_h);
		int** P7 = create_matr(new_h, new_h);
		multiply1(A22, S8, P7, new_h);
		mult0 += 7;
		int** T1 = plus1(P1, P2, new_h);
		int** T2 = plus1(T1, P4, new_h);

		int** C11 = plus1(P2, P3, new_h);
		int** C12 = plus1(T1, P5, new_h);
		C12 = plus1(C12, P6, new_h);
		int** C21 = minus1(T2, P7, new_h);
		int** C22 = plus1(T2, P5, new_h);

		sum0 += 7;
		copy_back(C11, 0, 0, new_h, c);  
		copy_back(C12, 0, new_h, new_h, c);
		copy_back(C21, new_h, 0, new_h, c);
		copy_back(C22, new_h, new_h, new_h, c);
	}
}

int** Winograd_Shtrassen::normal_mult(int** a, int** b, int h)
{
	int** c = create_matr(h, h);
	for (int i = 0; i < h; i++)
	{
		for (int f = 0; f < h; f++)
		{
			c[i][f] = 0;
			for (int j = 0; j < h; j++)
			{
				c[i][f] += a[i][j] * b[j][f];
				sum0++;
				mult0++;
			}
		}
	}
	return c;
}

int** Winograd_Shtrassen::copy(int** a, int n0, int m0, int h)
{
	int** b = create_matr(h, h);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < h; j++)
			b[i][j] = a[i + n0][j + m0];
	return b;
}

void Winograd_Shtrassen::copy_back(int** a, int n0, int m0, int h, int** c)
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < h; j++)
			c[i + n0][j + m0] = a[i][j];
}


int** Winograd_Shtrassen::plus1(int** a, int** b, int h)
{
	int** c = create_matr(h, h);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < h; j++)
			c[i][j] = a[i][j] + b[i][j];
	return c;
}

int** Winograd_Shtrassen::minus1(int** a, int** b, int h)
{
	int** c = create_matr(h, h);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < h; j++)
			c[i][j] = a[i][j] - b[i][j];
	return c;
}


int get_size(int n)
{
	int k = 2;
	while (k < n)
		k = k * 2;
	return k;
}

int** Winograd_Shtrassen::increase_matr(int**a, int n0, int m0, int max)
{
	int** b = new int* [max];
	for (int i = 0; i < max; i++)
		b[i] = new int[max];

	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
			b[i][j] = 0;

	for (int i = 0; i < n0; i++)
		for (int j = 0; j < m0; j++)
			b[i][j] = a[i][j];

	for (int i = 0; i < n0; i++)
		delete[] a[i];
	return b;
}

void  Winograd_Shtrassen::final_change_C()
{
	int** c1 = create_matr(start_n3, start_m3);
	for (int i = 0; i < start_n3; i++)
		for (int j = 0; j < start_m3; j++)
			c1[i][j] = C[i][j];

	for (int i = 0; i < n3; i++)
			delete[] C[i];

	C = c1;
	delete[] c1;
	n3 = start_n3;
	m3 = start_m3;

}

void  Winograd_Shtrassen::output_C_in_file(string out_file)
{
	ofstream file(out_file);
	for (int i = 0; i < n3; i++)
	{
		for (int j = 0; j < m3; j++)
			file << setw(6) << C[i][j];
		file << endl;
	}
	file << endl;
	file.close();
}

void  Classic::output_C_in_file(string out_file)
{
	ofstream file(out_file);
	for (int i = 0; i < n3; i++)
	{
		for (int j = 0; j < m3; j++)
			file << setw(6) << C[i][j];
		file << endl;
	}
	file << endl;
	file.close();
}

void  Winograd_Shtrassen::output_A_B_in_file(string out_file)
{
	ofstream file(out_file);
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m1; j++)
			file << setw(6) << A[i][j];
		file << endl;
	}
	file << endl;
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < m2; j++)
			file << setw(6) << B[i][j];
		file << endl;
	}
	file << endl;
	file.close();
}
