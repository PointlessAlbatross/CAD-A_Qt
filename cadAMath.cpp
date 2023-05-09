#include "cadAMath.h"

CadAMath::CadAMath()
{

}


double CadAMath::simpson(std::function<double (double)> f, double a, double b, int n)
{
    double h = (b - a) / n;

        // Вычисляем значение функции на узлах
        double x0 = f(a);
        double xn = f(b);
        double xi = 0.0;
        for (int i = 1; i < n; ++i) {
            xi += f(a + i * h);
        }

        // Считаем интеграл методом Симпсона
        double integral = h / 3 * (x0 + 4 * xi + 2 * xn);
        return integral;
}

double CadAMath::simpson2(std::function<double (double, double)> f, double a1, double b1, double a2, double b2, int n1, int n2)
{
    double h1 = (b1 - a1) / n1;
    double h2 = (b2 - a2) / n2;

    double sum = 0.0;
    for (int i = 0; i <= n1; i++) {
        double x1 = a1 + i * h1;
        for (int j = 0; j <= n2; j++) {
            double x2 = a2 + j * h2;

            double w1 = 1.0, w2 = 1.0;
            if (i == 0 || i == n1) w1 = 1.0 / 3.0;
            if (j == 0 || j == n2) w2 = 1.0 / 3.0;
            if ((i == 0 || i == n1) && (j == 0 || j == n2)) w1 = w2 = 1.0 / 9.0;

            sum += w1 * w2 * f(x1, x2);
        }
    }

    return (b1 - a1) * (b2 - a2) * sum / (n1 * n2);
}

double CadAMath::simpson3(std::function<double (double, double, double)> f, double a1, double b1, double a2, double b2, double a3, double b3, int n)
{
    double h1 = (b1 - a1) / (2.0 * n);
    double h2 = (b2 - a2) / (2.0 * n);
    double h3 = (b3 - a3) / (2.0 * n);
    double x1 = a1;
    double x2 = a2;
    double x3 = a3;

    double sum = 0.0;
    for (int i = 0; i <= 2 * n; i++) {
        x2 = a2;
        for (int j = 0; j <= 2 * n; j++) {
            x3 = a3;
            for (int k = 0; k <= 2 * n; k++) {
                double coef1 = 1.0;
                if (i == 0 || i == 2 * n) coef1 = 1.0;
                else if (i % 2 == 0) coef1 = 2.0;
                else coef1 = 4.0;

                double coef2 = 1.0;
                if (j == 0 || j == 2 * n) coef2 = 1.0;
                else if (j % 2 == 0) coef2 = 2.0;
                else coef2 = 4.0;

                double coef3 = 1.0;
                if (k == 0 || k == 2 * n) coef3 = 1.0;
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
