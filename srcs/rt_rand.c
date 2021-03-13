#include <rt.h>

double		rt_rand3dto1d(t_vec value, t_vec dot_dir)
{
	t_vec		small_value; 
	double		random;

	small_value = vec(cos(value.x), cos(value.y), cos(value.z));
	random = vec_dot(small_value, dot_dir);
	random = rt_frac(sin(random));
	return (random);
}

double		rt_rand1dto1d(double value, double mutator)
{
	return (rt_frac(sin(value + mutator) * 143758.5453));
}

t_vec		rt_rand1dto3d(double value)
{
	return (vec(
	rt_rand1dto1d(value, 3.9812),
	rt_rand1dto1d(value, 7.1536),
	rt_rand1dto1d(value, 5.7241)));
}

t_vec		rt_rand3dto3d(t_vec value)
{
	return (vec(
	rt_rand3dto1d(value, vec(102.989, 708.233, 370.719)),
	rt_rand3dto1d(value, vec(390.346, 110.135, 830.155)),
	rt_rand3dto1d(value, vec(730.156, 502.235, 90.151))));
}

long double		rand1dto1d(long double value, long double mutator)
{
	long double random;

	random = rt_frac(sin(value + mutator) * 143758.5453);
	return (random);
}
