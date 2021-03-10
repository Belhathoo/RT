
#include <rt.h>

void    rt_check_cam(t_camera c, t_rt *rt)
{
	if (c.lookat.x == c.lookfrom.x && c.lookat.y == c.lookfrom.y\
			&& c.lookat.z == c.lookfrom.z)
		rt_exit(rt, "", "camera: lookat & lookfrom should be different!", EXIT_FAILURE);
	if (c.fov < 4.0 || c.fov > 180)
		rt_exit(rt, "", "camera: fov is an angle [4-180]", EXIT_FAILURE);
}

void	rt_check_obj_name(t_object *obj, t_rt *rt)
{
	char	*str;

	if (obj->name == NULL)
		rt_exit(rt, "", "Object shoud have a name!", EXIT_FAILURE);
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
		obj->hit = rt_hit_lcylinder;
	else if (!ft_strcmp(str, "L_CONE"))
		obj->hit = rt_hit_lcone;
	else if (!ft_strcmp(str, "GLASSE"))
		obj->hit = rt_hit_glasse;
	else if (!ft_strcmp(str, "CUBE_TROUE"))
		obj->hit = rt_hit_cube_troue;
	else if (!ft_strcmp(str, "MOBIUS"))
		obj->hit = rt_hit_mobius;
	else
	{
		ft_strdel(&str);
		rt_exit(rt, obj->name," unknown obj!/n", EXIT_FAILURE); // no join
	}
	ft_strdel(&str);
}
void     rt_check_neg_obj_name(t_object *obj, t_rt *rt)
{
	char	*str;

	str = ft_strdup(obj->name);
	str = ft_strupcase(str);

	if (!ft_strcmp(str, "SPHERE"))
		obj->hit = rt_negative_sphere;
	else if (!ft_strcmp(str, "CYLINDER"))
		obj->hit = rt_negative_cylinder;
	else if (!ft_strcmp(str, "CONE"))
		obj->hit = rt_negative_cone;
	else
	{
		ft_strdel(&str);
		rt_exit(rt, obj->name,"unknown neg-obj!", EXIT_FAILURE);
	}
	ft_strdel(&str);
}

void			rt_set_coef(t_object *o)
{

	/* check if txt !!!
	   specific coef for textures (NO SPECULAR)
	   */
	if (o->material)
	{
		if (!ft_strcmp(o->material, "bl_plastic"))
			o->mat = (t_material){vec3(0.0), vec3(0.01), vec3(0.5), 32, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "cu"))
			o->mat = (t_material){vec(0.33, 0.23, 0.02), vec(0.78, 0.568, 0.113)\
				, vec(0.99, 0.94, 0.807), 27.897, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "chrome"))
			o->mat = (t_material){vec3(0.25), vec3(0.4), vec3(0.774), 76.70, 0.0, 0.0};
		else if (!ft_strcmp(o->material, "gold"))
			o->mat = (t_material){vec(0.24, 0.199, 0.074), vec(0.75, 0.606, 0.226),\
				vec(0.628, 0.555, 0.3660), 51.2, 0.55, 0.0};
		else if (!ft_strcmp(o->material, "mirror"))
			o->mat = (t_material){vec3(1.0), vec3(1.0), vec3(1), 100, 1.0, 0.0};
		else if (!ft_strcmp(o->material, "diamond"))
			o->mat = (t_material){vec3(0.8), vec3(0.4), vec3(0.2), 146.80, 0.0, 2.41};
		else if (!ft_strcmp(o->material, "ice"))
			o->mat = (t_material){vec3(0.8), vec3(0.2), vec3(0.2), 10, 0.0, 1.331};
		else if (!ft_strcmp(o->material, "glass"))
			o->mat = (t_material){vec3(0.25), vec3(0.2), vec3(0.5), 70, 0.0, 1.50};
		else if (!ft_strcmp(o->material, "water"))
			o->mat = (t_material){vec3(0.5), vec3(0.1), vec3(0.05), 20, 0.0, 1.20};
		else if (!ft_strcmp(o->material, "al"))
			o->mat = (t_material){vec3(0.92), vec3(0.999), vec3(0.8), 25, 0.150, 0.0};
		else
			o->mat = (t_material){vec3(0.7), vec3(0.8), vec3(0.30), 50 ,0.0 ,0.0};
	}
	else
		o->mat = (t_material){vec3(0.7), vec3(0.8), vec3(0.30), 50 ,0.0 ,0.0};
}

t_vec	rt_rot_dir(t_vec *r, t_vec d)
{
	/* check rt_parse_utils !!!!!!! */

	// return(rotation(d, r));
	*r = d;
	*r = rotation(d, *r);
	return vec3(1.0);
}

void	rt_comp_obj(t_object *o, t_rt *rt)
{
	if (ft_strcmp(o->name, "cube") == 0)
		get_cube_compos(o, rt);
}

void    rt_check_obj(t_object *o, t_rt *rt)
{

	// height width

	if (o->name == NULL)
		rt_exit(rt, "", "Object shoud have a name!", EXIT_FAILURE);
	if (o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0)
		rt_exit(rt, "", "obj: direction vector is non-zero!", EXIT_FAILURE);
	if (o->size <= 0.0 || o->radius <= 0.0 || o->r <= 0)
		rt_exit(rt, "", "obj: radius/r/size should be positive", EXIT_FAILURE);
	if (o->angle <= 0.0 || o->angle > 180.0)
		rt_exit(rt, "", "obj: angle should be in ]0-180[", EXIT_FAILURE);
	if (o->txt.is_txt == 1 && o->noi.is_noise == 1)
		rt_exit(rt, "", "obj: either texture either noise", EXIT_FAILURE);
	if (o->refr != 0.0 && (o->refr < 01.000 || o->refr > 10.0))
		rt_exit(rt, "", "refraction coef should be >= 1.0.", EXIT_FAILURE);
	if (o->is_sliced == 1) //events
	{
		if (!ft_strcmp(o->name, "sphere") && !in_sphere(o))
			rt_exit(rt, "", "sl-obj: slicing pnt is outside the sphere!", EXIT_FAILURE);
		if (!ft_strcmp(o->name, "cylinder") && !in_cylindr(o))
			rt_exit(rt, "", "sl-obj: slicing pnt is outside the cylinder!", EXIT_FAILURE);
	}

	if (!ft_strcmp(o->name, "l_cone") && o->height >= o->width)
			rt_exit(rt, "", "l_cone: height should be < width. (init: w:5 h:2.5) ", EXIT_FAILURE);
	if ((!ft_strcmp(o->name, "l_cylinder") || !ft_strcmp(o->name, "mobius")) && o->height <= 0.0)
			rt_exit(rt, "", "l_obj: height should be strictly positive. ", EXIT_FAILURE);
	if (!ft_strcmp(o->name, "rectangle") && (o->height <= 0.0 || o->width <= 0.0))
		rt_exit(rt, "", "rectangle: height & width should be strictly positive. ", EXIT_FAILURE);
	/*
	   add x y z slicing global || on ax
	   */

	o->angle = degtorad(o->angle) / 2;
	o->rot = rotation(o->dir, o->rot);
	rt_get_repere(o); ///events nop
	rt_comp_obj(o, rt); //// events...
	rt_adjustment(&o->col);
	
	rt_set_coef(o);
	if (o->refr == 0.0)
		o->refr = o->mat.kt;
	if (o->refl == 0.0)
		o->refl = o->mat.kr;
}


void    rt_check_neg_obj(t_object *o, t_rt *rt)
{
	if (o->name == NULL)
		rt_exit(rt, "", "Neg-Object shoud have a name!", EXIT_FAILURE);
	if (o->dir.x == 0 && o->dir.y == 0 && o->dir.z == 0)
		rt_exit(rt, "", "obj: direction vector is non-zero!", EXIT_FAILURE);
	if (o->radius <= 0.0)
		rt_exit(rt, "", "obj: radius should be positive", EXIT_FAILURE);
	if (o->angle <= 0.0 || o->angle > 179.0)
		rt_exit(rt, "", "obj: angle should be in ]0-180[", EXIT_FAILURE);
	o->angle = degtorad(o->angle) / 2;
	rt_rot_dir(&o->rot, o->dir);
}

void	rt_check_lights(t_light *l, t_rt *rt)
{
	/*
	   init dir/radius/angle for other light types !!!!
	   */
	// check color (0 0 0) && intensity < 0
// check type
	if (l->dir.x == 0 && l->dir.y == 0 && l->dir.z == 0)
		rt_exit(rt, "", "light: direction vector is non-zero!", EXIT_FAILURE);
	if ((l->intensity = ft_clamping(l->intensity)) == 0.0)
		rt_exit(rt, "", "light: intensity is a positive number ]0-1]", EXIT_FAILURE);
	if (l->angle < 0.0 || l->angle > 180.0)
		rt_exit(rt, "", "light: angle should be in ]0-180].", EXIT_FAILURE);
	if (l->col.x == 0.0 && l->col.y == 0.0 && l->col.z == 0.0)
		rt_exit(rt, "", "light: no light have black color", EXIT_FAILURE);
	// check if soft first !! for radius !
	// if (l->radius <= 0.0)
	// 	rt_exit(rt, "", "light: radius should be positive", EXIT_FAILURE);
	rt_adjustment(&l->col);
	l->intensity = ft_clamping(l->intensity);
}
