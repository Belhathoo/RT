/* ************************************************************************** */
#include <rt.h>

void  add_(t_object *o)
{ 

	if (ft_strcmp(o->name, "Cube") == 0)
		get_cube_compos( o);

}

void background(t_rt *rt)
{
	int i;
	int j;

	i = -1;
	while (j = -1, ++i < WIN_WIDTH)
		while (++j < WIN_HEIGHT)
			mlx_pixel_put(rt->mlx, rt->win, i, j, 0x3E3E3d);
}

int main(int argc, char **argv)
{
	t_rt rt;


	rt_init(&rt);
	rt.scene = rt_init_scene();
	rt.mlx = mlx_init();
	if (argc == 2)
		// ft_parser(argv[1], &rt);
		rt_parser(&rt, argv);
	else
		rt_exit(&rt, ft_strdup("usage: ./rt scene_file"), EXIT_FAILURE);
	rt.win = mlx_new_window(rt.mlx, WIN_WIDTH, WIN_HEIGHT, "RT");
	rt.img = mlx_new_image(rt.mlx, IMG_WIDTH, IMG_HEIGHT);
	rt.data = (int*)mlx_get_data_addr(rt.img, &rt.bpp, &rt.size, &rt.endian);
	//background(&rt);
	rt_draw(&rt);
	mlx_hook(rt.win, 17, (1L << 17), rt_close, &rt);
	mlx_hook(rt.win, 2, (1L << 0), rt_keys, &rt);
	mlx_hook(rt.win, 4, (1L << 0), rt_mouse, &rt);
	mlx_loop(rt.mlx);
	return (EXIT_SUCCESS);
}
