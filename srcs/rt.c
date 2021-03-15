/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:40 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/15 15:26:41 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		background(t_rt *rt)
{
	int		i;
	int		j;
	void	*img;
	int		*data;

	i = -1;
	img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	data = (int*)mlx_get_data_addr(img, &rt->bpp, &rt->size, &rt->endian);
	while (++i < WIN_WIDTH)
	{
		j = -1;
		while (++j < WIN_HEIGHT)
			data[j * (int)WIN_WIDTH + i] = 0x00202f;
	}
	// mlx_pixel_put(rt->mlx, rt->win, i, j, 0x00202f);
	mlx_put_image_to_window(rt->mlx, rt->win, img, 0, 0);
}

void		init(t_rt *rt)
{
	rt->win = mlx_new_window(rt->mlx, WIN_WIDTH, WIN_HEIGHT, "RT");
	rt->img = mlx_new_image(rt->mlx, IMG_WIDTH, IMG_HEIGHT);
	rt->data = (int*)mlx_get_data_addr(rt->img\
			, &rt->bpp, &rt->size, &rt->endian);
	background(rt);
	create_buttons(9, rt);
	rt->s_light = rt->scene->light;
}

void		rt_hook(t_rt *rt)
{
	mlx_hook(rt->win, 17, (1L << 17), rt_close, rt);
	mlx_hook(rt->win, 4, (1L << 0), rt_mouse, rt);
	mlx_hook(rt->win, 2, (1L << 0), rt_keys, rt);
}

void		rt_dynamic(char *av, t_rt *rt)
{
	if (!ft_strcmp(av, "milky"))
	{
		rt_parser(rt, "./xscenes/milky_way.xml");
		rt->scene->dyn = 1;
		rt->scene->key = 1;
		rt->scene->key_mvt = 0;
		rt->scene->sl_obj = rt->scene->object;
	}
	else
		rt_parser(rt, av);
}

int			main(int argc, char **argv)
{
	t_rt		rt;

	rt_init(&rt);
	rt.scene = rt_init_scene(&rt);
	rt.mlx = mlx_init();
	if (argc == 2)
	{
		rt_dynamic(argv[1], &rt);
	}
	else
		rt_exit(&rt, 0, ft_strdup("usage: ./rt scene_file"), EXIT_FAILURE);
	init(&rt);
	rt_hook(&rt);
	// rt.scene->sl_obj = rt.scene->object; //
	mlx_loop_hook(rt.mlx, &progress_bar, &rt);
	mlx_loop(rt.mlx);
	return (EXIT_SUCCESS);
}
