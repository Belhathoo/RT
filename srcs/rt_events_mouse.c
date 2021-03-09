

# include <rt.h>

# define FRAME 40
# define MENU_BAR 180
# define COND_SLCT1(x) (x > FRAME && x < IMG_WIDTH + FRAME)
# define COND_SLCT2(y) (y > MENU_BAR && y < IMG_HEIGHT + MENU_BAR)
# define COND_SELECT(x, y) (COND_SLCT1(x) && COND_SLCT2(y))

void		rt_select_obj(t_rt *rt, int col, int row)
{
	t_ray		r;
	t_hit   rec;

	r = rt_get_ray(&RS->cam, (double)(col + 0.5) / IMG_WIDTH,
			(double)(row + 0.5) / IMG_HEIGHT);
	if (rt_hit(rt->scene, &r, &rec, MAX))
		RS->sl_obj = rec.curr_obj;
	else
		RS->sl_obj = NULL;
}

void        save_btn(t_rt *rt)
{
	// swap_button_by_id(SAVE_BTN , rt);
	image_create(rt);  
}

void        cam_btn(t_rt *rt)
{
    			RS->key_cam = (RS->key_cam + 1) % 2;
			swap_button_by_id(CAM_BTN, rt);
}

void            mvt_btn(t_rt *rt)
{
	swap_button_by_id(MVT_BTN , rt);
	// RS->sl_obj = NULL; // rmve for mac
	RS->key_mvt = (RS->key_mvt + 1) % 2;
	if (!RS->key_mvt && RS->key_cam == 1)
		swap_button_by_id(CAM_BTN, rt);
    RS->key_cam = 0;
    RS->key = 1;
	rt_redraw(rt);
}

void        light_btn(t_rt *rt)
{
	if (RS->light)
		RS->light = NULL;
	else if (rt->s_light)
		RS->light = rt->s_light;
	else
		return ;
	swap_button_by_id(LGHT_BTN , rt);
	rt_redraw(rt);
}

void        dame_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = DAMIER;
			RS->sl_obj->scale = 14;
		}
		else if (RS->sl_obj->noi.type == DAMIER)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 14;
			RS->sl_obj->noi.type = DAMIER;
		}
		rt_redraw(rt); //--
	}
}


void        circ_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = CIRCLES;
			RS->sl_obj->scale = 10;
		}
		else if (RS->sl_obj->noi.type == CIRCLES)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 10;
			RS->sl_obj->noi.type = CIRCLES;
		}
		rt_redraw(rt); //--
	}
}

void        v1_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI1;
			RS->sl_obj->scale = 4;
		}
		else if (RS->sl_obj->noi.type == VORONOI1)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 4;
			RS->sl_obj->noi.type = VORONOI1;
		}
		rt_redraw(rt); //--
	}
}

void        v2_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI2;
			RS->sl_obj->scale = 2.0;
		}
		else if (RS->sl_obj->noi.type == VORONOI2)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 2.0;
			RS->sl_obj->noi.type = VORONOI2;
		}
		rt_redraw(rt); //--
	}
}


void        v3_btn(t_rt *rt)
{
	if (RS->sl_obj->txt.is_txt == 0)
	{
		if (RS->sl_obj->noi.is_noise == 0)
		{
			RS->sl_obj->noi.is_noise = 1;
			RS->sl_obj->noi.type = VORONOI3;
			RS->sl_obj->scale = 0.1;
		}
		else if (RS->sl_obj->noi.type == VORONOI3)
			RS->sl_obj->noi.is_noise = 0; // scale!
		else
		{
			RS->sl_obj->scale = 0.1;
			RS->sl_obj->noi.type = VORONOI3;
		}
		rt_redraw(rt); //--
	}
}


int				rt_mouse(int button, int x, int y, t_rt *rt)
{

	int btn;

	if (button == 2)
		RS->sl_obj = NULL;
	if (button == 1 && COND_SELECT(x, y))
	{
		rt_select_obj(rt, x - FRAME, (int)IMG_HEIGHT - (y - MENU_BAR));
		if (RS->sl_obj != NULL)
		{
			ft_putstr("- selected_object: ");
			ft_putendl(RS->sl_obj->name);
		}
	}
	btn = get_selected_button(x, y, rt);
	if (btn != -1)
	{
		if (btn == SAVE_BTN)
			save_btn(rt);
		else if (btn == MVT_BTN)
			mvt_btn(rt);
		else if (btn == LGHT_BTN)
			light_btn(rt);
	}
	return (0);
}
