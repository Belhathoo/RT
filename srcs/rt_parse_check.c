
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

void	rt_rot_dir(t_vec *r, t_vec d)
{
    /* check rt_parse_utils !!!!!!! */
	*r = d;
}

void    rt_check_obj(t_object *o, t_rt *rt)
{
    if (o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0)
        rt_exit(rt, "Direction est un vectur non nul!", EXIT_FAILURE);
    if (o->size <= 0.0)
        rt_exit(rt, "obj: radius should be positive", EXIT_SUCCESS);
	rt_set_coef(o, rt);
  	// rt_rot_dir(&o->rot, o->dir);
}