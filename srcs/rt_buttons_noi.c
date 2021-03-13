
# include <rt.h>

t_button	*circles_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("circles_button");
	ret->pos = vec_add(rt->btns_noi, vec(0, 60, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/circles.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/circles.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}
t_button	*voronoi1_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("voronoi1_button");
	ret->pos = vec_add(rt->btns_noi, vec(0, 120, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi1.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi1.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}
t_button	*voronoi2_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("voronoi2_button");
	ret->pos = vec_add(rt->btns_noi, vec(0, 180, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi2.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi2.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}
t_button	*voronoi3_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("voronoi3_button");
	ret->pos = vec_add(rt->btns_noi, vec(0, 240, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi3.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/voronoi3.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}
