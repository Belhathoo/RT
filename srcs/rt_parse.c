
# include <rt.h>


void  rt_add_camera(t_tag *tag, t_rt *rt)
{
	t_camera  cam;

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
	rt->scene->cam = rt_init_camera(cam.lookfrom, cam.lookat, cam.fov);
	// printf("\n{Cam}\n\tlkat:\t%.2f %.2f  %.2f\n\tlkfrm:\t%.2f %.2f  %.2f\n\tfov:\t%.2f\n\n",\
	cam.lookat.x, cam.lookat.y, cam.lookat.z, cam.lookfrom.x, cam.lookfrom.y, cam.lookfrom.z,cam.fov);
}

int	rt_check_obj(t_object *obj, t_rt *rt)
{
	char	*str;

	str = ft_strdup(obj->name);
	str = ft_strupcase(str);
	if (obj->name == NULL)
		rt_exit(rt, "Object shoud have a name!", EXIT_FAILURE);
	else if (!ft_strcmp(str, "SPHERE"))
		obj->hit = rt_hit_sphere;
	else if (!ft_strcmp(str, "CYLINDER"))
		obj->hit = rt_hit_cylinder;
	else if (!ft_strcmp(str, "PLAN"))
		obj->hit = rt_hit_plan;
	else if (!ft_strcmp(str, "CONE"))
		obj->hit = rt_hit_cone;
	else if (!ft_strcmp(str, "CUBE"))
		obj->hit = rt_hit_cube;
	else if (!ft_strcmp(str, "TORUS"))
		obj->hit = rt_hit_torus;
	else if (!ft_strcmp(str, "PARABOL"))
		obj->hit = rt_hit_parabol;
	else
		rt_exit(rt, ft_strjoin(obj->name, "unknown obj!"), EXIT_FAILURE);
	ft_strdel(&str);
	return (1);
}

void			rt_set_coef(t_object *o, t_rt *rt)
{

	/* check if txt !!!
		specific coef for textures (NO SPECULAR)
*/
	if (!o->material)
		o->material = ft_strdup("Chrome");
	if (!ft_strcmp(o->material, "Chrome"))
	{
		o->ka = 0.25;
		o->kd = 0.4;
		o->ks = 0.774;
		o->shininess = 76.8;
		return;
	}
	o->ka = 0.8;
	o->kd = 0.6;
	o->ks = 0.6;
	o->shininess = 90;
}



void  rt_add_object(t_tag *tag, t_rt *rt)
{
	/*
	   add different attributes Direction and Rotation !! redo rots functions!!*/
	t_object  *obj;

	obj = rt_init_object();
	while (tag->attr)
	{
		// printf("**%s**\n", tag->attr->name);
		if (!ft_strcmp(tag->attr->name, "name"))
		{
			obj->name = ft_strdup(tag->attr->value);
			rt_check_obj(obj, rt);
		}
		else if (!ft_strcmp(tag->attr->name, "position"))
			obj->pos = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "direction"))
			obj->dir = rt_ctovec(tag->attr->value, rt);
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
		else if (!ft_strcmp(tag->attr->name, "material"))
			obj->material = ft_strdup(tag->attr->value);
		// if (!ft_strcmp(tag->attr->name, "noise"))
		// 	obj->noise = ft_strdup(tag->attr->value);
		else
			rt_exit(rt, ft_strjoin(tag->name, "Unknown attribut"), EXIT_FAILURE);
		tag->attr = tag->attr->next;
	}
	rt_rot_dir(&obj->rot, obj->dir);
	rt_set_coef(obj, rt);
	if (rt->scene->object == NULL)
		rt->scene->object = obj;
	else
		rt->scene->object->next = obj;
}

void  rt_add_light(t_tag *tag, t_rt *rt)
{
	t_light *l;

	l = rt_init_light();
	while (tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "type")) // to redo!!
			l->type = 0; //ft_strdup(tag->attr->value);
		else if (!ft_strcmp(tag->attr->name, "position"))
			l->pos = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "direction"))
			l->dir = rt_ctovec(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "intensity"))
			l->intensity = rt_ctod(tag->attr->value, rt);
		else if (!ft_strcmp(tag->attr->name, "color"))
			l->col = rt_ctovec(tag->attr->value, rt);

		tag->attr = tag->attr->next;
	}
	if (rt->scene->light == NULL)
		rt->scene->light = l;
	else
		rt->scene->light->next = l;
	// printf("\n{FCT-Light}\n\tpos:\t%.2f %.2f  %.2f\n\tcolor:\t%.2f %.2f  %.2f\n\tintensity:\t%.2f\n\n",\
	// l->pos.x, l->pos.y, l->pos.z, l->col.x, l->col.y, l->col.z,l->intensity);
}

void  rt_add_option(t_tag *tag, t_rt *rt)
{
	while(tag->attr)
	{
		if (!ft_strcmp(tag->attr->name, "anti-aliasing"))
			rt->scene->anti_aliasing = rt_ctod(tag->attr->value, rt);
		tag->attr = tag->attr->next;
	}
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
	{
		xml_exit(x, "-1\n", EXIT_FAILURE);
		return;}// err. (check redo in main libxml)
	xml_to_rt(x, rt);



	t_object *o, *tt;
	t_camera c;
	t_light	*l;

	l = rt->scene->light;
	c = rt->scene->cam;
	o = rt->scene->object;
	// printf("Options:\taa %d\tl.int %f\n", rt->scene->anti_aliasing, rt->scene->light->intensity);
	// printf("\n{Cam}\n\tlkat:\t%.2f %.2f  %.2f\n\tlkfrm:\t%.2f %.2f  %.2f\n\tfov:\t%.2f\n\n",\
	// c.lookat.x, c.lookat.y, c.lookat.z, c.lookfrom.x, c.lookfrom.y, c.lookfrom.z,c.fov);
	// while (l)
	// {
	// 	printf("{Light}\n\tpos\t%.2f %.2f %.2f\n", l->pos.x, l->pos.y, l->pos.z);
	// 	printf("\tcol\t\t%.2f %.2f %.2f\n", l->col.x, l->col.y, l->col.z);
	// 	l = l->next;
	// }

	// while (o)
	// {
	// 	printf("[%s]\n", o->name);
	// 	printf("\tmat:\t\t%s\n", o->material);
	// 	printf("\tsize\t\t%.2f\n", o->size);
	// 	printf("\tpos\t\t%.2f %.2f %.2f\n", o->pos.x, o->pos.y, o->pos.z);
	// 	printf("\tdir(rot!)\t%.2f %.2f %.2f\n", o->rot.x, o->rot.y, o->rot.z);
	// 	printf("\tcol\t\t%.2f %.2f %.2f\n", o->col.x, o->col.y, o->col.z);
	// 	o = o->next;
	// }

	xml_close(x);
}
