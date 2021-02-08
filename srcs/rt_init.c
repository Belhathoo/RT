# include <rt.h>

t_camera	rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov)
{
	t_camera	c;
	t_vec	vup;

	vup = vec_unit(vec(0.001, 1.001, 0.001));
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (IMG_WIDTH / IMG_HEIGHT) * c.half_h;
	c.origin = lookfrom;
	c.w = vec_unit(vec_sub(lookat, lookfrom));
	c.u = vec_unit(vec_cross(c.w, vup));
	c.v = vec_cross(c.u, c.w);
	c.lower_left_corner = vec_sub(c.origin, vec_add(vec_pro_k(c.v, c.half_h),
				vec_pro_k(c.u, c.half_w)));
	c.lower_left_corner = vec_add(c.lower_left_corner, c.w);
	c.horizontal = vec_pro_k(c.u, 2.0 * c.half_w);
	c.vertical = vec_pro_k(c.v, 2.0 * c.half_h);
	c.fov = vfov;
	c.lookat = lookat;
	c.lookfrom = lookfrom;
	return (c);
}

t_texture		*rt_init_txt(t_rt *rt)
{
	t_texture	*txt;

	if ((!(txt = (struct s_texture*)malloc(sizeof(struct s_texture)))))
		rt_exit(rt, "Cannot allocate\n", EXIT_FAILURE); //rt_perror
	txt->buf = NULL;
	txt->img = NULL;
	return (txt);
}

t_light			*rt_init_light(void)
{
	t_light	*light;

	// recheck for other initialis// parameters
	// init depends on the type ! plus default light!!

	if (!(light = (struct s_l*)malloc(sizeof(struct s_l))))
		rt_perror();
	// rt_exit(rt, "Cannot allocate\n", EXIT_FAILURE);
	// light->pos = vec(-15.0,5.0,15.0);
	light->col = vec(1.0, 1.0, 1.0);
	light->intensity = 0.8;
	light->next = NULL;
	return (light);
}

t_object		*rt_init_object(void)
{
	t_object *obj;

	/*
	   recheck perror!! */
	if (!(obj = (struct s_o*)malloc(sizeof(struct s_o))))
		rt_perror();

	obj->name = NULL;
	obj->material = NULL; // make default material!!
	obj->txt = NULL;
	obj->pos = vec(0.0, 0.0, 0.0);
	obj->dir = vec(0.0, 1.0, 0.0);
	obj->rot = vec(0.0, 0.0, 0.0);
	obj->col = vec(1.0, 0.7, 0.3);
	obj->next = NULL;
	/* init material coefs*/
	return (obj);
}

t_scene		*rt_init_scene(void)
{
	t_scene *scene;

	if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		rt_perror();
	scene->anti_aliasing = 3;
	scene->ambient = 0.8;
	scene->object = NULL;
	scene->light = NULL;
	scene->cam.lookfrom = vec(10.0, 10.0 ,20.0);
	scene->cam.lookat = vec(0.0, 0.0, 0.0);
	scene->cam.fov = 60;
	return (scene);
}

void		rt_init(t_rt *rt)
{
	rt->img = NULL;
	rt->mlx = NULL;
	rt->data = NULL;
	rt->win = NULL;
	rt->filter = NONE_FILTER;
}
