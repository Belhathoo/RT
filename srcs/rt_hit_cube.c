
#include <rt.h>

int				rt_hit_cube(t_object *o, t_ray *r,  t_hit *rec)
{
	t_object	*oo;
	double		closest;
	int			check_hit;

	check_hit = 0;
	closest = MAX;
	oo = o;
	o = o->compos;
	while (o)
	{
		if (o->hit(o, r, rec))
		{
			check_hit = 1;
			closest = rec->t;
			rec->curr_obj = oo;
			rec->ray = r;
		}
		o = o->compos;
	}
	return (check_hit);
}

//  void			rt_check(t_object *compos, t_object *obj, int x)
// {
// 	if (x == 0)
// 		compos = x_zero(compos, obj);
// 	else if (x == 1)
// 		compos = x_un(compos, obj);
// 	else if (x == 2)
// 		compos = x_deux(compos, obj);
// 	else if (x == 3)
// 		compos = x_trois(compos, obj);
// 	else if (x == 4)
// 		compos = x_quatre(compos, obj);
// }

// void			add_compos(t_object *o, t_vec r, int x, t_object *head)
// {
// 	if (!(o->compos = (struct s_o *)malloc(sizeof(struct s_o))))
// 		rt_perror();
	
// 	o->compos->pos.x = head->pos.x + r.x;
// 	o->compos->pos.y= head->pos.y+ r.y;
// 	o->compos->pos.z = head->pos.z + r.z;
// 	o->compos->col = o->col;
// 	o->compos->hit = rt_hit_plan;
// 	o->compos->name = ft_strdup(o->name);
//     rt_check(o->compos, head, x);
// 	o->compos->compos = NULL;
// 	o->compos->next = NULL;
// }


static void		dup_cube(t_object *obj, int cas)
{
	if (!(obj->compos = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();

	obj->compos->col = obj->col;
    obj->compos->vec1 = obj->vec1;
	obj->compos->vec2 = obj->vec2;
	obj->compos->hit = rt_hit_plan;
	if (cas == 1)
	{
        obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->rot, 1.0 * 4.0));
		obj->compos->rot = obj->rot;
	}
	else if (cas == 2)
	{
		obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->rot, -1.0 * 4.0));
		obj->compos->rot = vec_pro_k(obj->rot, -1.0);
	}
	obj->compos->compos = NULL;
	obj->compos->next = NULL;
}


static void		dup_cube2(t_object *obj, int cas)
{
	if (!(obj->compos = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();
	obj->compos->col = obj->col;
	obj->compos->vec1 = obj->rot;
	obj->compos->vec2 = obj->vec1;
	obj->compos->hit = rt_hit_plan;
	if (cas == 3)
	{
		obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->vec2, 1.0 * 4.0));
		obj->compos->rot = vec_pro_k(obj->vec2, -1.0);
	}
	else if (cas == 4)
	{
		obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->vec2, -1.0 * 4.0));
		obj->compos->rot = vec_pro_k(obj->vec2, -1.0);
	}
	obj->compos->compos = NULL;   
	obj->compos->next = NULL;
}

static void		dup_cube3(t_object *obj, int cas)
{
	if (!(obj->compos = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();
	obj->compos->col = obj->col;
    obj->compos->vec1 = obj->vec2;
	obj->compos->vec2 = obj->rot;
	obj->compos->hit = rt_hit_plan;
	if (cas == 5)
	{
		obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->vec1, 1.0 * 4.0));
		obj->compos->rot = vec_pro_k(obj->vec1, 1.0);
	}
	else if (cas == 6)
	{
		obj->compos->pos = vec_add(obj->pos, vec_pro_k(obj->vec1, -1.0 * 4.0));
		obj->compos->rot = vec_pro_k(obj->vec1, -1.0);
	}
  obj->compos->compos = NULL;
  obj->compos->next = NULL;
}

void		get_cube_compos(t_object *obj)
{
    printf("%f %f %f", obj->vec2.x, obj->vec2.y, obj->vec2.z);
	dup_cube(obj, 1);
	dup_cube(obj->compos, 2);
	dup_cube2(obj->compos->compos, 3);
	dup_cube2(obj->compos->compos->compos, 4);
	dup_cube3(obj->compos->compos->compos->compos, 5);
	dup_cube3(obj->compos->compos->compos->compos->compos, 6);
	obj->compos->compos->compos->compos->compos->compos = NULL;
}




// void    get_cube_compos(t_object *obj)
// {
//     add_compos(obj, vec_add(obj->pos, vec_pro_k(obj->rot, 2.0)), 0, obj);
// 	add_compos(obj->compos, vec_add(obj->pos, vec_pro_k(obj->rot, -2.0)), 0, obj);
// 	add_compos(obj->compos->compos, vec_add(obj->pos, vec_pro_k(obj->vec2, 2.0)), 1, obj);
// 	add_compos(obj->compos->compos->compos, vec_add(obj->pos, vec_pro_k(obj->vec2, -2.0)), 1, obj);
// 	add_compos(obj->compos->compos->compos->compos,
// 			vec_add(obj->pos, vec_pro_k(obj->vec1, 2.0)), 4, obj);
// 	add_compos(obj->compos->compos->compos->compos->compos,
// 			vec_add(obj->pos, vec_pro_k(obj->vec1, -2.0)), 4, obj);
//   obj->compos->compos->compos->compos->compos->compos->compos = NULL;
// }

