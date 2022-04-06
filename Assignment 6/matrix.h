#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

#define rows 10
#define cols 10

using namespace std;

// function prototype

int  fileOpen(ifstream &file, string fileName);
int  fileRead(ifstream &file, int array2D[][cols]);
void print_matrix(const int M[rows][cols], int n, int m);

// global variable
const int MATRIX_SIZE = 10;

// Class for Matrix operator overloading
class Matrix
{

    const int MATRIX_SIZE_MIN = 1;
    const int MATRIX_SIZE_MAX = 10;

protected:
    // For input Matrix
    int size;
    int **matrix;

public:
    void display();
    void DeallocateMatrix();

    Matrix(int);
    ~Matrix();
    void createMatrix(int A[MATRIX_SIZE][MATRIX_SIZE]);

    friend ostream &operator<<(ostream &s, const Matrix &c);
    friend istream &operator>>(istream &s, Matrix &c);

    // Functions for operator overloading
    void operator+(Matrix x);
    void operator-(Matrix x);
    void operator*(Matrix x);
    void operator++();        // pre increment
    void operator++(int x);   // post
    void operator--();        // pre
    void operator--(int x);   // post
    void operator!();
    
    // copy constructor
    Matrix(Matrix &x); 
    Matrix &operator=(Matrix &x);
};
