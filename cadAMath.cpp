#include "cadAMath.h"

CadAMath::CadAMath()
{

}


std::complex<double> CadAMath::simpson(const std::function<std::complex<double>(double)>& func, double a, double b, int n)
{
    double h = (b - a) / n; // Шаг интегрирования
    std::complex<double> sum = func(a) + func(b); // Сумма на границах

    for (int i = 1; i < n; i += 2) {
        double x = a + i * h;
        sum += 4.0 * func(x); // Сумма с множителем 4
    }

    for (int i = 2; i < n - 1; i += 2) {
        double x = a + i * h;
        sum += 2.0 * func(x); // Сумма с множителем 2
    }

    return (h / 3.0) * sum; // Возвращаем результат интегрирования
}

std::complex<double> CadAMath::simpson2(const std::function<std::complex<double>(double, double)>& func, double ax, double bx, double ay, double by, int n)
{
    double hx = (bx - ax) / n; // Шаг интегрирования по x
    double hy = (by - ay) / n; // Шаг интегрирования по y

    std::complex<double> sum = func(ax, ay) + func(bx, ay) + func(ax, by) + func(bx, by); // Сумма на границах

    for (int i = 1; i < n; i += 2) {
        double x = ax + i * hx;
        for (int j = 1; j < n; j += 2) {
            double y = ay + j * hy;
            sum += 4.0 * func(x, y); // Сумма с множителем 4
            }
        }

        for (int i = 2; i < n - 1; i += 2) {
            double x = ax + i * hx;
            for (int j = 2; j < n - 1; j += 2) {
                double y = ay + j * hy;
                sum += 2.0 * func(x, y); // Сумма с множителем 2
            }
        }

        return (hx * hy / 9.0) * sum; // Возвращаем результат интегрирования
}

std::complex<double> CadAMath::simpson3(const std::function<std::complex<double>(double, double, double)>& func, double ax, double bx,
                                        double ay, double by, double az, double bz, int n)
{
    double hx = (bx - ax) / n; // Шаг интегрирования по x
    double hy = (by - ay) / n; // Шаг интегрирования по y
    double hz = (bz - az) / n; // Шаг интегрирования по z

    std::complex<double> sum = func(ax, ay, az) + func(bx, ay, az) + func(ax, by, az) + func(bx, by, az)
                             + func(ax, ay, bz) + func(bx, ay, bz) + func(ax, by, bz) + func(bx, by, bz); // Сумма на границах

    for (int i = 1; i < n; i += 2) {
        double x = ax + i * hx;
        for (int j = 1; j < n; j += 2) {
            double y = ay + j * hy;
            for (int k = 1; k < n; k += 2) {
                double z = az + k * hz;
                sum += 8.0 * func(x, y, z); // Сумма с множителем 8
            }
        }
    }
    for (int i = 2; i < n - 1; i += 2) {
        double x = ax + i * hx;
        for (int j = 2; j < n - 1; j += 2) {
            double y = ay + j * hy;
            for (int k = 2; k < n - 1; k += 2) {
                double z = az + k * hz;
                sum += 64.0 * func(x, y, z); // Сумма с множителем 64
            }
        }
    }
    for (int i = 1; i < n; i += 2) {
        double x = ax + i * hx;
        for (int j = 2; j < n - 1; j += 2) {
            double y = ay + j * hy;
            for (int k = 2; k < n - 1; k += 2) {
                double z = az + k * hz;
                sum += 32.0 * func(x, y, z); // Сумма с множителем 32
            }
        }
    }
    for (int i = 2; i < n - 1; i += 2) {
        double x = ax + i * hx;
        for (int j = 2; j < n - 1; j += 2) {
            double y = ay + j * hy;
            for (int k = 1; k < n; k += 2) {
                double z = az + k * hz;
                sum += 32.0 * func(x, y, z); // Сумма с множителем 32
            }
        }
    }
    return (hx * hy * hz / 27.0) * sum; // Возвращаем результат интегрирования
}



std::complex<double> CadAMath::monteCarlo(std::function<std::complex<double>(double)> f,
                   double a, double b, int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(a, b);
    std::complex<double> sum = 0;
    for (int i = 0; i < N; ++i)
    {
        double x = dist1(gen);
        sum += f(x);
    }
    return sum * (b - a) / double(N);
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

std::complex<double> CadAMath::monteCarlo3(std::function<std::complex<double>(double, double, double)> f,
                   double a1, double b1,
                   double a2, double b2,
                   double a3, double b3,int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(a1, b1);
    std::uniform_real_distribution<> dist2(a2, b2);
    std::uniform_real_distribution<> dist3(a3, b3);
    std::complex<double> sum = 0;
    for (int i = 0; i < N; ++i)
    {
        double x1 = dist1(gen);
        double x2 = dist2(gen);
        double x3 = dist3(gen);
        sum += f(x1, x2, x3);
    }
    return sum * (b1 - a1) * (b2 - a2) * (b3 - a3) / double(N);
}

QVector<std::complex<double>> CadAMath::fft(const QVector<std::complex<double>>& input)
{
    const int N = input.size();

    if (N <= 1)
    {
        return input;
    }

    QVector<std::complex<double>> even(N / 2);
    QVector<std::complex<double>> odd(N / 2);

    for (int i = 0; i < N / 2; ++i)
    {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }

    QVector<std::complex<double>> evenResult = fft(even);
    QVector<std::complex<double>> oddResult = fft(odd);

    QVector<std::complex<double>> result(N);

    for (int k = 0; k < N / 2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * oddResult[k];
        result[k] = evenResult[k] + t;
        result[k + N / 2] = evenResult[k] - t;
    }

    return result;
}

QVector<std::complex<double>> CadAMath::ifft(const QVector<std::complex<double>>& input)
{

    const int N = input.size();

    if (N <= 1)
    {
        return input;
    }

    QVector<std::complex<double>> even(N / 2);
    QVector<std::complex<double>> odd(N / 2);

    for (int i = 0; i < N / 2; ++i)
    {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }

    QVector<std::complex<double>> result(N);

    QVector<std::complex<double>> evenResult = ifft(even);
    QVector<std::complex<double>> oddResult = ifft(odd);

    for (int k = 0; k < N / 2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * oddResult[k];
        result[k] = evenResult[k] + t;
        result[k + N / 2] = evenResult[k] - t;
    }

    return result;
}

Complex CadAMath::rectInt2(std::function<Complex (double, double)> f, double x1, double x2, double y1, double y2, int N)
{
    int numPointsX = N, numPointsY = N;
    double dx = (x2 - x1) / numPointsX;
    double dy = (y2 - y1) / numPointsY;

    Complex integral = 0.0;

    for (int i = 0; i < numPointsX; ++i) {
        for (int j = 0; j < numPointsY; ++j) {
            double x = x1 + (i + 0.5) * dx;
            double y = y1 + (j + 0.5) * dy;
            integral += f(x, y) * dx * dy;
        }
    }

    return integral;
}

Complex CadAMath::trapez2(std::function<Complex (double, double)> f, double x1, double x2, double y1, double y2, int N)
{
        int numPointsX = N, numPointsY = N;
        double dx = (x2 - x1) / numPointsX;
        double dy = (y2 - y1) / numPointsY;

        Complex integral = 0.0;

        for (int i = 0; i < numPointsX; ++i) {
            for (int j = 0; j < numPointsY; ++j) {
                double x1 = x1 + i * dx;
                double x2 = x1 + (i + 1) * dx;
                double y1 = y1 + j * dy;
                double y2 = y1 + (j + 1) * dy;

                integral += (f(x1, y1) + f(x2, y1) + f(x1, y2) + f(x2, y2)) * 0.25 * dx * dy;
            }
        }

        return integral;
}

int CadAMath::maxOfThree(double a, double b, double c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

double CadAMath::floorToPowerOfTen(double number)
{
    if (number == 0.0) {
            return 0.0;
        }

        int exponent = static_cast<int>(floor(log10(fabs(number))));
        double factor = pow(10, exponent);

        return copysign(factor, number);
}

double CadAMath::ceilToPowerOfTen(double number)
{
    if (number == 0.0) {
        return 0.0;
    }

    int exponent = static_cast<int>(ceil(log10(fabs(number))));
    double factor = pow(10, exponent);

    return copysign(factor, number);
}
