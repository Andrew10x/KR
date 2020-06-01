#include "Header.h"
using namespace std;
void output(int**, int, int);
//Matrix::Matrix(int nn1, int mm1, int nn2, int mm2)
//{
//	n1 = nn1;
//	m1 = mm1;
//	n2 = nn2;
//	m2 = mm2;
//
//	A = new int* [n1];
//	B = new int* [n2];
//	for (int i = 0; i < n1; i++)
//		A[i] = new int[m1];
//	for (int i = 0; i < n2; i++)
//		B[i] = new int[m2];
//}

Matrix::Matrix()
{
	n1 = 0; m1 = 0;
	n2 = 0; m2 = 0;
	sum0 = 0;
	mult0 = 0;
	A = NULL;
	B = NULL;
}

int** Matrix::create_matr(int n0, int m0)
{
	int** a = new int* [n0];
	for (int i = 0; i < n0; i++)
		a[i] = new int[m0];
	return a;
}

void Matrix::fill_A()
{
	cout << "Input n1, m1:" << endl;
	cin >> n1 >> m1;
	A = create_matr(n1, m1);
	cout << "Fill matrix A:" << endl;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			cin >> A[i][j];
}

void Matrix::fill_B()
{
	cout << "Input n2, m2:" << endl;
	cin >> n2 >> m2;
	B = create_matr(n2, m2);
	cout << "Fill matrix B:" << endl;
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			cin >> B[i][j];
}

void Matrix::fill_A_B_from_file(string file_name)
{
	ifstream file(file_name);
	file >> n1 >> m1 >> n2 >> m2;
	A = create_matr(n1, m1);
	B = create_matr(n2, m2);
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			file >> A[i][j];

	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			file >> B[i][j];
	file.close();

	//output(A, n1, m1); //
	//output(B, n2, m2); //
}

void Matrix::fill_A_B_random()
{
	cout << "Input n1, m1, n2, m2:" << endl;
	cin >> n1 >> m1 >> n2 >> m2;

	A = create_matr(n1, m1);
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			A[i][j] = rand() % 110 - 15;

	B = create_matr(n2, m2);
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < m2; j++)
			B[i][j] = rand() % 15 - 6;
}

void Classic::C_random()
{
	fill_A_B_random();
	n3 = n1;
	m3 = m2;
	C = create_matr(n3, m3);

	//output(A, n1, m1); //
	//output(B, n2, m2); //
}

void Classic::C_from_file(string file_name)
{
	fill_A_B_from_file(file_name);
	n3 = n1;
	m3 = m2;
	C = create_matr(n3, m3);
}

void Classic::C_fill()
{
	fill_A();
	fill_B();
	n3 = n1;
	m3 = m2;
	C = create_matr(n3, m3);
}


void Classic::multiply()
{
	n3 = n1; m3 = m2;
	cout << n3 << " " << m3 << endl;
	for (int i = 0; i < n1; i++)
	{
		for (int f = 0; f < m2; f++)
		{
			C[i][f] = 0;
			for (int j = 0; j < m1; j++)
			{
				C[i][f] += A[i][j] * B[j][f];
				sum0++; mult0++;
			}
		}
	}
}

void Classic::output_C()
{
	cout << "\nMatrix C:" << endl << endl;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m2; j++)
		{
			cout << setw(8) << C[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void output(int** a, int n, int m)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(8) << a[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void  Classic::output_A_B_in_file(string out_file)
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
