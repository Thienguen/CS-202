#include "matrix.h"

using namespace std;

/**
 * @brief display menu
 * 
 */

void displayMenu(void)
{
    string stars(34, '*');

    cout << endl;
    cout << stars << endl;
    cout << "|          Menu                  |" << endl;
    cout << "|0. quit                         |" << endl;
    cout << "|1. Add(+) matrix                |" << endl;
    cout << "|2. Sub(-) matrix                |" << endl;
    cout << "|3. Mul(*) matrix                |" << endl;
    cout << "|4. (++)pre-increment matrix     |" << endl;
    cout << "|5. post-increment(++) matrix    |" << endl;
    cout << "|6. (--)pre-decrement matrix     |" << endl;
    cout << "|7. post-decrement(--) matrix    |" << endl;
    cout << "|8. Assignment(=) operation      |" << endl;
    cout << "|9. Copy constructor             |" << endl;
    cout << "|10. transpose(!) matrix         |" << endl;
    cout << stars << endl;
    cout << "Provide the input " << endl;
    cout << endl;
}

/**
 * @brief mail function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv)
{
    string stars(34, '*');
    
    ifstream input_file;
    ifstream input_file2;

    int readMatrix1[rows][cols];
    int readMatrix2[rows][cols];
    
    int open = 100;
    int size;

    if (argc == 1)
    {
        cerr << "Usage: ./main matrix_1.txt matrix_2.txt " << endl;
        return -1;
    }
    else if (argc > 3)
    {
        cerr << "Error: Too many command line arguments " << endl;
        return -1;
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "matrix_1.txt"))
        {
            cerr << "Error: Invalid file extension " << endl;
            return -1;
        }
        cout << "file1 name = " << argv[1] << endl;
        if (strcmp(argv[2], "matrix_2.txt"))
        {
            cerr << "Error: Invalid file extension " << endl;
            return -1;
        }
        cout << "file2 name = " << argv[2] << endl;
    }

    if (fileOpen(input_file, argv[1]) == -1)
    {
        cerr << "\n file open: input file" << endl;
        return -1;
    }

    if (fileOpen(input_file2, argv[2]) == -1)
    {
        cerr << "\n file open: input file" << endl;
        return -1;
    }

    fileRead(input_file, readMatrix1);
    input_file.close();

    fileRead(input_file2, readMatrix2);
    input_file2.close();

    while (1)
    {
        cout << "Enter squre matrix size min : 1 and max: 10 " << endl;
        cin >> size;
        if ((size <= 0) || (size > 10))
        {
            cout << "Error :- wrong size " << endl;
            cout << "Please provide valid input " << endl;
        }
        else
        {
            cout << "Matrix Size " << size << " X " << size << endl;
            break;
        }
    }
    cout << endl;
    Matrix mat1(size);
    Matrix mat2(size);
    Matrix mat3(size);

    // print_matrix(readMatrix1, rows, cols);
    cout << "Create Matrix 1 form matrix_1.txt" << endl;
    mat1.createMatrix(readMatrix1);
    mat1.display();

    // print_matrix(readMatrix2, rows, cols);
    cout << "Create Matrix 2 from matrix_2.txt" << endl;
    mat2.createMatrix(readMatrix2);
    mat2.display();

    while (open != 0)
    {
        displayMenu();
        cin >> open;
        switch (open)
        {
        case 0:
            cout << "quit " << endl;
            break;
        case 1:
            cout << stars << endl;
            cout << "Addition of two given Matrices is : " << endl;
            mat1 + mat2;
            cout << stars << endl;
            break;
        case 2:
            cout << stars << endl;
            cout << "Subtraction of two given Matrices is : " << endl;
            mat1 - mat2;
            cout << stars << endl;
            break;
        case 3:
            cout << stars << endl;
            cout << "Multiplication of two given Matrices is : " << endl;
            mat1 *mat2;
            cout << stars << endl;
            break;
        case 4:
            cout << stars << endl;
            cout << "(++)pre-increment of Matrix1 : " << endl;
            ++mat1;
            cout << mat1;
            cout << "(++)pre-increment of Matrix2 : " << endl;
            ++mat2;
            cout << mat2;
            cout << stars << endl;
            break;
        case 5:
            cout << stars << endl;
            cout << "post-increment(++) of Matrix1 : " << endl;
            mat1++;
            cout << mat1;
            cout << "post-increment(++) of Matrix2 : " << endl;
            mat2++;
            cout << mat2;
            cout << stars << endl;
            break;
        case 6:
            cout << stars << endl;
            cout << "(--)pre-decrement of Matrix1 : " << endl;
            --mat1;
            cout << mat1;
            cout << "(--)dec-increment of Matrix2 : " << endl;
            --mat2;
            cout << mat2;
            cout << stars << endl;
            break;
        case 7:
            cout << stars << endl;
            cout << "post-decrement(--) of Matrix1 : " << endl;
            mat1--;
            cout << mat1;
            cout << "post-decrement(--) of Matrix2 : " << endl;
            mat2--;
            cout << mat2;
            cout << stars << endl;
            break;
        case 8:
        {
            cout << stars << endl;
            Matrix mat3(size);
            cout << "perform assignment operation (matrix1=new matrix) of two given Matrices is : " << endl;
            cout << "Matrix1 : " << endl;
            cout << mat1;
            cin >> mat3;
            cout << "New Matrix : " << endl;
            cout << mat3;
            mat1 = mat3;
            cout << "Matrix1 : " << endl;
            cout << mat1;
            cout << stars << endl;
            break;
        }
        case 9:
        {
            cout << stars << endl;
            cout << "perform copy constructor operation:  " << endl;
            Matrix mat4 = mat1;
            cout << "Matrix1 : " << endl;
            cout << mat1;
            cout << "Result Matrix after copy constructor : " << endl;
            cout << mat4;
            cout << stars << endl;
        }
        break;
        case 10:
            cout << stars << endl;
            cout << "transpose(!) matrix1" << endl;
            !mat1;
            cout << "transpose(!) matrix2" << endl;
            !mat2;
            cout << stars << endl;

            break;
        default:
            cout << " Wrong operation please try again " << endl;
            displayMenu();
            break;
        }
    }

    cout << "\n This is what a matrix look like\n";
    print_matrix(readMatrix1, rows, cols);
    
    cout << "\n This is what a matrix look like\n";
    print_matrix(readMatrix2, rows, cols);
    return 0;
}

// make all
// ./main matrix_1.txt matrix_2.txt