#include "pid.h"

pid::pid(double p, double i, double d)
{
	P = p;
	I = i;
	D = d;
}
double pid::update(double target, double currVal, double dt)
{
	double e = target - currVal;
	for(int i = 0; i < IN-1; i ++)
	{
		prevE[i] = prevE[i+1];
		times[i] = times[i+1];
	}
	times[IN-1] += dt;
	prevE[IN-1] = e;
	gq.calcPolynomial(times,prevE);
	integral += gq.eval(times[IN-2], times[IN-1]);
	double deriv = (e - prevE[IN-2])/dt;
	return P*e + I*integral + D*deriv;
}
