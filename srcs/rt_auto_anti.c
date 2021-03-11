/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_anti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:28:13 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/11 12:31:01 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			progress_fill(t_rt *rt)
{
	int i;
	int j;

	(RS->select == RS->aa) ? (RS->progress = 12) : 0;
	i = -1;
	while (++i < ((double)IMG_WIDTH / (double)12) * (double)(RS->progress))
	{
		j = -1;
		while (++j < 5)
			rt_mlx_putpixel(rt, i, IMG_HEIGHT - 5 + j, 0xFF0000);
	}
}

t_vec			infinite_pixels(t_thread *t, t_vec cr, int select, t_vec cl)
{
	t_vec	color;
	t_vec	tmp;
	int		i;

	i = -1;
	color = cl;
	while (++i < select)
	{
		tmp = my_mlx_getpixel(t->RS->data1[i], cr.x, IMG_HEIGHT - cr.y);
		color = vec_add(color, tmp);
	}
	return (color);
}

void			init_tab(t_vec *tab)
{
	tab[0] = vec(0, 0, 0);
	tab[1] = vec(0, 1, 0);
	tab[2] = vec(1, 0, 0);
	tab[3] = vec(1, 1, 0);
	tab[4] = vec(0, 2, 0);
	tab[5] = vec(2, 0, 0);
	tab[6] = vec(2, 2, 0);
	tab[7] = vec(1, 2, 0);
	tab[8] = vec(2, 1, 0);
}

t_vec			anti_aa(t_thread *t, double col, double row, int select)
{
	t_vec		tab[9];
	t_vec		color;
	t_vec		colo;
	t_ray		r;
	double		anti_a;

	init_tab(tab);
	anti_a = sqrt(t->RS->max_anti_a);
	colo = vec3(0.0);
	if (t->rt->scene->stereo)
		color = rt_stereoscopy(t, col, row, select);
	else
	{
		r = rt_get_ray(&t->RS->cam,\
			(double)((col + ((tab[select].x + 0.5) / anti_a)) / IMG_WIDTH),\
			(double)((row + ((tab[select].y + 0.5) / anti_a)) / IMG_HEIGHT));
		color = rt_raytracer(t, r, MAX_DEPTH);
	}
	colo = infinite_pixels(t, (t_vec){col, row, 0}, select, color);
	my_mlx_putpixel(t->RS->data1[select], col, IMG_HEIGHT - row, color);
	return (colo);
}

t_vec			rt_anti_aliasing(t_thread *t, int col, int row)
{
	t_vec	color;

	color = vec(0, 0, 0);
	color = anti_aa(t, (double)col, (double)row, t->RS->select); //
	color = vec_div_k(color, t->RS->select + 1); //
	return (color);
}
