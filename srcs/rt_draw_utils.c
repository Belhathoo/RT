
# include <rt.h>


t_vec		rt_reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_pro_k(vec_pro_k(n, 2), vec_dot(v, n))));
}

t_ray		rt_ray(t_vec a, t_vec b)
{
	t_ray	r;

	r.origin = a;
	r.dir = b;
	return (r);
}

t_ray rt_get_ray(t_camera *p, double u, double v)
{
	return (rt_ray(p->origin, vec_unit(vec_sub(vec_add(p->lower_left_corner,
							vec_add(vec_pro_k(p->horizontal, u),
								vec_pro_k(p->vertical, v))), p->origin))));
}

void		rt_mlx_putpixel(t_rt *rt, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH
			&& y >= 0 && y < IMG_HEIGHT)
	{
		rt->data[y * (int)IMG_WIDTH + x] = color;
	}
}
