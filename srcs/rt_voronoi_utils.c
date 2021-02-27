
#include <rt.h>

/*
 ** return a or b depends on f
 ** a + f * (b - a)
*/

t_vec	rt_lerp(t_vec a, t_vec b, float f)
{
	return (vec_add(a, vec_pro_k(vec(b.x - a.x, b.y - a.y, b.y - a.y), f)));
}

double	rt_frac(double value)
{
	return (value - floor(value));
}

float	rt_step(float a, float x)
{
	return (x >= a);
}

float	rt_smoothstep(float a, float b, float x)
{
	float t;

	if (b != a)
		t = ft_clamping((x - a) / (b - a));
	else
		t = ft_clamping(a);
	return (t * t * (3.0 - 2.0 * t));
}

t_vec  vec_floor(t_vec v)
{ 
    return(vec(floor(v.x), floor(v.y), floor(v.z)));
}