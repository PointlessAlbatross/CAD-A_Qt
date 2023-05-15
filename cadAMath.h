#ifndef CADAMATH_H
#define CADAMATH_H
#include <functional>
#include <ccomplex>
#include <cmath>
#include <QVector>
#include <QRandomGenerator>
#include <QtMath>
#include <random>


class CadAMath
{
public:
    CadAMath();


    std::complex<double> monteCarlo(std::function<std::complex<double>(double)> f,
                       double a, double b, int N);
    std::complex<double> monteCarlo2(std::function<std::complex<double>(double, double)> f,
                       double a1, double b1,
                       double a2, double b2,int N);
    std::complex<double> monteCarlo3(std::function<std::complex<double>(double, double, double)> f,
                       double a1, double b1,
                       double a2, double b2,
                       double a3, double b3,int N);

    std::complex<double> simpson(const std::function<std::complex<double>(double)>& func, double a, double b, int n);
    std::complex<double> simpson2(const std::function<std::complex<double>(double, double)>& func, double ax, double bx, double ay, double by, int n);
    std::complex<double> simpson3(const std::function<std::complex<double>(double, double, double)>& func, double ax, double bx, double ay, double by, double az, double bz, int n);
    QVector<std::complex<double>> fft(const QVector<std::complex<double>>& input);
    QVector<std::complex<double>> ifft(const QVector<std::complex<double>>& input);
    /*
    romberg(std::function<double (double)> f,
                                 double a, double b, int n);
    romberg2(std::function<double (double, double)> f,
                                  double a1, double b1,
                                  double a2, double b2,
                                  int n, int m);
    romberg3(const std::function<double (double, double, double)> f,
                                        double a1, double b1,
                                        double a2, double b2,
                                        double a3, double b3,
                                        int n1, int n2, int n3);
*/
    int maxOfThree(double a, double b, double c);
};

#endif // CADAMATH_H
