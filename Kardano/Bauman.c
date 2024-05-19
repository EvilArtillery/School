#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct com{
    double x;
    double y;
}com;

double kv(com a){
	return a.x * a.x + a.y * a.y;
}

com del(com a, com b){
	com c; double r;
	b.y = -1 * b.y;
	r = kv(b);
	c.x = (a.x * b.x - a.y * b.y) / r;
	c.y = (a.y * b.x + b.y * a.x) / r;
	return c;
}

com deln(com a, double b){
	com c;
	c.x = a.x / b;
	c.y = a.y / b;
	return c;
}

com umn(com a, com b){
    com c;
	c.x = a.x * b.x - a.y * b.y;
	c.y = a.x * b.y + a.y * b.x;
	return c;   
}

com umnn(com a, double b){
	com c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

com min(com a, com b){
	com c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

com plus(com a, com b){
    com c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

double arg(com a){
	double r = sqrt(kv(a));
	if (a.y < 0) return -acos(a.x / r);
	return acos(a.x / r);
}

com kor2(com a){
	double r = sqrt(kv(a));
	if (r < 1e-14){
		a.x = 0.;
		a.y = 0.;
		return a;
	}
	r = sqrt(r);
	double z = arg(a) / 2.;
	a.x = r * cos(z);
	a.y = r * sin(z);
	return a;
}

com kor3(com a){
	double r = sqrt(kv(a));
	if (r < 1e-14){
		a.x = 0.;
		a.y = 0.;
		return a;
	}
	r = cbrt(r);
	double z = arg(a) / 3.;
	a.x = r * cos(z);
	a.y = r * sin(z);
	return a;
}

int printuf(com a){
    printf("%lf", a.x);
    printf("+i*%lf", a.y);
    printf("\n");
    return 1;
}

int main(void){
    com a,b,c,d,p,q,x1,x2,x3;
    printf("Hello World\n");
    printf("Решение уравнений типа ax^3+bx^2+cx+d=0\n");
    printf("Введите a.real \n");
    if (!scanf("%lf", &a.x))return 123;
    printf("Введите a.imag \n");
    if (!scanf("%lf", &a.y))return 123;
    if (a.x < 1e-14 && a.y < 1e-14){
		printf("Коэффициент a = 0\n");
		return -1;
	}
    printf("Введите b.real\n");
    if (!scanf("%lf", &b.x))return 123;
    printf("Введите b.imag\n");
    if (!scanf("%lf", &b.y))return 123;
    printf("Введите c.real\n");
    if (!scanf("%lf", &c.x))return 123;
    printf("Введите c.imag\n");
    if (!scanf("%lf", &c.y))return 123;
    printf("Введите d.real\n");
    if (!scanf("%lf", &d.x))return 123;
    printf("Введите d.imag\n");
    if (!scanf("%lf", &d.y))return 123;
    p = del(min(umnn(umn(a, c), 3.), umn(b, b)), umnn(umn(a, a), 3.));
    q = del(plus(min(umnn(umn(b, umn(b, b)), 2.), umnn(umn(a, umn(b, c)), 9.)), umnn(umn(d, umn(a, a)), 27.)), umnn(umn(a, umn(a, a)), 27.));
    com z = plus(deln(umn(q, q), 4.), deln(umn(p, umn(p, p)), 27.));
	z = kor2(z);
	com w;
	w = plus(umnn(z, -1), deln(q, -2.));
	z = plus(z, deln(q, -2.));
	com l = kor3(z);
	com k;
	com eps1;
	com eps2;
	eps1.x = cos(2. * M_PI / 3.);
	eps1.y = sin(2. * M_PI / 3.);
	eps2.x = cos(4. * M_PI / 3.);
	eps2.y = sin(4. * M_PI / 3.);
	if (!(l.x < 1e-14 && l.y < 1e-14)){
		k = del(umnn(p, -1.), umnn(l, 3.));
		x1 = plus(l, k);
		x2 = plus(umn(l, eps1), umn(k, eps2));
		x3 = plus(umn(l, eps2), umn(k, eps1));
	}
	else{
		k = kor3(w);
		x1 = k;
		x2 = umn(k, eps1);
		x3 = umn(k, eps2);
	}
	x1 = plus(x1, deln(b, -3));
	x2 = plus(x2, deln(b, -3));
	x3 = plus(x3, deln(b, -3));
	printuf(x1); printuf(x2); printuf(x3);
}
