#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct complex{
	double re, im;
} Complex;

Complex dtc(double a){
	Complex b;
	b.re = a;
	b.im = 0;
	return b;
}
Complex csumm(Complex a, Complex b){
	Complex c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}
Complex cneg(Complex a){
	Complex b;
	b.re = -a.re;
	b.im = -a.im;
	return b;
}
Complex cprod(Complex a, Complex b){
	Complex c;
	c.re = a.re * b.re - (a.im * b.im);
	c.im = a.im * b.re + (a.re * b.im);
	return c;
}
Complex cconj(Complex a){
	Complex b;
	b.re = a.re;
	b.im = 0 - a.im;
	return b;
} 
double cmod(Complex a){
	double b;
	b = a.re * a.re + (a.im * a.im);
	return sqrt(b);
}

double complexModuleSquared(Complex a){
	double b;
	b = a.re * a.re + (a.im * a.im);
	return b;
}

Complex cdiv(Complex a, Complex b){
	Complex c;
	double mb = complexModuleSquared(b);
	c.re = (a.re * b.re + (a.im * b.im))/mb;
	c.im = (b.re * a.im - (a.re * b.im))/mb;
	return c;
}
void cprint(Complex a){
	if(a.im > 1e-14) printf("%.2lf + %.2lfi\n", a.re, a.im);
	else if(fabs(a.im) < 1e-14) printf("%.2lf\n", a.re);
	else if(a.im < -1e-14) printf("%.2lf - %.2lfi\n", a.re, -a.im);
}

double argc(Complex a){
	double ar = 0;
	if(a.im > 1e-14) ar = fabs(atan(a.re/a.im));
	else if(a.im < -(1e-14)) ar = - fabs(atan(a.re/a.im));
	else if(a.re < -(1e-14)) ar = M_PI;
	return ar;
}

//Complex SOLVEr(double p, double q){
//	Complex t;
//	t = dtc(cbrt(-q/2. + sqrt(pow(q/2., 2) + pow(p/3., 3))));
//	return t;
//}

Complex cbrtc(Complex a){
	if(fabs(cmod(a) < 1e-10)) return dtc(0);
	Complex b;
	double r = cmod(a), fi = argc(a);
	fi /= 3.;
	r = cbrt(r);
	b.re = r * cos(fi);
	b.im = r * sin(fi);
	return b;
}

Complex sqrtc(Complex a){
	if(fabs(cmod(a) < 1e-10)) return dtc(0);
	Complex b;
	double r = cmod(a), fi = argc(a);
	fi /= 2.;
	r = sqrt(r);
	b.re = r * cos(fi);
	b.im = r * sin(fi);
	return b;
}

void SOLVEc(Complex p, Complex q, Complex* x0, Complex* x1, Complex* x2){
	Complex a, b, eps;
	eps.im = sqrt(3)/2;
	eps.re = -1/2.;

	if(fabs(cmod(p)) < 1e-14){
		*x0 = cbrtc(cneg(q));
		*x1 = csumm(*x0, eps);
		*x2 = csumm(*x1, eps);
		return;
	}

	//z = (q^2)/4 + (p^3)/27;
	Complex z = csumm(cdiv(cprod(q, q), dtc(4)), cdiv(cprod(cprod(p, p), p), dtc(27)));
	z = sqrtc(z);
	z = csumm(z, cdiv(q, dtc(-2)));

//	b = cbrtc(csumm(cneg(z), cneg(q)));
	a = cbrtc(z);

	b = csumm(cneg(z), cdiv(q, dtc(-2)));
	b = cdiv(cneg(p), cprod(a, dtc(3)));

	*x0 = csumm(a, b);
	*x1 = csumm(cprod(a, eps), cprod(b, cconj(eps)));
	*x2 = csumm(cprod(a, cconj(eps)), cprod(b, eps));
}	

int main(){
	int i;
	Complex a, b, c, d;


	Complex eps;
	eps.re = -1/2.;
	eps.im = sqrt(3)/2.;


	printf("Enter the real part of argument a: ");
	if(! scanf("%lf", &a.re)) return -1;
	printf("Enter the imaginary part of argument a: ");
	if(! scanf("%lf", &a.im)) return -1;
	printf("Enter the real part of argument b: ");
	if(! scanf("%lf", &b.re)) return -1;
	printf("Enter the imaginary part of argument b: ");
	if(! scanf("%lf", &b.im)) return -1;
	printf("Enter the real part of argument c: ");
	if(! scanf("%lf", &c.re)) return -1;
	printf("Enter the imaginary part of argument c: ");
	if(! scanf("%lf", &c.im)) return -1;
	printf("Enter the real part of argument d: ");
	if(! scanf("%lf", &d.re)) return -1;
	printf("Enter the imaginary part of argument d: ");
	if(! scanf("%lf", &d.im)) return -1;
	
	Complex ac = cprod(cprod(a, c), dtc(3));
	Complex tmp = csumm(ac, cneg(cprod(b, b)));
	Complex a2 = cprod(cprod(a, a), dtc(3));
	Complex p = cdiv(tmp, a2);

	Complex b2 = cprod(cprod(cprod(dtc(2), b), b), b);
	Complex abc = cprod(cprod(cprod(dtc(9), a), b), c);
	Complex da2 = cprod(cprod(cprod(dtc(27), d), a), a);
	tmp = csumm(csumm(b2, cneg(abc)), da2);
	Complex a3 = cprod(cprod(cprod(a, a), a), dtc(27));
	Complex q = cdiv(tmp, a3);

	Complex t[3], x[3];
	SOLVEc(p, q, &t[0], &t[1], &t[2]);
	x[0] = csumm(t[0], cdiv(b, cprod(a, dtc(3))));
	
	cprint(x[0]);

	for(i = 0; i < 2; i++){
		x[i+1] = cprod(x[i], eps);
		cprint(x[i+1]);
	}
	return 1;
}
