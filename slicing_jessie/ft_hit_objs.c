/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:33:48 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/10 15:13:05 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#define decoup_opt 1

void		ft_float_swap(double *a, double *b)
{
	double	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			ft_hit_disque(t_object *o, t_ray *r, t_record *rec)
{
	t_vec centre = o->pos;
	t_vec normal = o->rot;
	rec->t = ((ft_dot(normal, centre) - ft_dot(normal, r->origin)) / ft_dot(normal, r->dir));
	if (rec->t >= rec->closest || rec->t <= TMIN)
		return (0);
	t_vec point = ft_minus(ray_fctn(r, rec->t),centre);

	if (ft_lengthsquared(point) >= o->size)
		return(0);
	rec->normal = o->rot;
	/*
		 //// cross  n with r.dir 
		arcos(dot / lnght0 * length1) 
		theta = arcos (dot(n, r.dir)) [0-180] // normalser n et r.dir
		if n * r.dir > 0 ? n = n : n = -n
	*/
	rec->p = ray_fctn(r, rec->t);
	return (1);
}

int			ft_slicing(t_object *o, t_ray *r, t_record *rec)
{
	/*
		slicing for (sphere / cylinder / )
	*/

	t_vec my = ft_unit_vec(ft_minus(rec->p, ft_plus_k(o->pos, 0.5)));
	t_vec ax = ft_unit_vec(ft_vec(0, -1, 1));//
	if (ft_dot(my, ax) <= 0)
	{
		t_object plan;
		plan.pos = o->pos;
		plan.rot = ft_pro_k(ax, -1);
		rec->t = rec->sol[1];
		rec->p = ray_fctn(r, rec->t);
		t_vec my = ft_unit_vec(ft_minus(rec->p, o->pos));
		if (ft_dot(my, ax) <= 0)
			return(0);
		return(ft_hit_plan(&plan, r, rec));//remove this line if you want an empty slice
	}
	return (1);
}

int			ft_hit_sphere(t_object *sphere, t_ray *r, t_record *rec)
{
	rec->oc = ft_minus(r->origin, sphere->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir);
	rec->coef[1] = 2 * ft_dot(rec->oc, r->dir);
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(sphere->size, 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta > 0)
	{
		rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->sol[0] < rec->sol[1]) ? 0 : ft_float_swap(&rec->sol[0], &rec->sol[1]);
		if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
		{
			rec->t = rec->sol[0];
			rec->p = ray_fctn(r, rec->t);
			rec->normal = ft_div_k(ft_minus(rec->p, sphere->pos), sphere->size);
			if (/*o.slice = 1 && */ft_slicing(sphere, r, rec) == 0)
				return 0;
			return (1);
		}
	}
	return (0);
}
/*
int			ft_hit_plan(t_object *o, t_ray *r, t_record *rec)
{
	//double rayon_c = 4;
	t_vec centre = o->pos; //centre howa la point critique dial cylindre && la meme + hight * (vec.unit.rot dial cylindre)
	t_vec normal = o->rot; //le normal de cylindre
	rec->t = ((ft_dot(normal, centre) - ft_dot(normal, r->origin)) / ft_dot(normal, r->dir));
	if (rec->t >= rec->closest || rec->t <= TMIN)
		return (0);
	t_vec point = ft_minus(ray_fctn(r, rec->t),centre);

	if (ft_lengthsquared(point) >= (double)16) //16 howa rayon^2
		return(0);
	rec->normal = o->rot;
	rec->p = ray_fctn(r, rec->t);
	return (1);
}*/
/*
int			ft_hit_plan(t_object *o, t_ray *r, t_record *rec)
{
	(void)o;
	t_vec p0 = ft_vec(0, 0, 0);
	t_vec p1 = ft_vec(1, 0, 0);
	t_vec p2 = ft_vec(1, 1, 0);
	t_vec edgeA = ft_minus(p1, p0);
	t_vec edgeB = ft_minus(p2, p0);
	t_vec edgeC = ft_minus(p1, p2);
	t_vec normal = ft_cross(edgeA, edgeB);
	
	t_vec centre = o->pos;
	t_vec normal = o->rot;
	rec->t = ((ft_dot(normal, centre) - ft_dot(normal, r->origin)) / ft_dot(normal, r->dir));
	if (rec->t >= rec->closest || rec->t <= TMIN)
		return (0);
	rec->normal = o->rot;
	rec->p = ray_fctn(r, rec->t);
	
	float d = ft_dot(normal, p0); //is the distance from the origin (0, 0, 0) to the plane (if we trace a line from the origin to the plane, parallel to the plane's normal).
	float t = -1 * ((ft_dot(normal, r->origin) + d) / ft_dot(normal, r->dir));
	t_vec p = ray_fctn(r, rec->t);
	t_vec c0 = ft_minus(p, p0);
	t_vec c1 = ft_minus(p, p1);
	t_vec c2 = ft_minus(p, p1);
	if (ft_dot(normal, ft_cross(edgeA, c0)) > 0 && ft_dot(normal, ft_cross(edgeB, c1)) > 0 && ft_dot(normal, ft_cross(edgeC, c2)) <= 0)
		return 0; // P is outside the triangle
	rec->t = t;
	if (rec->t >= rec->closest || rec->t <= TMIN || rec->t < 0) // behind the camera
		return (0);
	rec->normal = normal;
	rec->p = p;
	return (1);
}*/

int			ft_hit_plan(t_object *o, t_ray *r, t_record *rec)
{
	rec->t = ((ft_dot(o->rot, o->pos) - ft_dot(o->rot, r->origin))
			/ ft_dot(o->rot, r->dir));
	if (rec->t >= rec->closest || rec->t <= TMIN)
		return (0);
	rec->normal = o->rot;
	rec->p = ray_fctn(r, rec->t);
	return (1);
}


int			ft_hit_cylinder(t_object *o, t_ray *r, t_record *rec)
{

	rec->oc = ft_minus(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (ft_dot(r->dir, o->rot)
				* ft_dot(rec->oc, o->rot)));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - pow(ft_dot(rec->oc, o->rot), 2)
		- o->size * o->size;
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta >= 0)
	{
		rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
		rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
		(rec->sol[0] < rec->sol[1]) ? 0 : ft_float_swap(&rec->sol[0], &rec->sol[1]);
		if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
		{

			rec->normal = ft_unit_vec(ft_minus(ft_minus(rec->p, o->pos), ft_pro_k(o->rot, ft_dot(r->dir, o->rot) * rec->t + ft_dot(rec->oc, o->rot))));
			if (ft_slicing(o, r, rec) == 0) // o.sli = 1
				return 0;
			return (1);
		}
	}
	return (0);
	
}



int			ft_hit_cone(t_object *o, t_ray *r, t_record *rec)
{
	rec->oc = ft_minus(r->origin, o->pos);
	rec->coef[0] = ft_dot(r->dir, r->dir) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(r->dir, o->rot), 2);
	rec->coef[1] = 2 * (ft_dot(r->dir, rec->oc) - (1 + pow(tan(o->size), 2))
			* ft_dot(r->dir, o->rot) * ft_dot(rec->oc, o->rot));
	rec->coef[2] = ft_dot(rec->oc, rec->oc) - (1 + pow(tan(o->size), 2))
		* pow(ft_dot(rec->oc, o->rot), 2);
	rec->delta = rec->coef[1] * rec->coef[1] - 4 * rec->coef[0] * rec->coef[2];
	if (rec->delta < 0)
		return (0);
	rec->sol[0] = (-rec->coef[1] - sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->sol[1] = (-rec->coef[1] + sqrt(rec->delta)) / (2 * rec->coef[0]);
	rec->sol[0] = (rec->sol[0] > TMIN && rec->sol[0] < rec->sol[1]) ?
					rec->sol[0] : rec->sol[1];
	if (rec->sol[0] < rec->closest && rec->sol[0] > TMIN)
	{
		rec->t = rec->sol[0];
		rec->p = ray_fctn(r, rec->t);
		rec->tmp = ft_pro_k(o->rot, (ft_dot(r->dir, o->rot) * rec->t
					+ ft_dot(rec->oc, o->rot)));
		rec->tmp = ft_pro_k(rec->tmp, (1 + pow(tan(o->size), 2)));
		double m = ft_dot(r->dir, o->rot) * rec->t + ft_dot(rec->oc, o->rot);
		rec->normal = ft_unit_vec(ft_minus(ft_minus(rec->p, o->pos), rec->tmp));
		if (m < -1 || m > 2) //(-1 < m < 2) decide the first and the second cap //cap1 p=A(cone convex)+unit(dir(cone))*hight(-1) rayon=tan(o->size()) * abs(hight(-1)) //cap2 p=A(cone convex)+unit(dir(cone))*hight(2) rayon=tan(o->size()) * hight(2)
		{
			return (0);
		}
		return (1);
	}
	return (0);
}
