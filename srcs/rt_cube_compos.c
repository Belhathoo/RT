/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cube_compos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:18:10 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 15:18:14 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/* rotation from parse baa9**/
void			rt_init_compos(t_object *obj, t_object *comp)
{
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
	comp->next = NULL;
	comp->compos = NULL;
}

static void		get_cube_compos1(t_object *obj, t_object **comp, int side\
				, t_rt *rt)
{
	if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_exit(rt, "Cannote allocate", "", EXIT_FAILURE);
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

static void		get_cube_compos2(t_object *obj, t_object **comp, int side\
				, t_rt *rt)
{
	if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_exit(rt, "Cannote allocate", "", EXIT_FAILURE);
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
		(*comp)->pos = vec_add(obj->pos,\
			vec_pro_k(obj->vec2, -1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec2, -1.0);
	}
	(*comp)->compos = NULL;
	(*comp)->next = NULL;
}

static void		get_cube_compos3(t_object *obj, t_object **comp, int side\
					, t_rt *rt)
{
	if (!(*comp = (struct s_o *)malloc(sizeof(struct s_o))))
		rt_exit(rt, "Cannote allocate", "", EXIT_FAILURE);
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
		(*comp)->pos = vec_add(obj->pos\
			, vec_pro_k(obj->vec1, -1.0 * obj->dist));
		(*comp)->rot = vec_pro_k(obj->vec1, -1.0);
	}
	(*comp)->compos = NULL;
	(*comp)->next = NULL;
}

void			get_cube_compos(t_object *obj, t_rt *rt)
{
	obj->dist = obj->size;
	get_cube_compos1(obj, &(obj->compos), 1, rt);
	get_cube_compos1(obj, &(obj->compos->compos), 2, rt);
	get_cube_compos2(obj, &(obj->compos->compos->compos), 3, rt);
	get_cube_compos2(obj, &(obj->compos->compos->compos->compos), 4, rt);
	get_cube_compos3(obj,\
						&(obj->compos->compos->compos->compos->compos), 5, rt);
	get_cube_compos3(obj,\
				&(obj->compos->compos->compos->compos->compos->compos), 6, rt);
	obj->compos->compos->compos->compos->compos->compos->compos = NULL;
}
