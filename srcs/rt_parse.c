
# include <rt.h>


void  rt_add_camera(t_tag *tag, t_rt *rt)
{
	t_camera  cam;

	cam.lookfrom = vec(10.0, 10.0 ,20.0);
	cam.lookat = vec(0.0, 0.0, 0.0);
	cam.fov = 60;
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "lookat"))
			cam.lookat = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "lookfrom"))
			cam.lookfrom = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "fov"))
			cam.fov = rt_ctod(tag->attr->value, rt);
		tag->attr = tag->attr->next;
	}
	rt_check_cam(cam, rt);
	rt->scene->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
}

void  rt_add_object(t_tag *tag, t_rt *rt)
{
	/*
		add different attributes Direction and Rotation !! redo rots functions!!
	*/
	
	t_object	*obj;
	t_object	*tmp;

	obj = rt_init_object();
	tmp = rt->scene->object;
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "name"))
		{
			obj->name = ft_strdup(tag->attr->value);
			rt_check_obj_name(obj, rt);
		}
		else if (!ft_strcmp(tag->attr->name, "position"))
			obj->pos = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "direction"))
			obj->dir = vec_unit(rt_ctovec(tag->attr->value, rt));
		else if (!ft_strcmp(tag->attr->name, "translation"))
			obj->pos = vec_add(obj->pos, rt_ctovec(tag->attr->value, rt));
		else if (!ft_strcmp(tag->attr->name, "rotation"))
			obj->rot = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "color"))
			obj->col = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "radius"))
			obj->size = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "r"))
			obj->r = rt_ctod(tag->attr->value, rt);    
		else if (!ft_strcmp(tag->attr->name, "texture"))
			obj->txt = rt_ctotxt(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "noise"))
			obj->noi = rt_add_noise(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "material"))
			obj->material = ft_strdup(tag->attr->value);
		else if (!ft_strcmp(tag->attr->name, "slice_vec") && (obj->is_sliced = 1))
			obj->sl_vec = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "slice_pnt") && (obj->is_sliced = 1))
			obj->sl_pnt = rt_ctovec(tag->attr->value, rt);
		else
			rt_exit(rt, ft_strjoin(tag->name, "Unknown attribut"), EXIT_FAILURE);
		tag->attr = tag->attr->next;
	}
	rt_check_obj(obj, rt);
	rt->scene->object = obj;
	obj->next = tmp;
}

void  rt_add_light(t_tag *tag, t_rt *rt)
{
	t_light *l;
	t_light	*tmp;

	l = rt_init_light();
	tmp = rt->scene->light;
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "type")) // to redo!!
			l->type = 0; //ft_strdup(tag->attr->value);
		else if (!ft_strcmp(tag->attr->name, "position"))
			l->pos = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "direction"))
			l->dir = vec_unit(rt_ctovec(tag->attr->value, rt));
		else if (!ft_strcmp(tag->attr->name, "intensity"))
			l->intensity = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "color"))
			l->col = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "radius"))
			l->radius = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "angle"))
			l->angle = rt_ctod(tag->attr->value, rt);
		tag->attr = tag->attr->next;
	}
	rt_check_lights(l, rt);
	rt->scene->light = l;
	l->next = tmp;
}

void  rt_add_option(t_tag *tag, t_rt *rt)
{
	while(tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "anti-aliasing"))
			rt->scene->anti_aliasing = rt_ctod(tag->attr->value, rt); //atoi
//		if (!ft_strcmp(tag->attr->name, "filtre"))
//			rt->filter = fnct for filters;		
		tag->attr = tag->attr->next;
	}
	if (rt->scene->anti_aliasing <= 0 )
		rt_exit(rt, "anti-aliasing should be a positive int", EXIT_FAILURE);	
}

void  xml_to_rt(t_xml *x, t_rt *rt)
{
	/*
	   function that looks for s pecific tag
	   */
	if (x->cam_nbr != 1)
		xml_exit(x, "One Camera !!", EXIT_FAILURE);   /*	obj_nbr == 0 >> with UI can add objects*/

	while(x->tags)
	{
		if (!ft_strcmp(x->tags->name, "Camera"))
			rt_add_camera(x->tags, rt);
		else if (!ft_strcmp(x->tags->name, "Object"))
			rt_add_object(x->tags, rt);
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

	xml_close(x);
}
