// MatrixMultiplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

typedef std::vector<int> row;
typedef std::vector<row> matrix;

int read_int(int limit = 999, bool positive = false)
{
    int i;
    bool not_valid = false;
    do
    {
        std::cin >> i;
        not_valid = std::cin.fail();
        std::cin.clear();
        if (not_valid)
            std::cout << "Please enter a valid integer" << std::endl;
        else if (positive && i <= 0)
        {
            std::cout << "Please enter a positive integer" << std::endl;
            not_valid = true;
            continue;
        }

        if(i > limit || i < -limit)
        {
            std::cout << "Please enter an integer in the limits: [-" << limit << ", " << limit << "]" << std::endl;
            not_valid = true;
        }

    } while (not_valid);

    return i;
}

row read_line(size_t no_col)
{
    row a_row;
    std::cout << "Enter " << no_col << " integers separated by <Return>" << std::endl;

    for (size_t i = 0; i < no_col; ++i)
        a_row.emplace_back(read_int());

    return a_row;
}

matrix read_matrix(size_t no_rows, size_t no_cols)
{
    matrix m;
    for (size_t i = 0; i < no_rows; ++i)
    {
        std::cout << "Row " << i + 1 << std::endl;
        m.emplace_back(read_line(no_cols));
    }

    return m;
}

void print_matrix(matrix x)
{
    for (row r : x)
    {
        for (int i : r)
            std::cout << std::setw(15) << i;
        std::cout << std::endl;
    }
}

matrix multiply(matrix m1, matrix m2)
{
    assert(m1.size() > 0);
    assert(m2.size() > 0);

    // m1 is N lines, M columns
    size_t N = m1.size();
    size_t M = m1.at(0).size();

    // m2 is M lines, P columns
    assert(m2.size() == M);
    size_t P = m2.at(0).size();

    matrix result;
    row result_row;
    result_row.reserve(P);

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t k = 0; k < P; ++k)
        {
            int cell_value = 0;
            for (size_t j = 0; j < M; ++j)
                cell_value += m1.at(i).at(j)*m2.at(j).at(k);

            result_row.emplace_back(cell_value);
        }
        result.emplace_back(result_row);
        result_row.clear();
        result_row.reserve(P);
    }
    return result;
}

void run_tests()
{
    matrix a = { {6, 2 ,9}, {1,7,3} };
    matrix b = { {1, 0, -1, 2}, {-2, 1, 3, 0}, {1, -1, 2, 1} };
    matrix result = { {11, -7, 18, 21}, {-10, 4, 26, 5} };
    assert(result == multiply(a, b));
    matrix a1 = { {1, 2}, {3, 4}, {5, 6} };
    matrix b1 = { {1, 2, 3}, {4, 5, 6} };
    matrix result1 = { {9, 12, 15}, {19, 26, 33}, {29, 40, 51} };
    assert(result1 == multiply(a1, b1));
    std::cout << "All tests completed with success" << std::endl;
}

int main()
{
    std::cout << "Press 't' for running tests, 'i' for interactive mode or 'x' for exit." << std::endl;

    char c;
    do
    {
        std::cin >> c;
        if (c == 'i')
            break;
        else if (c == 't')
        {
            run_tests();
            exit(0);
        }
        else if (c == 'x')
            exit(0);

    } while (true);

    std::cout << "This program performs matrix multiplication." << std::endl;
    std::cout << "The matrix dimension cannot exceed 20." << std::endl;
    std::cout << "The elements of a matrix are integers in the limits[-999, 999]." << std::endl;
    std::cout << "Please enter the first matrix number of rows:" << std::endl;
    size_t N = read_int(20, true);
    std::cout << "Please enter the first matrix number of columns:" << std::endl;
    size_t M = read_int(20, true);
    std::cout << "The second matrix number of rows equals the first matrix number of columns: " << M << std::endl;
    std::cout << "Please enter the second matrix number of columns:" << std::endl;
    size_t P = read_int(20, true);

    std::cout << "Please enter now the first matrix elements:" << std::endl;
    matrix a = read_matrix(N, M);
    std::cout << "Please enter now the second matrix elements:" << std::endl;
    matrix b = read_matrix(M, P);


    std::cout << "This is the first matrix:" << std::endl << std::endl;
    print_matrix(a);
    std::cout << std::endl << "This is the second matrix:" << std::endl << std::endl;
    print_matrix(b);
    matrix product = multiply(a, b);
    std::cout << std::endl << "This is the first matrix multiplied with the second matrix:" << std::endl << std::endl;
    print_matrix(product);
}
