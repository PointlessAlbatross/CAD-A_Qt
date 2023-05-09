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


    double monteCarlo(std::function<double(double)> f,
                       double a, double b, int N);
    std::complex<double> monteCarlo2(std::function<std::complex<double>(double, double)> f,
                       double a1, double b1,
                       double a2, double b2,int N);
    double monteCarlo3(std::function<double(double, double, double)> f,
                       double a1, double b1,
                       double a2, double b2,
                       double a3, double b3,int N);

    double simpson(std::function<double(double)> f, double a, double b, int n);
    double simpson2(std::function<double(double, double)> f, double a1, double b1, double a2, double b2, int n1, int n2);
    double simpson3(std::function<double (double, double, double)> f, double a1, double b1, double a2, double b2, double a3, double b3, int n);
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
};

#endif // CADAMATH_H
