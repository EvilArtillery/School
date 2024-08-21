#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double func1(double x) {
    return exp(x) - 6*x - 3;
}
double func2(double x) {
    return 3*x + 4;
}
double func3(double x) {
    return sqrt(x+3) - 1.;
}

double method1 (double a, double b, double error, double (*func)(double)) { //метод деления отрезка пополам(бисекции)
    double c;
    if (fabs(func(a))<(1e-14 + error)) return a;
    if (fabs(func(b))<(1e-14 + error)) return b;
    if(func(a)*func(b)>1e-14) return -1;
    c = (a + b)*0.5;
    if(func(a)*func(c)<0) b = c;
    else a = c;
    return method1(a,b,error,func);
    }

double method2(double a, double b, double error, double (*func)(double)) { //метод секущих
    if (fabs(func(a))<(1e-14 + error)) return a;
    if (fabs(func(b))<(1e-14 + error)) return b;
    if(fabs(b-a) < error) return a;
    double c,d;
    c = a - (func(a)*(b-a)/(func(b)-func(a)));
    a = b; b = c;
    return method2(a,b,error,func);
    }

int main() {
    int n;
    double error,a,b;
    double answer;
    double (*func)(double);
    printf("Список функций:\n1. exp(x) - 6x - 3\n2. 3*x + 4\n3. sqrt(x+3) - 1\n");
    if (!(scanf("%d", &n))) {
        return -2;
    }
    if (n == 1) {
        func = func1;
    }
    else if (n == 2) {
        func = func2;
    }
    else if (n == 3) {
        func = func3;
    }
    else {
        return 2;
    }
    printf("Список методов:\n1. Метод бисекции\n2. Метод секущих\n");
    if (!(scanf("%d", &n))){
        return -1;
    }
    printf("Погрешность:\n");
    if (!(scanf("%lf", &error))) {
            return -1;
    }
    printf("Интервал:\n");
    if (!(scanf("%lf %lf", &a, &b))) {
        return -1;
    }
    if (func(a)*func(b) > 0) {
        printf("error func(a)*func(b) > 0\n");
        return -1;
    }
    if (n == 1) {
        answer = method1(a, b, error, *func);
    } else if (n == 2) {
        answer = method2(a, b, error, *func);
    } else {
        return 3;
    }
    printf("%lf\n", answer);
    return 0;
}
