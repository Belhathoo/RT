
#include <rt.h>

t_button	*save_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->pos = vec(1270, 752, 0);
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/save0.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/save_no.xpm", &ret->w, &ret->h);
	if (!ret->img || !ret->deflt)
		rt_exit(rt, "", "buttons : img unfound", EXIT_FAILURE);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}

t_button	*mvmnt_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->pos = vec_add(rt->btns_up, vec(15, 10, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/stop.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/play.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y) ;
	return (ret);
}

t_button	*cam_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->pos = vec_add(rt->btns_up, vec(25, 140, 0));
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/c_off0.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/c_on.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}


t_button	*light_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->pos = vec_add(rt->btns_up, vec(17, 250, 0));
	if (rt->scene->light)
		ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/lon.xpm", &ret->w, &ret->h);
	else
		ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/loff1.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/loff1.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}


t_button	*damier_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->pos = rt->btns_noi;
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/damier.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/damier.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}
