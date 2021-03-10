#include <rt.h>

// void		rt_perror(void)
// {
// 	perror("error: ");
// 	//exit with rt_exit
// 	exit(EXIT_FAILURE);
// }

int				rt_hit_glasse(t_object *obj, t_ray *r,  t_hit *rec)
{
	t_object	*o;
	double		closest;
	int			check_hit;
	t_hit		record;

	check_hit = 0;
	o = obj->compos;
	record.closest = rec->closest;;
	record.curr_obj = NULL;
	while (o)
	{
		if (o->hit(o, r, &record))
		{
			check_hit = 1;
			record.closest = record.t;
			record.curr_obj = o;
			record.ray = r;
			*rec = record;
		}
		o = o->compos;
	}
	return (check_hit);
}

// static void     add_cylinder_compos(t_object *obj, t_object **comp)
// {
  
//     if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
// 		rt_perror();
//      (*comp)->col = obj->col;
//      (*comp)->rot = obj->rot;
//      (*comp)->height =  fabs(obj->height);
//      (*comp)->width =  obj->width;
//       (*comp)->size = obj->size ;
//      (*comp)->pos = obj->pos;
//      (*comp)->hit = rt_hit_lcylinder;
//      (*comp)->vec1 = obj->vec1;
//      (*comp)->vec2 = obj->vec2;
//      (*comp)->compos = NULL;   
// 	 (*comp)->next = NULL;
// }

// static void     add_pcone_compos(t_object *obj, t_object **comp)
// {
//     if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
// 		rt_perror();
//     (*comp)->col = obj->col;
//     (*comp)->rot = obj->rot;
//     (*comp)->height =  obj->height;
//     (*comp)->width = obj->width;
//     (*comp)->angle = obj->angle;
//     (*comp)->pos = obj->pos; //vec_pro_k(obj->pos, obj->height);
//     (*comp)->hit = rt_hit_lcone;
//     (*comp)->vec1 = obj->vec1;
//     (*comp)->vec2 = obj->vec2;
//     (*comp)->compos = NULL;   
// 	   (*comp)->next = NULL;
// }

// static void     add_gcone_compos(t_object *obj, t_object **comp)
// {
//     if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
// 		rt_perror();
//     (*comp)->col = vec(5.0, 0.0, 1.3);
//     (*comp)->rot = vec_pro_k(obj->rot, -1.0);
//     (*comp)->height =  obj->height;
//      (*comp)->width = obj->width;
//     (*comp)->size = 5.0;
//     (*comp)->angle = obj->angle * 3.0;
//     (*comp)->pos = obj->pos; //vec_pro_k(obj->pos, -1.0 * obj->height);
//     (*comp)->hit = rt_hit_lcone;
//     (*comp)->vec1 = obj->vec1;
//     (*comp)->vec2 = obj->vec2;
//     (*comp)->compos = NULL;   
// 	(*comp)->next = NULL;
// }

// void        get_glasse_compos(t_object *obj)
// {
//     add_cylinder_compos(obj, &(obj->compos));
//     add_pcone_compos(obj, &(obj->compos));
//     add_gcone_compos(obj, &(obj->compos->compos));
//     obj->compos->compos->compos = NULL;
// }