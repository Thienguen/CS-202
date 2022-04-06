/*
    Thien Nguyen Revision: 3/30/2022
    Description: This program will utilize operator overloading to use operators for 2 separate matrices.
    Input: Indexes
    Output: The results of the operators
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include "matrix.h"

static const char *green = "\033[0;32m";
static const char *white = "\033[0;37m";
static const char *red = "\033[0;31m";

// Your code goes here

int fileOpen(ifstream &file, string fileName)
{
    file.open(fileName);
    if(!file.is_open())
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int fileRead(ifstream &file, int array2D[][cols])
{
    int num;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            file >> num;
            array2D[i][j] = num;
        }
    }
    return 0;
}

void print_matrix(const int M[rows][cols], int n, int m)
{
    int counter = 0;           

    for (n = 0; n < rows; n++)
    {  // Printing top of grid
        cout << " -----";
    }

    cout << endl;
    
    for (n = 0; n < rows; n++)
    {         // Printing each row
        for (m = 0; m < cols; m++)
        {     // Printing each column
            cout << "|" << red;
            if (counter < 10)
            {   // For numbers 0-9, makes sure theres a '0' before
                cout << "0";
            }
            // Print index in red then white
            cout << counter << white << "   ";          
            counter++;
        }
        
        cout << "|" << endl;
        
        for (m = 0; m < cols; m++){
            cout << "|" << right << setw(4);
            cout <<  M[n][m];
            cout << " ";
        }

        cout << "|" << endl;
        
        for (m = 0; m < cols; m++){
            cout << "|" << "     ";
        }

        cout << "|" << endl;

        for(m = 0; m < cols; m++){
            cout << " -----";
        }

        cout << " " << endl;
        
    }
}

ostream &operator<<(ostream &s, const Matrix &c){
    if(c.matrix != nullptr)
    {
        for (int i = 0; i < c.size; i++)
        {   // Top of grid
            s << " -------";
        }
        s << endl;
        
        for (int i = 0; i < c.size; i++)
        {   // Printing each row
            for (int j = 0; j < c.size; j++)
            {   // Printing each column
                s << "|" << "       ";
            }
            s << "|" << endl;

            for (int j = 0; j < c.size; j++)
            {
                s << "|" << green << setw(6) << right;
                s << c.matrix[i][j] << white;
                s << " ";
            }

            s << "|" << endl;
            
            for (int j = 0; j < c.size; j++)
            {
                s << "|" << "       ";
            }
            s << "|" << endl;
            
            for (int j = 0; j < c.size; j++)
            {
                s << " -------";
            }
            s << endl;
        }
    }
    return s;
}

istream& operator>>(istream &s, Matrix &c)
{
    cout << "Enter matrix element " << c.size << " x " << c.size << endl;
    for (int i = 0; i < c.size; i++)
    {
        for (int j = 0; j < c.size; j++)
        {
            cout << "row:[" << i << "] column:[" << j << "]\n";
            s >> c.matrix[i][j];
        }
    }
    return s;
}

void Matrix::display()
{
    for(int i = 0; i <= size - 1; i++)
    {
        cout << " -----";
    }
    cout << endl;
    for (int i = 0; i <= size - 1; i++)
    {
        for (int j = 0; j <= size - 1; j++)
        {
            cout << "|" << red << i << j << white << "   ";
        }
        cout << "|" << endl;
        for (int j = 0; j <= size - 1; j++)
        {
            cout << "|" << setw(4) << right << matrix[i][j] << " ";
        }
        cout << "|" << endl;
        for (int j = 0; j <= size - 1; j++){
            cout << "|     ";
        }
        cout << "|" << endl;
        for (int j = 0; j <= size - 1; j++){
            cout << " -----";
        }
        cout << endl;
    }
}

void Matrix::DeallocateMatrix()
{
    if (matrix != nullptr)
    {
        for (int i = 0; i < size; ++i)
        {
            delete [] matrix[i];
        }
        delete [] matrix;
        matrix = nullptr;
    }
}

Matrix::Matrix(int size)
{
    if (size < MATRIX_SIZE_MIN || size > MATRIX_SIZE_MAX)
    {
        this->size = 0;
        matrix = nullptr;
        cout << "Error, invalid size.\n"
             << "Please provide valid size.\n";
        size = 0;
    }
    else{
        this->size = size;
        matrix     =  new int* [size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new int [size];
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

Matrix::~Matrix()
{
    DeallocateMatrix();
}

void Matrix::createMatrix(int A[MATRIX_SIZE][MATRIX_SIZE]){
    // temporary int to store information
    int variable = 0; 
    bool check;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            do{
                check = false;
                cout << "Enter matrix index for " << i << j << endl;
                cin >> variable;
                if (variable < 0 || variable > 99 )
                {
                    check = true;
                    cout << "Please provide valid index\n";
                    cin.clear();
                    cin.ignore(100,'\n');
                }
            } while(check);
            
            matrix[i][j] = A[variable/10][variable%10];
        }
    }
}

Matrix::Matrix(Matrix &x)
{
    this->size = x.size;
    matrix =  new int* [x.size];
    for (int i=0; i < size; i++)
    {
        matrix[i] = new int [size];
    }
    for (int i=0; i < size; i++)
    {
        for (int j=0; j < size; j++){
            matrix[i][j] = x.matrix[i][j];
        }
    }
}

void Matrix::operator+(Matrix x)
{  
    // matrix1 + matrix2
    Matrix temp (size);
    cout << green << "Result of Matrix1 + Matrix2: \n"
         << white;
    for (int i=0; i < size; i++)
    {
        for (int j=0; j < size; j++)
        {
            temp.matrix[i][j] = this->matrix[i][j] + x.matrix[i][j];
        }
    }
    cout << temp;
}

void Matrix::operator-(Matrix x)
{
    Matrix temp (size);
    cout << green << "Result of Matrix1 - Matrix2:\n" << white;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp.matrix[i][j] = this->matrix[i][j] - x.matrix[i][j];
        }
    }
    cout << temp;
}

void Matrix::operator++(){
    Matrix result(size);
    if (matrix != nullptr && result.matrix != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.matrix[i][j] = ++matrix[i][j];
            }
        }
    }
}

void Matrix::operator++(int x)
{
    Matrix result(size);
    if (result.matrix != nullptr && matrix != nullptr)
    {
        for (int i = 0; i < size; i++)
        { 
            for (int j = 0; j < size; j++)
            {
                result.matrix[i][j] = matrix[i][j]++;
            }
        }
    }
}

void Matrix::operator--()
{
    Matrix result(size);
    if (matrix != nullptr && result.matrix != nullptr){
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.matrix[i][j] = --matrix[i][j];
            }
        }
    }
}

void Matrix::operator--(int x)
{
    Matrix result(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (result.matrix != nullptr && result.matrix != nullptr){
                result.matrix[i][j] = matrix[i][j]--;
            }
        }
    }
}

void Matrix::operator!()
{
    cout << green << "After selecting, Traverse the Matrix operation" << endl << white;
    Matrix result(size); 
    if (result.matrix != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.matrix[i][j] = matrix[j][i];
            }
        }
    }
    cout << result;
}

void Matrix::operator*(Matrix x)
{
    Matrix temp(size);
    cout << green << "Result of Matrix1 * Matrix2:\n" << white;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                temp.matrix[i][j] += this->matrix[i][k] * x.matrix[k][j];
            }
        }
    }
    cout << temp;
}

Matrix& Matrix::operator=(Matrix &x)
{
    DeallocateMatrix();
    this->size = x.size;
    matrix = new int*[x.size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[x.size];
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = x.matrix[i][j];
        }
    }
    return x;
}