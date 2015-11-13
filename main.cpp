#include <iostream>
#include <stdio.h>
#include <math.h>
#include "pid.h"
using namespace std;

double f(double x)
{
	return sin(x)+x*x*x;
}
double I(double x)
{
	return -1.0*cos(x)+x*x*x*x/4.0;
}
int main()
{
	int N = 10;
	GaussianQuad gq;
	double t[N];
	double y[N];
	double dt = 0.0004;
	for(int i = 0; i < N; i ++)
	{
		t[i] = i*dt;
		y[i] = f(t[i]);
	}
	gq.calcPolynomial(t,y);
	printf("%10.20f\n",gq.eval(t[N-2], t[N-1]));
	printf("%10.20f\n",I(t[N-1]) - I(t[N-2]));
	return 0;
}
