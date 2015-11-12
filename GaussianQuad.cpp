#include "GaussianQuad.h"

GaussianQuad::GaussianQuad()
{
	x[0] = 0;
	w[0] = 0.5688888888888888888888888888888888888888888888888888;
	x[1] = 0.5384693101056830910363144207002088049672866069055599;
	w[1] = 0.4786286704993664680412915148356381929122955533431415;
	x[2] = -0.5384693101056830910363144207002088049672866069055599;
	w[2] = 0.4786286704993664680412915148356381929122955533431415;
	x[3] = 0.9061798459386639927976268782993929651256519107625308;
	w[3] = 0.2369268850561890875142640407199173626432600022124140;
	x[4] = -0.9061798459386639927976268782993929651256519107625308;
	w[4] = 0.2369268850561890875142640407199173626432600022124140;
}
double GaussianQuad::eval(double a, double b)
{
	double l = 0;
	double r = 0;
	double m = (a+b)/2.0;
	for(int i = 0; i < GN; i ++)
	{
		l += w[i]*(evalInt((m-a)/2.0*x[i] + (a+m)/2.0));
		r += w[i]*(evalInt((b-m)/2.0*x[i] + (b+m)/2.0));
	}
	return (m-a)/2.0*l+(b-m)/2.0*r;
}
void GaussianQuad::calcPolynomial(double *x, double *f)
{
        xj = x[IN-2];
        for(int i = 0; i < IN-1; i ++)
        {
                h[i] = x[i+1] - x[i];
                a[i] = f[i];
        }
        a[IN-1] = f[IN-1];
        for(int i = 1; i < IN-1; i ++)
                al[i] = 3.0/h[i]*(a[i+1]-a[i])-3.0/h[i-1]*(a[i]-a[i-1]);
        l[0] = 1.0;
        m[0] = 0.0;
        z[0] = 0.0;
        for(int i = 1; i < IN-1; i ++)
        {
                l[i] = 2.0*(x[i+1]-x[i-1])-h[i-1]*m[i-1];
                m[i] = h[i]/l[i];
                z[i] = (al[i] - h[i-1]*z[i-1])/l[i];
        }
        l[IN-1] = 1.0;
        z[IN-1] = 0.0;
        c[IN-1] = 0.0;
        for(int j = IN-1; j >= 0; j --)
        {
                c[j] = z[j] - m[j]*c[j+1];
                b[j] = (a[j+1]-a[j])/h[j] - h[j]*(c[j+1]+2.0*c[j])/3.0;
                d[j] = (c[j+1] - c[j])/(3.0*h[j]);
        } 
}

double GaussianQuad::evalInt(double t)
{
        //Returns S_j-1(x) as this function will only be used for Adams-Bashforth Method
        return a[IN-2] + (t-xj)*b[IN-2] + (t-xj)*(t-xj)*c[IN-2] + (t-xj)*(t-xj)*(t-xj)*d[IN-2];
}
