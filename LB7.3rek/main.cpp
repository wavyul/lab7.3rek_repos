#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** a, const int K, const int N, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < K - 1)
        CreateRows(a, K, N, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int K, const int N, int rowNo)
{
    PrintRow(a, rowNo, N, 0);
    if (rowNo < K - 1)
        PrintRows(a, K, N, rowNo + 1);
    else
        cout << endl;
}

bool checkNeighbours(int** a, int i, int j, int x, int y, int size, int current)
{
    if (x < 0 || x >= size || y < 0 || y >= size)
        return true;
    if (x == i && y == j)
        return true;

    if (a[x][y] <= current)
        return false;

    if (y < j + 1)
        return checkNeighbours(a, i, j, x, y + 1, size, current);
    else if (x < i + 1)
        return checkNeighbours(a, i, j, x + 1, j - 1, size, current);

    return true;
}

bool isLocalMin(int** a, int i, int j, int size)
{
    return checkNeighbours(a, i, j, i - 1, j - 1, size, a[i][j]);
}

int countLocalMinimaRec(int** a, int i, int j, int size)
{
    if (i >= size - 1)
        return 0;

    int count = 0;

    if (j >= size - 1)
        return count + countLocalMinimaRec(a, i + 1, 1, size);

    if (isLocalMin(a, i, j, size))
        count++;

    return count + countLocalMinimaRec(a, i, j + 1, size);
}

void countLocalMinima(int** a, const int size)
{
    int count = countLocalMinimaRec(a, 1, 1, size);
    cout << "Кількість локальних мінімумів: " << count << endl;
}

int sumAboveMainDiagonalRec(int** a, int i, int j, const int size)
{
    if (i >= size)
        return 0;

    if (j >= size)
        return sumAboveMainDiagonalRec(a, i + 1, i + 2, size);

    return abs(a[i][j]) + sumAboveMainDiagonalRec(a, i, j + 1, size);
}

int sumAboveMainDiagonal(int** a, const int size)
{
    return sumAboveMainDiagonalRec(a, 0, 1, size);
}


int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Low = -10;
    int High = 10;
    int size;

    cout << "Введіть розмір матриці n: ";
    cin >> size;

    int** a = new int* [size];

    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    CreateRows(a, size, size, Low, High, 0);

    PrintRows(a, size, size, 0);

    countLocalMinima(a, size);

    int sum = sumAboveMainDiagonal(a, size);
    cout << "Сума модулів елементів вище головної діагоналі: " << sum << endl;

    for (int i = 0; i < size; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
