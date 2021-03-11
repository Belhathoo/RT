
# include <rt.h>

void  rt_add_neg_object(t_tag *tag, t_rt *rt)
{
	t_object	obj;

	if (RS->is_neg != 0)
		rt_exit(rt, "Negative object", "Only one is allowed.", EXIT_FAILURE);
	obj = rt_init_neg_object();
	while (TA)
	{
		if (!ft_strcmp(TA->name, "name"))
		{
			obj.name = ft_strdup(TA->value);
			rt_check_neg_obj_name(&obj, rt);
		}
		else if (!ft_strcmp(TA->name, "position"))
			obj.pos = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "direction"))
			obj.dir = vec_unit(rt_ctovec(TA->value, rt));
		else if (!ft_strcmp(TA->name, "rotation"))
			obj.rot = rt_ctovec(TA->value, rt);
		else if (!ft_strcmp(TA->name, "radius"))
			obj.size = rt_ctod(TA->value, rt);
		else if (!ft_strcmp(TA->name, "angle"))
			obj.angle = rt_ctod(TA->value, rt);
		TA = TA->next;
	}
	rt_check_neg_obj(&obj, rt);
	RS->is_neg = 1;
	RS->n_obj = obj;
}

void  rt_add_option(t_tag *tag, t_rt *rt)
{
	while(TA)
	{
		if (!ft_strcmp(TA->name, "aa"))
			RS->aa = (int)rt_ctod(TA->value, rt); //atoi
		else if (!ft_strcmp(TA->name, "amb"))
			RS->ambient = rt_ctod(TA->value, rt);
		else if (!ft_strcmp(TA->name, "stereo"))
			RS->stereo = rt_ctod(TA->value, rt);
		else if (!ft_strcmp(TA->name, "filter"))
			rt->filter = NONE_FILTER; //fnct for filters;		
		TA = TA->next;
	}
	/* filter fnct */
	if (RS->aa <= 0 || RS->aa > 9)
		rt_exit(rt, "Option: aa", "should be positive & <= 9", EXIT_FAILURE);
	if (RS->stereo < 0 || RS->stereo > 10) ///
		rt_exit(rt, "Option: Stereo", "should be positive & <= 10", EXIT_FAILURE);
	RS->ambient = ft_clamping(RS->ambient);
}
