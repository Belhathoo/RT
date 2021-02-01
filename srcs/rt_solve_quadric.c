
#include <rt.h>

int				rt_is_zero(double delta)
{
	return ((delta > -1e-9 && delta < 1e-9));
}

int				rt_solve_quadric(double w[3], double s[2])
{
	 double	p;
	 double	q;
	 double	d;

	p = w[1] / (2.0 * w[2]);
	q = w[0] / w[2];
	d = p * p - q;
	if (rt_is_zero(d))
	{
		s[0] = -p;
		return (1);
	}
	else if (d < 0)
		return (0);
	else
	{
		d = sqrt(d);
		s[0] = d - p;
		s[1] = -d - p;
		return (2);
	}
}