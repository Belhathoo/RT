# include <rt.h>

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

void		rt_mlx_putpixel(t_rt *rt, int x, int y, int color)
{
	if (x >= 0 && x < IMG_WIDTH
			&& y >= 0 && y < IMG_HEIGHT)
	{
		rt->data[y * (int)IMG_WIDTH + x] = color;
	}
}
t_vec		vec_ray(t_ray *r, double t)
{
	return (vec_add(r->origin, vec_pro_k(r->dir, t)));
}
