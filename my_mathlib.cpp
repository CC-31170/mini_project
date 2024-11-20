#include <math.h>

double sgn(double t)
{
	if (t > 0)
		return 1.0;
	else if (t < 0)
		return -1.0;
	else
		return 0.0;
}
