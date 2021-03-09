/* ************************************************************************** */
#include <rt.h>

void background(t_rt *rt)
{
	int i;
	int j;

	i = -1;
	void *img;
	int *data;
	img = mlx_new_image(rt->mlx, WIN_WIDTH, WIN_HEIGHT);
	data = (int*)mlx_get_data_addr(img, &rt->bpp, &rt->size, &rt->endian);

	while (j = -1, ++i < WIN_WIDTH)
		while (++j < WIN_HEIGHT)
			data[j * (int)WIN_WIDTH + i] = 0x00202f;
			// mlx_pixel_put(rt->mlx, rt->win, i, j, 0x00202f);
	mlx_put_image_to_window(rt->mlx, rt->win, img, 0, 0);
}


int main(int argc, char **argv)
{
	t_rt rt;


	rt_init(&rt);
	rt.scene = rt_init_scene();
	rt.mlx = mlx_init();
	if (argc == 2)
		rt_parser(&rt, argv);
	else
		rt_exit(&rt, ft_strdup("usage: ./rt scene_file"), EXIT_FAILURE);
	rt.win = mlx_new_window(rt.mlx, WIN_WIDTH, WIN_HEIGHT, "RT");
	rt.img = mlx_new_image(rt.mlx, IMG_WIDTH, IMG_HEIGHT);
	rt.data = (int*)mlx_get_data_addr(rt.img, &rt.bpp, &rt.size, &rt.endian);
	background(&rt);

	create_buttons(9, &rt);
	rt.s_light = rt.scene->light;
			rt.scene->sl_obj = rt.scene->object;
	mlx_hook(rt.win, 17, (1L << 17), rt_close, &rt);
	mlx_hook(rt.win, 4, (1L << 0), rt_mouse, &rt);
	mlx_hook(rt.win, 2, (1L << 0), rt_keys, &rt);


	mlx_loop_hook(rt.mlx, &progress_bar, &rt);
	mlx_loop(rt.mlx);
	return (EXIT_SUCCESS);
}
