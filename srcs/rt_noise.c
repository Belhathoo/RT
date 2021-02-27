

# include <rt.h>

t_vec		rt_noise_damier(t_hit *rec)
{
	int pro1;
	int pro2;
	
	if (ft_strcmp(rec->curr_obj->name, "torus") == 0)
		return (rt_torus_noise(rec));
	if (ft_strcmp(rec->curr_obj->name, "sphere") == 0)
	    rec->curr_obj->scale = 1.0;

	pro1 = floor(rec->u * 14);
	pro2 = floor(rec->v * 14);
	if (fabs(fmod(pro1, 2)) == fabs(fmod(pro2, 2)))
	     return (rec->curr_obj->noi.col1);
	return (rec->curr_obj->noi.col2);	
}

t_vec	rt_noise_circles(t_object *o, t_hit *rec)
{
	double		pro;
	t_vec	r_p;

	r_p = vec_pro_k(vec_sub(o->pos, rec->p), o->scale);
	pro = floor(vec_length(r_p));
	if (fmod(pro, 2) == 0.0)
		return (rec->curr_obj->noi.col1);
	else
		return (rec->curr_obj->noi.col2);
}

t_vec	rt_noise_voronoi(t_hit *rec, t_object *o)
{
	t_vec  r_p;
    r_p = vec_sub(rec->p, o->pos);
	r_p = vec(vec_dot(r_p, o->vec1), vec_dot(r_p, o->vec2), vec_dot(r_p, o->rot));
	return (rt_voronoi(r_p, o));

}

t_vec	rt_noise(t_object *o, t_hit *rec)
{
	t_vec	ret;
	int  type;

	type = o->noi.type;
	ret = o->noi.col1;
	if (type == DAMIER)
		return (rt_noise_damier(rec));
	else if (type == CIRCLES)
	    return(rt_noise_circles(o, rec));
	else if (type == VORONOI1 || type == VORONOI2)
	   return (rt_noise_voronoi(rec, o));
	else
		return (ret);
}