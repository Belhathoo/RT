
#include<rt.h>

#include<rt.h>

int		rt_add_noise(char *val, t_rt *rt) //parser
{
	if (!ft_strcmp(val, "damier"))
		return (0);
	else if (!ft_strcmp(val, "circles"))
		return (1);
	else if (!ft_strcmp(val, "voronoi1"))
		return (2);
	else if (!ft_strcmp(val, "voronoi2"))
	   	return (3);
	else if (!ft_strcmp(val, "voronoi3"))
	   	return (4);
	else
		rt_exit(rt, "noise: Unknown type!", EXIT_FAILURE);
}

t_vec  rt_torus_noise(t_hit *rec)
{
	int i;
	int j;
    int oddity;

	i = (int)(10 * rec->u);
	j = (int)(10 * rec->v);
	if ((i & 0x01) == (j & 0x01))
		oddity = 1;
	else
		oddity = 0;
	if ((((10 * rec->u - i) < 0.2) && oddity) || ((10 * rec->v - j) < 0.2))
	  return (vec(0, 0, 0));
	else 
	  return (vec(1, 1, 1));
}