# include <rt.h>

double      ffmax(double a, double b)
{
	return(a > b ? a : b);
}

void		ft_float_swap(double *a, double *b)
{
	double	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void			rt_adjustment(t_vec *c)
{
	c->x = ft_clamping(c->x);
	c->y = ft_clamping(c->y);
	c->z = ft_clamping(c->z);
}

int rt_rgb_to_int(t_vec c)
{
  int r;
  int g;
  int b;

  r = (int)(255.99 * c.x);
  g = (int)(255.99 * c.y);
  b = (int)(255.99 * c.z);
  return (r * 256 * 256 + g * 256 + b);
  //return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

t_vec		rt_int_to_rgb(int x)
{
	t_vec p;
   int i[2];

 p.z = (x % 256);
 i[0] = (x / 256);
 p.y = (i[0] % 256);
 i[1] = i[0] / 256;
 p.x = (i[1] % 256);
 
	//return(vec(x >> 16 & 0xFF, x >> 8 & 0xFF, x & 0xFF));
   return (vec_div_k(p, 256));
}

t_vec		vec_ray(t_ray *r, double t)
{
	return (vec_add(r->origin, vec_pro_k(r->dir, t)));
}

int		is_equal(t_vec a, t_vec b)
{
	return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

 double		radtodeg(double angle)
{
	return ((angle * 180) / M_PI);
}

double		degtorad(double angle)
{
	return ((angle * M_PI) / 180);
}
