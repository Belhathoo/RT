

# include <rt.h>

# define FRAME 40
# define MENU_BAR 180

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

# define COND_SLCT1(x) (x > FRAME && x < IMG_WIDTH + FRAME)
# define COND_SLCT2(y) (y > MENU_BAR && y < IMG_HEIGHT + MENU_BAR)
# define COND_SELECT(x, y) (COND_SLCT1(x) && COND_SLCT2(y))

int				rt_mouse(int button, int x, int y, t_rt *rt)
{

	int btn;

	if (button == 2)
		RS->sl_obj = NULL;
	if (button == 1 &&
		((x > FRAME_LFT && x < IMG_WIDTH + FRAME_RGHT) \
		&& y > FRAME_UP && y < IMG_HEIGHT + FRAME_DWN))
	{
		rt_select_obj(rt, x - FRAME_LFT, (int)IMG_HEIGHT - (y - FRAME_UP));
		if (RS->sl_obj != NULL)
		{
			ft_putstr(" - selected_object:");
			ft_putendl(RS->sl_obj->name);
		}
	}
	btn = get_selected_button(x, y, rt);
	if (btn != -1)
	{
		if (btn == SAVE_BTN)
			save_btn(rt);
		if (btn == MVT_BTN)
			mvt_btn(rt);
		if (RS->key_mvt == 1)
		{
			(btn == LGHT_BTN) ? light_btn(rt) : 0;
			if (btn == CAM_BTN)
				cam_btn(rt);
			else if (RS->sl_obj != NULL)
			{
				(btn == DAME_BTN ) ? dame_btn(rt) : 0;
				(btn == CIRC_BTN ) ? circ_btn(rt) : 0;
				(btn == V1_BTN) ? v1_btn(rt) : 0;
				(btn == V2_BTN) ? v2_btn(rt) : 0;
				(btn == V3_BTN) ? v3_btn(rt) : 0;
			}
		}
		return (0);
	}
	return (0);
}
