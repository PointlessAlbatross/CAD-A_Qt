#include "cadAMath.h"

CadAMath::CadAMath()
{

}

/*
CadAMath::simpson(std::function<double (double)> f, double a, double b, int n)
{
    double h = (b - a) / n;

        // Вычисляем значение функции на узлах
        T x0 = f(a);
        T xn = f(b);
        T xi = 0.0;
        for (int i = 1; i < n; ++i) {
            xi += f(a + i * h);
        }

        // Считаем интеграл методом Симпсона
        T integral = h / 3 * (x0 + 4 * xi + 2 * xn);
        return integral;
}

CadAMath::simpson2(std::function<double (double, double)> f, double a1, double b1, double a2, double b2, int n1, int n2)
{
    double h1 = (b1 - a1) / n1;
    double h2 = (b2 - a2) / n2;

    T sum = 0.0;
    for (int i = 0; i <= n1; i++) {
        T x1 = a1 + i * h1;
        for (int j = 0; j <= n2; j++) {
            T x2 = a2 + j * h2;

            T w1 = 1.0, w2 = 1.0;
            if (i == 0 || i == n1) w1 = 1.0 / 3.0;
            if (j == 0 || j == n2) w2 = 1.0 / 3.0;
            if ((i == 0 || i == n1) && (j == 0 || j == n2)) w1 = w2 = 1.0 / 9.0;

            sum += w1 * w2 * f(x1, x2);
        }
    }

    return (b1 - a1) * (b2 - a2) * sum / (n1 * n2);
}

CadAMath::simpson3(std::function<double (double, double, double)> f, double a1, double b1, double a2, double b2, double a3, double b3, int n1, int n2, int n3)
{
    double h1 = (b1 - a1) / (2.0 * n1);
    double h2 = (b2 - a2) / (2.0 * n2);
    double h3 = (b3 - a3) / (2.0 * n3);
    double x1 = a1;
    double x2 = a2;
    double x3 = a3;

    T sum = 0.0;
    for (int i = 0; i <= 2 * n1; i++) {
        x2 = a2;
        for (int j = 0; j <= 2 * n2; j++) {
            x3 = a3;
            for (int k = 0; k <= 2 * n3; k++) {
                double coef1 = 1.0;
                if (i == 0 or i == 2 * n1)
                    coef1 = 1.0;
                else if (i % 2 == 0)
                    coef1 = 2.0;
                else
                    coef1 = 4.0;

                double coef2 = 1.0;
                if (j == 0 || j == 2 * n2) coef2 = 1.0;
                else if (j % 2 == 0) coef2 = 2.0;
                else coef2 = 4.0;

                double coef3 = 1.0;
                if (k == 0 || k == 2 * n3) coef3 = 1.0;
                else if (k % 2 == 0) coef3 = 2.0;
                else coef3 = 4.0;

                sum += coef1 * coef2 * coef3 * f(x1, x2, x3);
                x3 += h3;
            }
            x2 += h2;
        }
        x1 += h1;
    }
    return (h1 * h2 * h3 / 27.0) * sum;
}

T CadAMath::romberg(std::function<T(double)> f, double a, double b, int n)
{
        T h[n+1], R[n+1][n+1];
        h[0] = b - a;
        R[0][0] = 0.5 * h[0] * (f(a) + f(b));

        for (int i = 1; i <= n; i++) {
            h[i] = h[i-1] / 2;
            double sum = 0;
            for (int k = 1; k <= pow(2, i-1); k++) {
                sum += f(a + (2*k-1)*h[i]);
            }
            R[i][0] = 0.5 * R[i-1][0] + h[i] * sum;
            for (int j = 1; j <= i; j++) {
                R[i][j] = (pow(4, j) * R[i][j-1] - R[i-1][j-1]) / (pow(4, j) - 1);
            }
        }

        return R[n][n];
    }
template <typename T>
T CadAMath::romberg2(std::function<T(double, double)> f, double a1, double b1, double a2, double b2, int n, int m)
{
    double h1 = (b1 - a1) / (1 << (n - 1));
    double h2 = (b2 - a2) / (1 << (m - 1));

    QVector<QVector<T>> R(n, QVector<T>(m));
    R[0][0] = 0.5 * (f(a1, a2) + f(b1, b2)) * h1 * h2;

    for (int i = 1; i < n; ++i) {
        h1 /= 2;
        R[i][0] = 0;
        for (int k = 0; k < (1 << (i - 1)); ++k) {
            R[i][0] += f(a1 + (2*k + 1)*h1, a2) * h2;
        }
        R[i][0] = 0.5*R[i-1][0] + R[i][0]*h1;
    }

    for (int j = 1; j < m; ++j) {
        h2 /= 2;
        R[0][j] = 0;
        for (int k = 0; k < (1 << (j - 1)); ++k) {
            R[0][j] += f(a1, a2 + (2*k + 1)*h2) * h1;
        }
        R[0][j] = 0.5*R[0][j-1] + R[0][j]*h2;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            R[i][j] = (1.0/(pow(4, i) - 1)) * (pow(4, i)*R[i-1][j] - R[i-1][j-1]);
        }
    }

    return R[n-1][m-1];
}
template <typename T>
T CadAMath::romberg3(const std::function<T(double, double, double)> f,
                          double a1, double b1,
                          double a2, double b2,
                          double a3, double b3, int n1, int n2, int n3)
{
    QVector<QVector<QVector<T>>> R(n1 + 1, QVector<QVector<T>>(n2 + 1, QVector<T>(n3 + 1)));
        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                for (int k = 0; k <= n3; k++) {
                    double h1 = (b1 - a1) / pow(2, i);
                    double h2 = (b2 - a2) / pow(2, j);
                    double h3 = (b3 - a3) / pow(2, k);

                    if (i == 0 && j == 0 && k == 0) {
                        R[i][j][k] = (b1 - a1) * (b2 - a2) * (b3 - a3) * f(a1, a2, a3);
                    } else {
                        T sum = 0.0;
                        for (int l = 0; l < pow(2, i - 1); l++) {
                            for (int m = 0; m < pow(2, j - 1); m++) {
                                for (int o = 0; o < pow(2, k - 1); o++) {
                                    double x1 = a1 + (2 * l + 1) * h1;
                                    double x2 = a2 + (2 * m + 1) * h2;
                                    double x3 = a3 + (2 * o + 1) * h3;
                                    sum += f(x1, x2, x3);
                                }
                            }
                        }
                        R[i][j][k] = 0.25 * R[i-1][j-1][k-1] + (pow(2, i-2) * pow(2, j-2) * pow(2, k-2) / pow(2, i+j+k-3)) * h1 * h2 * h3 * sum;
                    }
                }
            }
        }

        return R[n1][n2][n3];
}
*/

double CadAMath::monteCarlo(std::function<double(double)> f,
                   double a, double b, int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(a, b);
    double sum = 0;
    for (int i = 0; i < N; ++i)
    {
        double x = dist1(gen);
        sum += f(x);
    }
    return sum * (b - a) / N;
}

std::complex<double> CadAMath::monteCarlo2(std::function<std::complex<double>(double, double)> f,
                   double a1, double b1,
                   double a2, double b2,int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(a1, b1);
    std::uniform_real_distribution<> dist2(a2, b2);
    std::complex<double>  sum = 0;
    for (int i = 0; i < N; ++i)
    {
        double x1 = dist1(gen);
        double x2 = dist2(gen);
        sum += f(x1, x2);
    }
    return sum * (b1 - a1) * (b2 - a2) / double(N);
}

double CadAMath::monteCarlo3(std::function<double(double, double, double)> f,
                   double a1, double b1,
                   double a2, double b2,
                   double a3, double b3,int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(a1, b1);
    std::uniform_real_distribution<> dist2(a2, b2);
    std::uniform_real_distribution<> dist3(a3, b3);
    double sum = 0;
    for (int i = 0; i < N; ++i)
    {
        double x1 = dist1(gen);
        double x2 = dist2(gen);
        double x3 = dist3(gen);
        sum += f(x1, x2, x3);
    }
    return sum * (b1 - a1) * (b2 - a2) * (b3 - a3) / N;
}
