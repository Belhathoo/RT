
# include <libvec.h>

double      vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec       vec_cross(t_vec a, t_vec b)
{
	return (vec((a.y * b.z - a.z * b.y), -(a.x * b.z - a.z * b.x),
				(a.x * b.y - a.y * b.x)));
}

double      vec_length(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double      vec_lengthsquared(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}