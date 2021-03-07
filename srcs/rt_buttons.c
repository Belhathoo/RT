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


/*

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

int				rt_mouse(int button, int x, int y, t_rt *rt)
{

	//select_button_by_id(0, rt);
	int btn;
	btn = get_selected_button(x, y, rt);
	//if (btn != -1)
	//{
		if (btn == SAVE_BTN)
		{
			swap_button_by_id(SAVE_BTN , rt);
			image_create(rt);
		}
		
	//}
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

void      rt_redraw(t_rt *rt)
{
	rt->scene->progress = 1;
	rt->scene->select = 0;
	//progress_bar(rt);
	if(rt->scene->key_cam == 1)
	{
		rt->scene->cam = rt_init_camera(rt->scene->cam.lookfrom,
		rt->scene->cam.lookat, rt->scene->cam.fov);
	}
	else if (rt->scene->sl_obj)
		{
			rt_get_repere(rt->scene->sl_obj);
			if (rt->scene->sl_obj->compos)
				get_cube_compos(rt->scene->sl_obj);
		}
}

int				rt_keys(int key, t_rt *rt)
{
	t_object  *o;
	//rt selt obj in main.c !!!! for linux events
	if (key == K_ESC)
		rt_close(rt);
	if (rt->scene->key == 0)
	{
		if (key == K_C)
			rt->scene->key_cam = (rt->scene->key_cam + 1) % 2;
	}
			if (key == K_S)
		{
			swap_button_by_id(SAVE_BTN , rt);
			//unselect_btn_id(SAVE_BTN, rt);
			image_create(rt);
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

				ft_putendl(rt->scene->sl_obj->next->name);
				rt->scene->sl_obj = rt->scene->sl_obj->next;
			}
			if (key == K_X)
			{rt->scene->sl_obj->rot = rt_rotX(rt->scene->sl_obj->rot, 5);rt_redraw(rt);}
			if (key == K_Y)
			{rt->scene->sl_obj->rot = rt_rotY(rt->scene->sl_obj->rot, 5);rt_redraw(rt);}
			if (key == K_Z)
			{rt->scene->sl_obj->rot = rt_rotZ(rt->scene->sl_obj->rot, 5);rt_redraw(rt);}
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
			 || key == K_X || key == K_Y || key == K_Z))
	{
		rt->scene->key2 = 1;
	}
	if (key == K_A)
	{
		swap_button_by_id(A_BTN , rt);
		rt->scene->sl_obj = NULL;
		rt->scene->key = (rt->scene->key + 1) % 2;
		rt->scene->key_cam = 0;
		rt->scene->key2 = 1;
		rt_redraw(rt);
	}
	return (0);
}
*/


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

void	create_buttons(int	size, t_rt *rt)
{
	t_button **b;

	b = (t_button **)malloc(size * sizeof(t_button *));
	b[0] = save_button(rt);
	b[1] = mvmnt_button(rt);
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