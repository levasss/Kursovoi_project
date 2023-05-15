#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функция для решения СЛАУ методом Зейделя
vector<double> solve_seidel(vector<vector<double>>& A, vector<double>& b, double eps)
{
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_old(n, 0.0);
    double diff = eps + 1.0;

    while (diff > eps) {
        x_old = x;
        for (int i = 0; i < n; ++i) {
            double s1 = 0.0, s2 = 0.0;
            for (int j = 0; j < i; ++j) {
                s1 += A[i][j] * x[j];
            }
            for (int j = i + 1; j < n; ++j) {
                s2 += A[i][j] * x_old[j];
            }
            x[i] = (b[i] - s1 - s2) / A[i][i];
        }
        diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += abs(x[i] - x_old[i]);
        }
    }
    return x;
}

int main()
{
    cout << "Viberite rejim vvoda:" << endl;
    cout << "1 - ruchnoi vvod" << endl;
    cout << "2 - chtenie iz faila" << endl;
    int k;
    cin >> k;
    if (k = 1) {
        int n;
        double eps;
        cout << "Vvedite razmernost" << endl;
        cin >> n;
        cout << "Vvedite tochnost'" << endl;
        cin >> eps;
        vector<vector<double>> A(n, vector<double>(n, 0.0));
        vector<double> b(n, 0.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << "A[" << i << "][" << j << "] = ";
                cin >> A[i][j];
            }
            cout << "b[" << i << "] = ";
            cin >> b[i];
        }
        vector<double> x = solve_seidel(A, b, eps);
        cout << "Reshenie: " << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i << "] = " << x[i] << endl;
        }
        return 0;
    }
    else {
        ifstream in_file("input.txt");
        if (!in_file) {
            cout << "Oshibka chteniya faila" << endl;
            return 1;
        }
        int n;
        double eps;
        in_file >> n >> eps;
        vector<vector<double>> A(n, vector<double>(n, 0.0));
        vector<double> b(n, 0.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in_file >> A[i][j];
            }
            in_file >> b[i];
        }
        in_file.close();
        vector<double> x = solve_seidel(A, b, eps);
        cout << "Reshenie: " << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i << "] = " << x[i] << endl;
        }
        return 0;
    }
}
