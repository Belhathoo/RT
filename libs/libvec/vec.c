
#include <libvec.h>


t_vec		vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec		vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec		vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec		vec_unit(t_vec a)
{
	float k;

	if (a.x == 0.0 && a.y == 0.0 && a.z == 0.0)
		return (vec(0, 0, 0));
	k = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (vec_pro_k(a, k));
}