#include "Header.h"
#include <string>
using namespace std;
void interface();

int main()
{
	/*Classic a; 
	a.C_random();
	a.multiply();
	a.output_C();

	Winograd_Shtrassen b;
	b.C_random();
	b.multiply();*/

	interface();


	/*Shtrassen s;
	s.C_from_file("file.txt");
	s.multiply();*/
}

void interface()
{
	int method, fill;
	cout << "Choose method: 1 - classic, 2 - Shtrassen, 3 - Winograd_Shtrassen:" << endl;
	cin >> method;
	cout << "Choose a way to fill matrixes: 1 - from file, 2 - random, 3 - from keyboard:" << endl;
	cin >> fill;
	string out_way;
	cout << "Write the output way: " << endl;
	cin.ignore();
	getline(cin, out_way);
	if (method == 1)
	{
		Classic matr;
		if (fill == 1)
		{
			string way;
			cout << "Choose the start way:";
			cin.ignore();
			getline(cin, way);
			matr.C_from_file(way);
		}
		else if (fill == 2)
		{
			matr.C_random();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}

		else if (fill == 3)
		{
			matr.C_fill();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}

		matr.multiply();
		matr.output_C();
		matr.output_C_in_file(out_way);
		int mult0 = matr.get_mult();
		int sum0 = matr.get_sum();
		cout << "Sum=" << sum0 << ", Mult=" << mult0 << endl;
	}
	if (method == 2)
	{
		Shtrassen matr;
		if (fill == 1)
		{
			string way;
			cout << "Choose the start way:";
			cin.ignore();
			getline(cin, way);
			matr.C_from_file(way);
		}
		else if (fill == 2)
		{
			matr.C_random();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}
		else if (fill == 3)
		{
			matr.C_fill();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}
		

		matr.multiply();
		matr.output_C_in_file(out_way);
		int mult0 = matr.get_mult();
		int sum0 = matr.get_sum();
		cout << "Sum=" << sum0 << ", Mult=" << mult0 << endl;
	}
	if (method == 3)
	{
		Winograd_Shtrassen matr;
		if (fill == 1)
		{
			string way;
			cout << "Choose the start way:";
			cin.ignore();
			getline(cin, way);
			matr.C_from_file(way);
		}
		else if (fill == 2)
		{
			matr.C_random();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}

		else if (fill == 3)
		{
			matr.C_fill();
			cout << "Write the output way for start matrixes: " << endl;
			string way1;
			cin.ignore();
			getline(cin, way1);
			matr.output_A_B_in_file(way1);
		}

		matr.multiply();
		matr.output_C_in_file(out_way);
		int mult0 = matr.get_mult();
		int sum0 = matr.get_sum();
		cout << "Sum=" << sum0 << ", Mult=" << mult0 << endl;
	}
}
