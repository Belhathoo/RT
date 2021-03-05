

#include <rt.h>

t_vec	rt_rotZ(t_vec vec, double angle)
{
	t_vec	newv;

	newv.x = cos(degtorad(angle)) * vec.x - sin(degtorad(angle)) * vec.y;
	newv.y = cos(degtorad(angle)) * vec.y + sin(degtorad(angle)) * vec.x;
	newv.z = vec.z;
	return (newv);
}

t_vec	rt_rotX(t_vec vec, double angle)
{
	t_vec	newv;

	newv.y = cos(degtorad(angle)) * vec.y - sin(degtorad(angle)) * vec.z;
	newv.z = cos(degtorad(angle)) * vec.z + sin(degtorad(angle)) * vec.y;
	newv.x = vec.x;
	return (newv);
}

t_vec	rt_rotY(t_vec vec, double angle)
{
	t_vec	newv;

	newv.z = cos(degtorad(angle)) * vec.z - sin(degtorad(angle)) * vec.x;
	newv.x = cos(degtorad(angle)) * vec.x + sin(degtorad(angle)) * vec.z;
	newv.y = vec.y;
	return (newv);
}

t_vec			rotation(t_vec dir, t_vec rot)
{
	return (rt_rotY(rt_rotZ(rt_rotX(dir, rot.x), rot.z), rot.y));
}