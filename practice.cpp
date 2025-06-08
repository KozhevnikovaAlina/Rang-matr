#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include<string>

using namespace std;

// Функция для безопасного ввода целого числа > 0
int read_positive_int(const char* prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x > 0) {
            return x;
        }
        cerr << "Ошибка: введите целое число больше 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Функция для безопасного ввода вещественного числа
double read_double(const char* prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            return x;
        }
        cerr << "Ошибка: введите корректное число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Вычисление ранга матрицы методом Гаусса
int matrix_rank(vector<vector<double>>& A, int m, int n) {
    const double EPS = 1e-9;
    int rank = 0;
    vector<bool> used_row(m, false);

    for (int col = 0; col < n; ++col) {
        // Находим ненулевую строку с максимальным по модулю элементом в текущем столбце
        int sel = -1;
        double max_abs = EPS;
        for (int row = 0; row < m; ++row) {
            if (!used_row[row] && fabs(A[row][col]) > max_abs) {
                max_abs = fabs(A[row][col]);
                sel = row;
            }
        }
        // Если подходящая строка не найдена, переходим к следующему столбцу
        if (sel == -1) continue;

        // Эта строка станет ведущей для текущего шага
        used_row[sel] = true;
        ++rank;

        // Нормируем ведущую строку (делим всю строку на ведущий элемент)
        double lead = A[sel][col];
        for (int j = col; j < n; ++j) {
            A[sel][j] /= lead;
        }

        // Обнуляем все остальные элементы в этом столбце
        for (int row = 0; row < m; ++row) {
            if (row != sel) {
                double factor = A[row][col];
                for (int j = col; j < n; ++j) {
                    A[row][j] -= factor * A[sel][j];
                }
            }
        }
    }

    return rank;
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "=== Программа для нахождения ранга матрицы методом Гаусса ===\n";

    // Ввод размеров
    int m = read_positive_int("Введите число строк m: ");
    int n = read_positive_int("Введите число столбцов n: ");

    // Создаём и заполняем матрицу
    vector<vector<double>> A(m, vector<double>(n));
    cout << "Введите элементы матрицы A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = read_double(("A[" + to_string(i + 1) + "][" + to_string(j + 1) + "] = ").c_str());
        }
    }

    int rank = matrix_rank(A, m, n);
    cout << "\nРанг матрицы равен: " << rank << endl;

    return 0;
}