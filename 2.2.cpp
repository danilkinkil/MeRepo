#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;
#asdasdwasdas
template<typename T>
vector<vector<double>> fillMatrixRandomD(vector<vector<T>>& matrix, T minVal, T maxVal)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<T> dis(minVal, maxVal);

    for (auto& row : matrix)
    {
        for (auto& elem : row)
        {
            elem = dis(gen);
        }
    }
    return matrix;
}
template<typename T>
T determinant(const vector<vector<T>>& matrix)
{
    int size = matrix.size();
    if (size == 1)
    {
        return matrix[0][0]; // Для матрицы 1x1 определитель равен ее единственному элементу
    }
    else if (size == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]; // Для матрицы 2x2
    }
    else
    {
        // Для матрицы размера больше 2x2 используем метод Гаусса для вычисления определителя
        T det = 0;
        for (int j = 0; j < size; ++j)
        {
            // Вычисляем минор
            vector<vector<T>> minorMatrix(size - 1, vector<T>(size - 1));
            for (int m = 1; m < size; ++m)
            {
                for (int n = 0; n < size; ++n)
                {
                    if (n < j) {
                        minorMatrix[m - 1][n] = matrix[m][n];
                    }
                    else if (n > j)
                    {
                        minorMatrix[m - 1][n - 1] = matrix[m][n];
                    }
                }
            }
            // Рекурсивно вычисляем определитель
            det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * determinant(minorMatrix);
        }
        return det;
    }
}

// Шаблонная функция для нахождения обратной матрицы
template<typename T>
vector<vector<T>> inverse(const vector<vector<T>>& matrix)
{
    int size = matrix.size();
    // Проверяем, является ли матрица квадратной
    if (size != matrix[0].size())
    {
        cerr << "Матрица должна быть квадратной!" << endl;
        return {};
    }
    // Вычисляем определитель матрицы
    T det = determinant(matrix);
    if (det == 0)
    {
        cerr << "Матрица вырожденная, обратной не существует!" << endl;
        return {};
    }
    // Создаем матрицу алгебраических дополнений
    vector<vector<T>> adjointMatrix(size, vector<T>(size));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // Вычисляем минор для каждого элемента
            vector<vector<T>> minorMatrix(size - 1, vector<T>(size - 1));
            for (int m = 0; m < size; ++m)
            {
                for (int n = 0; n < size; ++n)
                {
                    if (m != i && n != j)
                    {
                        int p = (m < i) ? m : m - 1;
                        int q = (n < j) ? n : n - 1;
                        minorMatrix[p][q] = matrix[m][n];
                    }
                }
            }
            // Вычисляем алгебраическое дополнение
            adjointMatrix[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinant(minorMatrix);
        }
    }
    // Вычисляем обратную матрицу как транспонированную матрицу алгебраических дополнений,
    // разделенную на определитель исходной матрицы
    vector<vector<T>> inverseMatrix(size, vector<T>(size));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            inverseMatrix[i][j] = adjointMatrix[i][j] / det;
        }
    }
    return inverseMatrix;
}
int main()
{
    int size;
    int n;
    int povtor = 1;

    cout << "Введите размер квадратной матрицы: ";
    cin >> size;


    int vibor;



    vector<vector<double>> matrix(size, vector<double>(size));
    vector<vector<double>> new_matrix(size, vector<double>(size));
    auto start = high_resolution_clock::now();
    matrix = fillMatrixRandomD(matrix, 0.0, 10.0);

    new_matrix = inverse(matrix);


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Время выполнения: " << duration.count() << " микросекунд" << endl;


    return 0;
}
