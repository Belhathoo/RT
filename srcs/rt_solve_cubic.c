
#include <rt.h>

static int	rt_case_1(double s[2], double *q)
{
	int			num;
	double	u;

	if (rt_is_zero(*q))
	{
		s[0] = 0;
		num = 1;
	}
	else
	{
		u = cbrt(-(*q));
		s[0] = 2.0 * u;
		s[1] = -u;
		num = 2;
	}
	return (num);
}

static int	rt_case_2(double s[3], double *q, double *p,
  double *cb_p)
{
	double	phi;
	double	t;

	phi = 1.0 / 3.0 * acos(-(*q) / sqrt(-(*cb_p)));
	t = 2.0 * sqrt(-(*p));
	s[0] = t * cos(phi);
	s[1] = -t * cos(phi + M_PI / 3.0);
	s[2] = -t * cos(phi - M_PI / 3.0);
	return (3);
}

static int	rt_case_3(double s[3], double *q, double *d)
{
	double	sqrt_d;
	double	u;
	double	v;

	sqrt_d = sqrt(*d);
	u = cbrt(sqrt_d - (*q));
	v = - cbrt(sqrt_d + (*q));
	s[0] = u + v;
	return (1);
}

int			rt_solve_cubic(double w[4], double s[3])
{
	int			i;
	int			num;
	double	sub;
	t_cubic		c;

	c.a = w[2] / w[3];
	c.b = w[1] / w[3];
	c.c = w[0] / w[3];
	c.sq_a = c.a * c.a;
	c.p = 1.0 / 3.0 * (-1.0 / 3.0 * c.sq_a + c.b);
	c.q = 1.0 / 2.0 * (2.0 / 27.0 * c.a * c.sq_a - 1.0 / 3.0 * c.a * c.b + c.c);
	c.cb_p = c.p * c.p * c.p;
	c.d = c.q * c.q + c.cb_p;
	if (rt_is_zero(c.d))
		num = rt_case_1(s, &c.q);
	else if (c.d < 0)
		num = rt_case_2(s, &c.q, &c.p, &c.cb_p);
	else
		num = rt_case_3(s, &c.q, &c.d);
	sub = 1.0 / 3.0 * c.a;
	i = -1;
	while (++i < num)
		s[i] -= sub;
	return (num);
}
