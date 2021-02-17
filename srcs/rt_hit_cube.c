
#include <rt.h>

int				rt_hit_cube(t_object *obj, t_ray *r,  t_hit *rec)
{
	t_object	*o;
	double		closest;
	int			check_hit;

	check_hit = 0;
	o = obj->compos;
	
	while (o)
	{
		if (o->hit(o, r, rec))
		{
			check_hit = 1;
			rec->closest = rec->t;
			rec->curr_obj = o;
			rec->ray = r;
		}
		o = o->compos;
	}
	return (check_hit);
}

void	rt_init_compos(t_object *obj, t_object *comp)
{
	//////////
	comp->name = NULL;
	comp->material = NULL;
	comp->pos = obj->pos;
	comp->dir = obj->dir;
	comp->rot = obj->rot;
	comp->col = obj->col;
	comp->noi = obj->noi;
	comp->txt = obj->txt;
	comp->mat = obj->mat;
	comp->size = obj->size;
	// comp->width = obj->width;
	// comp->height = obj->height;
	// comp->dist = 1.0; maybe needed for composed objs != cube !!!!
	comp->next = NULL;
	comp->compos = NULL;
}

static void		get_cube_compos1(t_object *obj, t_object **comp, int side)
{
	if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();
	rt_init_compos(obj, *comp);
	(*comp)->vec1 = obj->vec1;
	(*comp)->vec2 = obj->vec2;
	(*comp)->hit = rt_hit_care;
	if (side == 1)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->rot, 1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->rot, 1.0);
	}
	else if (side == 2)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->rot, -1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->rot, -1.0);
	}
	(*comp)->compos = NULL;
	(*comp)->next = NULL;
}


static void	get_cube_compos2(t_object *obj, t_object **comp, int side)
{
	if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();
	rt_init_compos(obj, *comp);
	(*comp)->vec1 = obj->rot;
	(*comp)->vec2 = obj->vec1;
	(*comp)->hit = rt_hit_care;
	if (side == 3)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->vec2, 1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec2, 1.0);
	} 
	else if (side == 4)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->vec2, -1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec2, -1.0);
	}
	(*comp)->compos = NULL;   
	(*comp)->next = NULL;
}

static void		get_cube_compos3(t_object *obj, t_object **comp, int side)
{
	if (!( *comp  = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_perror();
	rt_init_compos(obj, *comp);
	(*comp)->vec1 = obj->vec2;
	(*comp)->vec2 = obj->rot;
	(*comp)->hit = rt_hit_care;
	if (side == 5)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->vec1, 1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec1, 1.0);
	}
	else if (side == 6)
	{
		(*comp)->pos = vec_add(obj->pos, vec_pro_k(obj->vec1, -1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec1, -1.0);
	}
	(*comp)->compos = NULL;
	(*comp)->next = NULL;
}

void		get_cube_compos(t_object *obj)
{
	obj->dist = obj->size;
	get_cube_compos1(obj, &(obj->compos), 1);
	get_cube_compos1(obj, &(obj->compos->compos), 2);
	get_cube_compos2(obj, &(obj->compos->compos->compos), 3);
	get_cube_compos2(obj, &(obj->compos->compos->compos->compos), 4);
	get_cube_compos3(obj, &(obj->compos->compos->compos->compos->compos), 5);
	get_cube_compos3(obj, &(obj->compos->compos->compos->compos->compos->compos), 6);
	obj->compos->compos->compos->compos->compos->compos->compos = NULL;
}
