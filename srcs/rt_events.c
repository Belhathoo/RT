/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:55:11 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/07 16:56:20 by belhatho         ###   ########.fr       */
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

#define SAVE_BTN 0
#define A_BTN 1
#define CAM_BTN 2
# define L_BTN 3

void      rt_redraw(t_rt *rt)
{
	rt->scene->progress = 1;
	rt->scene->select = 0;
	if(rt->scene->key_cam == 1)
	{
		rt->scene->cam = rt_init_camera(rt->scene->cam.lookfrom,
				rt->scene->cam.lookat, rt->scene->cam.fov);
	}
	else if (rt->scene->sl_obj)
	{
		// rt_get_repere(rt->scene->sl_obj);
		if (rt->scene->sl_obj->compos)
			get_cube_compos(rt->scene->sl_obj);
	}
}
int				rt_mouse(int button, int x, int y, t_rt *rt)
{

	int btn;
	
	if (button == 2)
		rt->scene->sl_obj = NULL;
	if (button == 1 && COND_SELECT(x, y))
	{
		ft_select_obj(rt, x - FRAME, (int)IMG_HEIGHT - (y - MENU_BAR));
		if (rt->scene->sl_obj != NULL)
		{
			ft_putstr("- selected_object: ");
			ft_putendl(rt->scene->sl_obj->name);
		}
	}
	btn = get_selected_button(x, y, rt);
	if (btn != -1)
	{
		if (btn == A_BTN)
		{
			swap_button_by_id(A_BTN , rt);
			rt->scene->sl_obj = NULL;
			rt->scene->key = (rt->scene->key + 1) % 2;
			rt->scene->key_cam = 0;
			rt->scene->key2 = 1;
			rt_redraw(rt);
		}
		if (btn == SAVE_BTN)
		{
			swap_button_by_id(SAVE_BTN , rt);
			image_create(rt);
		}
		// if (btn == L_BTN)
		// {
		// 	swap_button_by_id(L_BTN , rt);
		// 	if (rt->scene->light)
		// 		rt->scene->light = NULL;
		// 	else
		// 		rt->scene->light = &rt->s_light;
		// 	rt_redraw(rt);
		// }


	}
	return (0);
}

void		square_fill(t_rt *data, int color, t_vec pos, t_vec size)
{
	int		i;
	int		j;

	i = (int)pos.x - 1;
	while (++i < (int)size.x)
	{
		j = pos.y - 1;
		while (++j < size.y)
			mlx_pixel_put(data->mlx, data->win, i, j, color);
	}
}

void		square_str(t_rt *data, char *str, t_vec pos, t_vec size)
{
	t_vec	t;

	//t.x = pos.x + (pos.x + size.x) / 2 - (ft_strlen(str) * 12) / 2;
	//t.y = (size.y - pos.y) / 3 + pos.y - 3;
	t.x = pos.x + 10;
	t.y = pos.y + 10;
	mlx_string_put(data->mlx, data->win, t.x, t.y, 0xFFFFFF, str);
}

void		ctrl_name(t_rt *data)
{
	square_fill(data, 0xF9AA33, (t_vec){700, 10}, (t_vec){900, 50});
	ft_putendl(data->scene->sl_obj->name);
	//mlx_string_put(data->mlx, data->win, 750, 20, 0xFFFFFF, data->scene->sl_obj->name);
	square_str(data, data->scene->sl_obj->name , (t_vec){700, 10}, (t_vec){900, 50});
}

int				rt_keys(int key, t_rt *rt)
{
	t_object  *o;
	//rt selt obj in main.c !!!! for linux events
	if (key == K_ESC)
		rt_close(rt);
	if (key  == K_S)
		{
			swap_button_by_id(SAVE_BTN , rt);
			image_create(rt);
		}
	if (rt->scene->key == 0)
	{
		if (key == K_C)
		{
			rt->scene->key_cam = (rt->scene->key_cam + 1) % 2;
			swap_button_by_id(CAM_BTN, rt);
		}
	}
	if (rt->scene->key == 0)
	{
		if (rt->scene->key_cam == 1)
		{
			if (key == K_NP_PLU)
			{rt->scene->cam.lookfrom.z += 1;rt_redraw(rt);}
			if (key == K_NP_MIN)
			{rt->scene->cam.lookfrom.z -= 1;rt_redraw(rt);}
			if (key == K_UP)
			{rt->scene->cam.lookfrom.y += 1;rt_redraw(rt);}
			if (key == K_DWN)
			{rt->scene->cam.lookfrom.y -= 1;rt_redraw(rt);}
			if (key == K_LFT )
			{rt->scene->cam.lookfrom.x -= 1;rt_redraw(rt);}
			if (key == K_RGHT)
			{rt->scene->cam.lookfrom.x += 1;rt_redraw(rt);}
		}
		else if (rt->scene->sl_obj != NULL)
		{
			if (key == K_N && rt->scene->sl_obj)
			{
				ctrl_name(rt);
				ft_putendl(rt->scene->sl_obj->next->name);
				rt->scene->sl_obj = rt->scene->sl_obj->next;
			}
			if (key == K_X)
			{rt->scene->sl_obj->rot = rt_rotX(rt->scene->sl_obj->rot, 5);
			rt->scene->sl_obj->vec2 = rt_rotX(rt->scene->sl_obj->vec2, 5);rt->scene->sl_obj->vec1 = rt_rotX(rt->scene->sl_obj->vec1, 5);
			rt_redraw(rt);}
			if (key == K_Y)
			{rt->scene->sl_obj->rot = rt_rotY(rt->scene->sl_obj->rot, 5);
			rt->scene->sl_obj->vec2 = rt_rotY(rt->scene->sl_obj->vec2, 5);rt->scene->sl_obj->vec1 = rt_rotY(rt->scene->sl_obj->vec1, 5);
			rt_redraw(rt);}
			if (key == K_Z)
			{rt->scene->sl_obj->rot = rt_rotZ(rt->scene->sl_obj->rot, 5);
			rt->scene->sl_obj->vec2 = rt_rotZ(rt->scene->sl_obj->vec2, 5);rt->scene->sl_obj->vec1 = rt_rotZ(rt->scene->sl_obj->vec1, 5);
			rt_redraw(rt);}
			if (key == K_NP_PLU)
			{rt->scene->sl_obj->pos.z += 1;rt_redraw(rt);}
			if (key == K_NP_MIN)
			{rt->scene->sl_obj->pos.z -= 1;rt_redraw(rt);}
			if (key == K_UP)
			{rt->scene->sl_obj->pos.y += 1;rt_redraw(rt);}
			if (key == K_DWN)
			{rt->scene->sl_obj->pos.y -= 1;rt_redraw(rt);}
			if (key == K_LFT )
			{rt->scene->sl_obj->pos.x -= 1;rt_redraw(rt);}
			if (key == K_RGHT)
			{rt->scene->sl_obj->pos.x += 1;rt_redraw(rt);}
		}
	}
	if (rt->scene->key == 0 && (rt->scene->sl_obj != NULL || rt->scene->key_cam == 1) && 
			(key == K_N  || key == K_NP_PLU || key == K_NP_MIN\
			 || key == K_UP|| key == K_DWN || key == K_LFT || key == K_RGHT \
			 || key == K_X || key == K_Y || key == K_Z || (key == K_U)))//x,y,z only for obj no cam!!!
	{
		rt->scene->key2 = 1;
	}
	if (rt->scene->key == 0 && rt->scene->sl_obj != NULL && rt->scene->key_cam == 0)
	{
		if (key == K_U && rt->scene->sl_obj->txt.is_txt == 0)
		{
			if (rt->scene->sl_obj->noi.is_noise == 0)
			{
				rt->scene->sl_obj->noi.is_noise = 1;
				rt->scene->sl_obj->noi.type = 0;
				rt->scene->sl_obj->scale = 12;
				rt_redraw(rt);
			}
			else if (rt->scene->sl_obj->noi.type != 0)
			{
				rt->scene->sl_obj->scale = 14;
				rt->scene->sl_obj->noi.type = 0;
				rt_redraw(rt);
			}
			// else
			// {
			// 	rt->scene->sl_obj->noi.is_noise = 0;
			// 	rt_redraw(rt);
			// }
		}
	}
	if (key == K_A)
		{
			swap_button_by_id(A_BTN , rt);
			(rt->scene->key_cam == 1) ? swap_button_by_id(CAM_BTN, rt) : 0;
			// rt->scene->sl_obj = NULL;
			rt->scene->key = (rt->scene->key + 1) % 2;
			rt->scene->key_cam = 0;
			rt->scene->key2 = 1;
			rt_redraw(rt);
		}

	return (0);
}
