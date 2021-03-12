# include <rt.h>

long double		ft_frac(long double value)
{
	return (value - floor(value));
}

long double		ft_acc(t_vec c[2][2][2], t_vec v, long double acc)
{
	int			i;
	int			j;
	int			k;
	t_vec	weight;
	t_vec	noise;

	noise = vec(v.x * v.x * (3.0 - 2.0 * v.x), v.y * v.y *
	(3.0 - 2.0 * v.y), v.z * v.z * (3.0 - 2.0 * v.z));
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			k = -1;
			while (++k < 2)
			{
				weight = vec(v.x - i, v.y - j, v.z - k);
				acc += (i * noise.x + (1 - i) * (1 - noise.x)) *
				(j * noise.y + (1 - j) * (1 - noise.y)) * (k * noise.z +
				(1 - k) * (1 - noise.z)) * vec_dot(c[i][j][k], weight);
			}
		}
	}
	return (acc);
}

long double		noise(t_rt *rt, t_vec v)
{
	t_vec	c[2][2][2];
	t_vec	acc;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			k = -1;
			while (++k < 2)
			{
				c[i][j][k] = rt->ran[rt->hash[((int)floor(v.x) + i) &
				255] ^ rt->hash[((int)floor(v.y) + j) &
				255] ^ rt->hash[((int)floor(v.z) + k) & 255]];
			}
		}
	}
	acc = vec(ft_frac(v.x), ft_frac(v.y), ft_frac(v.z));
	return (ft_acc(c, acc, 0.0));
}

long double		perlin_noise(t_rt *rt, t_vec v, int depth)
{
	long double		acc;
	long double		weight;
	int				i;

	acc = 0.0;
	weight = 1.0;
	i = -1;
	while (++i < depth)
	{
		acc += weight * noise(rt, v);
		weight *= 0.5;
		v = vec_pro_k(v, 2.0);
	}
	return (fabs((double)acc));
};

t_vec			perlin(t_rt *rt, t_vec v, t_object *obj)
{
	t_vec		dist;
	long double	result;
    
	result = obj->scale * perlin_noise(rt, v, 2);
	dist.x = (long double)obj->col.x * result;
	dist.y = (long double)obj->col.y * result;
	dist.z = (long double)obj->col.z * result;
	return (dist);
}