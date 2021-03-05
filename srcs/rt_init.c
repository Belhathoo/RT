# include <rt.h>

t_camera	rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov)
{
	t_camera	c;
	t_vec	vup;
	t_vec	tmp;
	
	tmp = vec_unit(vec_sub(lookat, lookfrom));
	vup = vec_unit(vec(0.0, 1.0, 0.0));

	// if (tmp.x == vup.x && tmp.y == vup.y && tmp.z == vup.z)
	// 	vup.y += 0.01;// = vec_add_k(vup, 0.0001);
	if (!(vec_dot(vec_cross(tmp, vup), vec3(1.0))))
		vup = vec_add_k(vup, 0.01);
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

t_texture		rt_init_txt(void)
{
	t_texture	txt;

	txt.is_txt = 1;
	txt.is_trans = 0;
	txt.buf = NULL;
	txt.img = NULL;
	return (txt);
}


t_object		rt_init_neg_object(void)
{
	t_object obj;

	/*
	   recheck perror!! */
	obj.name = NULL;
	obj.pos = vec(0.0, 0.0, 0.0);
	obj.size = 2.0;
	obj.angle = 30.0;
	obj.dir = vec(0.0, 1.0, 0.0);
	obj.rot = vec(0.0, 0.0, 0.0);
	obj.is_sliced = 0;
	obj.txt.is_txt = 0;
	obj.noi.is_noise = 0;
	obj.next = NULL;
	obj.compos = NULL;
	return (obj);
}


t_light			*rt_init_light(void)
{
	t_light	*light;

	// recheck for other initialis// parameters
	// init depends on the type ! plus default light!!
	if (!(light = (struct s_l*)malloc(sizeof(struct s_l))))
		rt_perror();
	// rt_exit(rt, "Cannot allocate\n", EXIT_FAILURE);
	light->type = PT_LIGHT;
	light->angle = 30.0;
	light->pos = vec(5.0, 5.0, 15.0);
	light->col = vec(1.0, 1.0, 1.0);
	light->dir = vec3(1.0);
	light->intensity = 0.8;
	light->next = NULL;
	return (light);
}

t_noise			rt_init_noise(void)
{
	t_noise n;

	n.is_noise = 0;
	n.type = 0;
	n.col1 = vec(1.0, 1.0, 1.0);
	n.col2 = vec(0.0, 0.0, 0.0);
	return (n);
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
	obj->pos = vec(0.0, 0.0, 0.0);
	obj->size = 3.0;
	obj->radius = 3.0;
	obj->angle = 35;
	obj->r = 1.0;
	obj->dist = 4.0;
	obj->width = 4.0;
	obj->height = 2.50;
	obj->angle = 30.0;
	obj->dir = vec(0.0, 1.0, 0.0);
	obj->rot = vec(0.0, 0.0, 0.0);
	obj->col = vec(1.0, 0.7, 0.3);
	obj->txt.is_txt = 0;
	obj->noi = rt_init_noise();
	obj->scale = 1.5;
	obj->is_sliced = 0;
	obj->sl_pnt = vec(0.0, 0.0, 0.0);
	obj->sl_vec = vec(0.0, -1.0, 0.0);;
	obj->refl = 0.0;
	obj->refr = 0.0;
	obj->next = NULL;
	obj->compos = NULL;
	return (obj);
}

t_scene		*rt_init_scene(void)
{
	t_scene *scene;

	if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		rt_perror();
	scene->progress = 1;
	scene->select = 0;
	scene->max_anti_a = 9;
	scene->aa = 1;
	scene->ambient = 0.15;
	scene->object = NULL;
	scene->light = NULL;
	scene->sl_obj = NULL;
	scene->is_neg = 0;
	scene->key = 1;
	scene->key2 = 0;
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
