/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:56:46 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/06 19:11:26 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>



void	swap_void(void *dflt, void *img, size_t n)
{
	void *p;

	p = malloc(n);
	ft_memcpy(p, dflt, n);
	ft_memcpy(dflt, img, n);
	ft_memcpy(img, p, n);
	free(p);
}

void	unselect_btn_id(int	id, t_rt *rt)
{
	ft_memcpy(rt->bt[id]->data, rt->bt[id]->img_data, sizeof(int) * rt->bt[id]->w * rt->bt[id]->h);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->bt[id]->data_data, (int)rt->bt[id]->pos.x, (int)rt->bt[id]->pos.y);	
}

void	select_btn_id(int	id, t_rt *rt)
{
	ft_memcpy(rt->bt[id]->data, rt->bt[id]->deflt_data, sizeof(int) * rt->bt[id]->w * rt->bt[id]->h);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->bt[id]->data_data, (int)rt->bt[id]->pos.x, (int)rt->bt[id]->pos.y);	
}

void	swap_button_by_id(int	id, t_rt *rt)
{
	swap_void(rt->bt[id]->deflt_data, rt->bt[id]->img_data,
	sizeof(int) * rt->bt[id]->w * rt->bt[id]->h);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->bt[id]->deflt, (int)rt->bt[id]->pos.x, (int)rt->bt[id]->pos.y);	
}

t_button	*save_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("save");
	ret->pos = vec(10, 10, 0);
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/save.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/save_no.xpm", &ret->w, &ret->h);
	ret->data_data = mlx_xpm_file_to_image(rt->mlx ,"buttons/save_no.xpm", &ret->w, &ret->h);
	if (!ret->img || !ret->deflt || !ret->data_data)
	{
		rt_exit(rt, "buttons : img unfound", EXIT_FAILURE);
	}
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	ret->data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}

t_button	*mvmnt_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("A_button");
	ret->pos = vec(100, 10, 0);
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/save.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/save_no.xpm", &ret->w, &ret->h);
	ret->data_data = mlx_xpm_file_to_image(rt->mlx ,"buttons/save_no.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	ret->data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}

t_button	*cam_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("cam_button");
	ret->pos = vec(200, 10, 0);
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/no_cam_btn.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/cam_btn.xpm", &ret->w, &ret->h);
	ret->data_data = mlx_xpm_file_to_image(rt->mlx ,"buttons/cam_btn.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	ret->data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}

t_button	*damier_button(t_rt *rt)
{
	t_button *ret;

	ret = (t_button *)malloc(sizeof(t_button));
	ret->name = ft_strdup("cam_button");
	ret->pos = vec(500, 10, 0);
	ret->deflt = mlx_xpm_file_to_image(rt->mlx ,"buttons/damier.xpm", &ret->w, &ret->h);
	ret->img = mlx_xpm_file_to_image(rt->mlx ,"buttons/damier.xpm", &ret->w, &ret->h);
	// ret->data_data = mlx_xpm_file_to_image(rt->mlx ,"buttons/damier.xpm", &ret->w, &ret->h);
	ret->deflt_data = (int*)mlx_get_data_addr(ret->deflt, &ret->bpp, &ret->size, &ret->endian);
	ret->img_data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	ret->data = (int*)mlx_get_data_addr(ret->img, &ret->bpp, &ret->size, &ret->endian);
	mlx_put_image_to_window(rt->mlx, rt->win, ret->deflt, (int)ret->pos.x, (int)ret->pos.y);
	return (ret);
}

void	create_buttons(int	size, t_rt *rt)
{
	t_button **b;

	b = (t_button **)malloc(size * sizeof(t_button *));
	b[0] = save_button(rt);
	b[1] = mvmnt_button(rt);
	b[2] = cam_button(rt);
	b[3] = damier_button(rt);
	rt->bt = b;
	rt->size_bt = size;
}

void	select_button(int x, int y, t_rt *rt)
{
	int i = 0;
	while (i < rt->size_bt)
	{
		if (((int)rt->bt[i]->pos.x <= x && x <= (int)rt->bt[i]->pos.x + rt->bt[i]->w) && ((int)rt->bt[i]->pos.y <= y && y <= (int)rt->bt[i]->pos.y + rt->bt[i]->h))
		{
			swap_void(rt->bt[i]->deflt_data, rt->bt[i]->img_data, sizeof(int) * rt->bt[i]->w * rt->bt[i]->h);
			mlx_put_image_to_window(rt->mlx, rt->win, rt->bt[i]->deflt, (int)rt->bt[i]->pos.x, (int)rt->bt[i]->pos.y);
		}
		i++;
	}
}



int		get_selected_button(int x, int y, t_rt *rt)
{
		int i = 0;
	while (i < rt->size_bt)
	{
		if (((int)rt->bt[i]->pos.x <= x && x <= (int)rt->bt[i]->pos.x + rt->bt[i]->w) && ((int)rt->bt[i]->pos.y <= y && y <= (int)rt->bt[i]->pos.y + rt->bt[i]->h))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}