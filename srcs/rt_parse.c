
# include <rt.h>

void  rt_add_camera(t_tag *tag, t_rt *rt)
{
	t_camera  cam;

	cam.lookfrom = vec(0.0, 10.0 ,20.0);
	cam.lookat = vec(0.0, 0.0, 0.0);
	cam.fov = 60;
	while (TA)
	{
		if (!ft_strcmp(TA->name, "lookat"))
			cam.lookat = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "lookfrom"))
			cam.lookfrom = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "fov"))
			cam.fov = rt_ctod(TA->value, rt);
		TA = TA->next;
	}
	rt_check_cam(cam, rt);
	RS->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
}

int		rt_check_light_type(t_rt *rt, char *val)
{
	if (!ft_strcmp(val, "point"))
		return (PT_LIGHT);
	else if (!ft_strcmp(val, "spot"))
		return (SP_LIGHT);
	else if (!ft_strcmp(val, "parallel"))
		return (PL_LIGHT);
	else
		rt_exit(rt, "", "light type unknown", EXIT_FAILURE);
	return (-1);
}

void	rt_add_light(t_tag *tag, t_rt *rt)
{
	t_light *l;
	t_light	*tmp;

	l = rt_init_light(rt);
	tmp = RS->light;
	while (TA)
	{
		if (!ft_strcmp(TA->name, "type"))
			l->type = rt_check_light_type(rt, TA->value);
		else if (!ft_strcmp(TA->name, "position"))
			l->pos = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "direction"))
			l->dir = vec_unit(rt_ctovec(TA->value, rt));
		else if (!ft_strcmp(TA->name, "intensity"))
			l->intensity = rt_ctod(TA->value, rt);
		else if (!ft_strcmp(TA->name, "color"))
			l->col = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "angle"))
			l->angle = rt_ctod(TA->value, rt);
		// else if (!ft_strcmp(TA->name, "radius"))
		// 	l->radius = rt_ctod(TA->value, rt);
		TA = TA->next;
	}
	// rt_check_lights(l, rt);
	RS->light = l;
	l->next = tmp;
}




void  xml_to_rt(t_xml *x, t_rt *rt)
{

	if (x->cam_nbr != 1)
		xml_exit(x, "One Camera !!", EXIT_FAILURE);
	/*obj_nbr == 0 >> with UI can add objects*/
	while(x->tags)
	{
		if (!ft_strcmp(x->tags->name, "Camera"))
			rt_add_camera(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Object"))
			rt_add_object(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "N_Object"))
			rt_add_neg_object(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Light"))
			rt_add_light(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Option"))
			rt_add_option(x->tags, rt);
		x->tags = x->tags->next;
	}
}

void rt_parser(t_rt *rt, char **argv)
{
	t_xml *x;

	x = xml_init(argv[1]);
	if (xml_parse(x) == -1)
		xml_exit(x, "-1\n", EXIT_FAILURE);
	// err. (check redo in main libxml)
	xml_to_rt(x, rt);
	// printf("%d", RS->light->type);
	rt->name_sc = argv[1];
	xml_close(x);
}
