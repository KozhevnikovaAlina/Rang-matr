#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include<string>

using namespace std;

// ������� ��� ����������� ����� ������ ����� > 0
int read_positive_int(const char* prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x > 0) {
            return x;
        }
        cerr << "������: ������� ����� ����� ������ 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ������� ��� ����������� ����� ������������� �����
double read_double(const char* prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            return x;
        }
        cerr << "������: ������� ���������� �����.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ���������� ����� ������� ������� ������
int matrix_rank(vector<vector<double>>& A, int m, int n) {
    const double EPS = 1e-9;
    int rank = 0;
    vector<bool> used_row(m, false);

    for (int col = 0; col < n; ++col) {
        // ������� ��������� ������ � ������������ �� ������ ��������� � ������� �������
        int sel = -1;
        double max_abs = EPS;
        for (int row = 0; row < m; ++row) {
            if (!used_row[row] && fabs(A[row][col]) > max_abs) {
                max_abs = fabs(A[row][col]);
                sel = row;
            }
        }
        // ���� ���������� ������ �� �������, ��������� � ���������� �������
        if (sel == -1) continue;

        // ��� ������ ������ ������� ��� �������� ����
        used_row[sel] = true;
        ++rank;

        // ��������� ������� ������ (����� ��� ������ �� ������� �������)
        double lead = A[sel][col];
        for (int j = col; j < n; ++j) {
            A[sel][j] /= lead;
        }

        // �������� ��� ��������� �������� � ���� �������
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
    cout << "=== ��������� ��� ���������� ����� ������� ������� ������ ===\n";

    // ���� ��������
    int m = read_positive_int("������� ����� ����� m: ");
    int n = read_positive_int("������� ����� �������� n: ");

    // ������ � ��������� �������
    vector<vector<double>> A(m, vector<double>(n));
    cout << "������� �������� ������� A (" << m << "x" << n << "):\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = read_double(("A[" + to_string(i + 1) + "][" + to_string(j + 1) + "] = ").c_str());
        }
    }

    int rank = matrix_rank(A, m, n);
    cout << "\n���� ������� �����: " << rank << endl;

    return 0;
}