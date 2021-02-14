/* ************************************************************************** */

#include <rt.h>

double      ffmax(double a, double b)
{
	return(a > b ? a : b);
}

t_vec		ft_reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_pro_k(vec_pro_k(n, 2), vec_dot(v, n))));
}

t_vec		ft_diffuse(t_thread *th, t_light *l, t_vec lo, double f_att)
{
	double	d;
	t_vec	diff;

	d = th->rec.curr_obj->mat.kd * l->intensity;
	d *= ffmax(0.0, vec_dot(vec_unit(lo), th->rec.n));
	diff = vec_prod(th->rec.col, l->col);
	diff = vec_pro_k(diff, d * f_att);
	return (diff);
}

t_vec		ft_specular(t_thread *th, t_light *l, t_vec lo, double f_att)
{
	t_object	*o;
	double		s;
	t_vec		spec;
	t_vec		refl;

	o = th->rec.curr_obj;
	refl = vec_unit((ft_reflect(vec_unit(lo), th->rec.n)));
	s = pow(ffmax(0.0, vec_dot(refl,
					vec_unit(th->rec.ray->dir))), o->mat.shininess);
	s *= o->mat.ks * l->intensity;
	spec = vec_add(th->rec.col, l->col);
	spec = vec_pro_k(spec, s * f_att);
	return (spec);
}

void		ft_phong(t_thread *th, t_light *l, t_vec lo, t_vec *d_s)
{
	double f_att;

	f_att = ft_clamping(1 /
			((vec_length(lo) + vec_length(th->rec.ray->dir)) * 0.02));
	d_s[0] = vec_add(d_s[0], ft_diffuse(th, l, lo, f_att));
	d_s[1] = vec_add(d_s[1], ft_specular(th, l, lo, f_att));
}

int		rt_lighting(t_thread *th, t_light *l)
{
	t_vec		l_vec;
	t_vec		d_s[2];
	int			shade;

	shade = 0;
	d_s[0] = vec(0.0, 0.0, 0.0);
	d_s[1] = vec(0.0, 0.0, 0.0);
double f_att = 0;

	ft_ambient(l, th, &th->rec.col);
	while (l != NULL)
	{
		l_vec = vec_sub(l->pos, th->rec.p);
		if ((shade = ft_shading(th, l_vec)) == 0)
		{

			f_att = ft_clamping(1 /
					((vec_length(l_vec) + vec_length(th->rec.ray->dir)) * 0.02));
			d_s[0] = vec_add(d_s[0], ft_diffuse(th, l, l_vec, f_att));
			d_s[1] = vec_add(d_s[1], ft_specular(th, l, l_vec, f_att));
		}
		// ft_phong(th, l, l_vec, d_s);
		l = l->next;
	}
	th->rec.col = vec_add(th->rec.col, vec_add(d_s[0], d_s[1]));
	return (0);
}
