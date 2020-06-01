#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
void output(int**, int, int);

class Matrix
{
protected:
	int sum0, mult0;
	int** A;
	int** B;
	int n1, n2;
	int m1, m2;
public:
    Matrix();
	void fill_A();
	void fill_B();
	void fill_A_B_from_file(string);
	void fill_A_B_random();
	int** create_matr(int, int);
};

class Classic : public Matrix
{
	int** C;
	int n3, m3;
public:
	Classic() : n3(0), m3(0), C(NULL) {};
	void C_from_file(string);
	void output_C_in_file(string);
	void C_random();
	void C_fill();
	void output_A_B_in_file(string);
	void multiply();
	void output_C();
	int get_sum() { return sum0; }
	int get_mult() { return mult0; }
};

class Winograd_Shtrassen : public Matrix
{
protected:
	int** C;
	int n3, m3;
	int start_n3, start_m3;
public:
	Winograd_Shtrassen() : n3(0), m3(0), start_n3(0), start_m3(0), C(NULL) {};
	void C_from_file(string);
	void C_fill();
	void output_C_in_file(string);
	void output_A_B_in_file(string);
	void C_random();
	void multiply();
	void multiply1(int**,int**, int**&, int);
	int** increase_matr(int**, int, int, int);
	void change_A_B();
	int** copy(int**, int, int, int);
	void copy_back(int**, int, int, int, int**);
	int** plus1(int**, int**, int);
	int** minus1(int**, int**, int);
	int** normal_mult(int**, int**, int);
	void final_change_C();
	int get_sum() { return sum0; }
	int get_mult() { return mult0; }
};

class Shtrassen : public Winograd_Shtrassen
{
	/*int** C;
	int n3, m3;
	int start_n3, start_m3;*/
public:
	//Shtrassen() : n3(0), m3(0), start_n3(0), start_m3(0), C(NULL) {};
	//void C_from_file(string);
	//void C_fill();
	//void C_random();
	void multiply();
	void multiply1(int**, int**, int**&, int);

};
