#ifndef PID_H
#define PID_H
#include "GaussianQuad.h"
class pid
{
private:
	double P;
	double I;
	double D;
	double e;
	double integral;
	double prevE[IN];
	double times[IN];
	GaussianQuad gq;
public:
	pid(double,double,double);
	double update(double, double, double);	
};

#endif
