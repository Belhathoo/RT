
#include <rt.h>

void    rt_check_cam(t_camera c, t_rt *rt)
{
	if (c.lookat.x == c.lookfrom.x && c.lookat.y == c.lookfrom.y\
			&& c.lookat.z == c.lookfrom.z)
		rt_exit(rt, "camera: lookat & lookfrom should be different!", EXIT_FAILURE);
	if (c.fov < 4.0 || c.fov > 180)
		rt_exit(rt, "camera: fov is an angle [4-180]", EXIT_FAILURE);
}


void     rt_check_obj_name(t_object *obj, t_rt *rt)
{
	char	*str;

	if (obj->name == NULL)
		rt_exit(rt, "Object shoud have a name!", EXIT_FAILURE);
	str = ft_strdup(obj->name);
	str = ft_strupcase(str);
	if (!ft_strcmp(str, "SPHERE"))
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
	else if (!ft_strcmp(str, "RECTANGLE"))
		obj->hit = rt_hit_care;
	else if (!ft_strcmp(str, "L_CYLINDER"))
		obj->hit = rt_hit_l_cylinder;
	else if (!ft_strcmp(str, "L_CONE"))
		obj->hit = rt_hit_l_cone;
	else
	{
		ft_strdel(&str);
		rt_exit(rt, ft_strjoin(obj->name, "unknown obj!"), EXIT_FAILURE);
	}
	ft_strdel(&str);
}

void			rt_set_coef(t_object *o, t_rt *rt)
{

	/* check if txt !!!
	   specific coef for textures (NO SPECULAR)
	   */
	if (!o->material)
		o->material = ft_strdup("ko");
	if (!ft_strcmp(o->material, "chrome"))
	{
		o->mat.ka = 0.25;
		o->mat.kd = 0.9;
		o->mat.ks = 0.29;
		o->mat.kr = 0.0;
		o->mat.kt = 0.0;
		o->mat.shininess = 5;
	}
	else if (!ft_strcmp(o->material, "diamond"))
	{
		o->mat.ka = 0.8;
		o->mat.kd = 0.4;
		o->mat.ks = 0.774;
		o->mat.shininess = 76.8;
		o->mat.kt = 1.42;
		o->mat.kr = 0.0;
	}
	else if (!ft_strcmp(o->material, "ice"))
	{
		o->mat.ka = 0.25;
		o->mat.kd = 0.4;
		o->mat.ks = 0.5;
		o->mat.shininess = 50;
		o->mat.kt = 1.5;
		o->mat.kr = 0.2;
	}
	else if (!ft_strcmp(o->material, "gold"))
	{
		o->mat.ka = 0.5;
		o->mat.kd = 0.5;
		o->mat.ks = 0.5;
		o->mat.shininess = 51.2;
		o->mat.kr = 0.8;
		o->mat.kt = 0.0;
	}
	else if (!ft_strcmp(o->material, "al"))
	{
		// o->mat = (t_material){}
		o->mat.ka = 0.75;
		o->mat.kd = 0.9;
		o->mat.ks = 1.0;
		o->mat.shininess = 20;
		// o->mat.kr = 0.99;
		o->mat.kr = 0.0;
		o->mat.kt = 0.0;
	}
	else
	{
		o->mat.ka = 0.7;
		o->mat.kd = 0.6;
		o->mat.ks = 0.6;
		o->mat.kr = 0.0;
		o->mat.kt = 0.0;
		o->mat.shininess = 50;
	}
	if(o->txt)
		{
			o->mat.ka = 1.0;
			o->mat.shininess = 0;
			o->mat.ks = 0;
		}
}

void	rt_rot_dir(t_vec *r, t_vec d)
{
	/* check rt_parse_utils !!!!!!! */
	*r = d;
}

void	rt_comp_obj(t_object *o)
{
	if (ft_strcmp(o->name, "cube") == 0)
		get_cube_compos(o);

}

void    rt_check_obj(t_object *o, t_rt *rt)
{

	/*
		radius for cone ((angle ]0 -180]))!!!!!!!!!
	*/
	if (ft_strcmp(o->name, "sphere") &&\
		(o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0))
	{	
		o->dir = vec(1.0, 1.0, 0.0);
		rt_exit(rt, "obj: direction vector is non-zero!", EXIT_FAILURE);
	}
	if (o->size <= 0.0 && ft_strcmp(o->name, "plan") != 0)
		rt_exit(rt, "obj: radius should be positive", EXIT_FAILURE);
	o->angle *= M_PI / 180 / 2;
	if (o->txt && o->noi.is_noise == 1)
		rt_exit(rt, "obj: either texture either noise", EXIT_FAILURE);
	rt_rot_dir(&o->rot, o->dir);
	rt_get_repere(o);
	rt_comp_obj(o);
	rt_adjustment(&o->col);
	rt_set_coef(o, rt);
}

void	rt_check_lights(t_light *l, t_rt *rt)
{
		/*
		minit dir/radius/angle for other light types !!!!
		*/
	// if (l->dir.x == 0 && l->dir.y == 0 && l->dir.z == 0)
	// 	rt_exit(rt, "light: direction vector is non-zero!", EXIT_FAILURE);
	if ((l->intensity = ft_clamping(l->intensity)) == 0.0)
		rt_exit(rt, "light: intensity is a positive number ]0-1]", EXIT_FAILURE);
	if (l->angle)
// check if soft first !! for radius !
	// if (l->radius <= 0.0)
	// 	rt_exit(rt, "light: radius should be positive", EXIT_FAILURE);
	rt_adjustment(&l->col);
}