#ifndef CADAMATH_H
#define CADAMATH_H
#include <functional>
#include <cmath>
#include <QVector>
#include <QRandomGenerator>
#include <QtMath>
#include <random>

class cadAMath
{
public:
    cadAMath();

    double monteCarlo(std::function<double(double)> f,
                       double a, double b, int N);
    double monteCarlo2(std::function<double(double, double)> f,
                       double a1, double b1,
                       double a2, double b2,int N);
    double monteCarlo3(std::function<double(double, double, double)> f,
                       double a1, double b1,
                       double a2, double b2,
                       double a3, double b3,int N);
    double monteCarlo4(std::function<double(double, double, double, double)> f,
                       double a1, double b1,
                       double a2, double b2,
                       double a3, double b3,
                       double a4, double b4, int N);
    double monteCarlo5(std::function<double(double, double, double, double, double)> f,
                       double a1, double b1,
                       double a2, double b2,
                       double a3, double b3,
                       double a4, double b4,
                       double a5, double b5, int N);
    double simpson(std::function<double(double)> f, double a, double b, int n);
    double simpson2(std::function<double(double, double)> f, double a1, double b1,
                                                             double a2, double b2,
                                                             int n1, int n2);
    double simpson3(std::function<double(double, double, double)> f, double a1, double b1,
                                                                     double a2, double b2,
                                                                     double a3, double b3,
                                                                     int n1, int n2, int n3);
    double romberg(std::function<double (double)> f,
                                 double a, double b, int n);
    double romberg2(std::function<double (double, double)> f,
                                  double a1, double b1,
                                  double a2, double b2,
                                  int n, int m);
    double romberg3(const std::function<double (double, double, double)> f,
                                        double a1, double b1,
                                        double a2, double b2,
                                        double a3, double b3,
                                        int n1, int n2, int n3);
};

#endif // CADAMATH_H
