/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:55:11 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/28 17:00:45 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>

void		ft_select_obj(t_rt *rt, int col, int row)
{
	t_ray		r;
	t_hit   rec;

	r = rt_get_ray(&rt->scene->cam, (double)(col + 0.5) / IMG_WIDTH,
			(double)(row + 0.5) / IMG_HEIGHT);
	if (rt_hit(rt->scene, &r, &rec, MAX))
		rt->scene->sl_obj = rec.curr_obj;
	else
		rt->scene->sl_obj = NULL;
}
# define FRAME 40
# define MENU_BAR 180
# define COND_SLCT1(x) (x > FRAME && x < IMG_WIDTH + FRAME)
# define COND_SLCT2(y) (y > MENU_BAR && y < IMG_HEIGHT + MENU_BAR)
# define COND_SELECT(x, y) (COND_SLCT1(x) && COND_SLCT2(y))

int				rt_mouse(int button, int x, int y, t_rt *rt)
{


	if (button == 1 && COND_SELECT(x, y))
	{
		ft_select_obj(rt, x - FRAME, (int)IMG_HEIGHT - (y - MENU_BAR));
		if (rt->scene->sl_obj != NULL)
		{
			printf("- selected_object: %s -\n", rt->scene->sl_obj->name);
			// p->light_slct = 0;
			// p->cam_slct = 0;
		}
	}
	if (button == 2)
		rt->scene->sl_obj = NULL;
	return (0);
}

t_vec	ft_rot_vec(t_vec a, t_vec b, double t)
{
	t_vec	res;

	res.x = (b.x * b.x + (1.0 - b.x * b.x) * cos(t)) * a.x + (b.x * b.y
			* (1.0 - cos(t)) - b.z * sin(t)) * a.y + (b.x * b.z
			* (1.0 - cos(t)) + b.y * sin(t)) * a.z;
	res.y = (b.x * b.y * (1.0 - cos(t)) + b.z * sin(t)) * a.x
		+ (b.y * b.y + (1.0 - b.y * b.y) * cos(t)) * a.y
		+ (b.y * b.z * (1.0 - cos(t)) - b.x * sin(t)) * a.z;
	res.z = (b.x * b.z * (1.0 - cos(t)) - b.y * sin(t)) * a.x
		+ (b.y * b.z * (1.0 - cos(t)) + b.x * sin(t)) * a.y
		+ (b.z * b.z + (1.0 - b.z * b.z) * cos(t)) * a.z;
	return (res);
}

void      rt_redraw(t_rt *rt)
{
	rt->scene->progress = 1;
	rt->scene->select = 0;
	//progress_bar(rt);
}

int				rt_keys(int key, t_rt *rt)
{
	t_object  *o;

	if (key == K_ESC)
		rt_close(rt);
	if (rt->scene->sl_obj != NULL && rt->scene->key == 1)
	{
		o = rt->scene->sl_obj;
		if (key == K_NP_PLU) //&& o->pos.z < rt->scene->cam.lookfrom.z)
		{rt->scene->sl_obj->pos.z += 1;rt_redraw(rt);}
		if (key == K_NP_MIN)//&& o->pos.z > -rt->scene->cam.lookfrom.z)
		{rt->scene->sl_obj->pos.z -= 1;rt_redraw(rt);
		}
		if (key == K_UP) //&& o->pos.y < rt->scene->cam.lookfrom.y)
		{rt->scene->sl_obj->pos.y += 1;rt_redraw(rt);}
		if (key == K_DWN)// && o->pos.y > -rt->scene->cam.lookfrom.y)
		{rt->scene->sl_obj->pos.y -= 1;rt_redraw(rt);}
		if (key == K_LFT )// && o->pos.x > - rt->scene->cam.lookfrom.x)
		{rt->scene->sl_obj->pos.x -= 1;rt_redraw(rt);}
		if (key == K_RGHT )//&& o->pos.x < rt->scene->cam.lookfrom.x)
		{rt->scene->sl_obj->pos.x += 1;rt_redraw(rt);}
	}
	if (key == K_NP_PLU || key == K_NP_MIN || key == K_UP || key == K_DWN || key == K_LFT || key == K_RGHT)
	{
		rt->scene->key2 = 1;
	}
	if (key == K_A)
	{
		rt->scene->sl_obj = NULL;
		rt->scene->key = (rt->scene->key + 1) % 2;
		rt->scene->key2 = 1;
	}
	return (0);
}
