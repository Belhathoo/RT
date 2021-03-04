
#include <rt.h>

static void		rt_second_voronoi(t_cell *cell, t_vec p)
{
   	t_cell	tmp;
	int		i[3];
	t_vec  cellposition; 

	i[0] = -1;
	while (++i[0] <= 2)
	{
		i[1] = -1;
		while (++i[1] <= 2)
		{
			i[2] = -1;
			while (++i[2] <= 2)
			{
				tmp.closest = vec_add(cell->base, vec(i[0], i[1], i[2]));
				cellposition = vec_add(tmp.closest, rt_rand3dto3d(tmp.closest));
				tmp.toclosest = vec_sub(cellposition, p);
				tmp.diff = vec_fabs(vec_sub(cell->closest, tmp.closest));
				if (tmp.diff.x + tmp.diff.y + tmp.diff.z >= 0.1)
				 {
				    tmp.tocenter = vec_pro_k(vec_add(cell->toclosest, tmp.toclosest), 0.5);
				   	tmp.celldifference = vec_unit(vec_sub(tmp.toclosest, cell->toclosest));
					tmp.edgedistance = vec_dot(tmp.tocenter, tmp.celldifference);
					tmp.minedgedistance = fmin(cell->minedgedistance, tmp.edgedistance);
					*cell = tmp;
				}
					
			}
		}
	}
}

static void     rt_first_voronoi(t_cell *c, t_vec p)
{
   t_cell		tmp;
	t_vec	cellposition;
    int     i[3];

	i[0] = -2;
	while (++i[0] <= 1)
	{
		i[1] = -2;
		while (++i[1] <= 1)
		{
			i[2] = -2;
			while (++i[2] <= 1)
			{
				tmp.base = c->base;
				tmp.closest = vec_add(tmp.base, vec(i[0], i[1], i[2]));
				cellposition = vec_add(tmp.closest, rt_rand3dto3d(tmp.closest));
				tmp.toclosest = vec_sub(cellposition, p);
				tmp.mindistocell = vec_length(tmp.toclosest);
				if (tmp.mindistocell < c->mindistocell)
					*c = tmp;
            }
        }
    }
} 

t_vec  rt_start_voronoi(t_vec p,  t_object *o)
{
    t_cell cell;
   double  random;

   cell.base = vec_floor(p);
   cell.mindistocell = 10.0;
    rt_first_voronoi(&cell, p);
	cell.minedgedistance = 10.0;
   if (o->noi.type != VORONOI1 && o->noi.type != VORONOI2)   
  	 rt_second_voronoi(&cell, p);
   random = rt_rand3dto1d(cell.closest, vec(12.9898, 78.233, 37.719));
	return (vec(cell.mindistocell, random, cell.minedgedistance));
}

static void   	rt_surf(t_voronoi *v, t_object *o)
{
  
    v->cellcolor = rt_rand1dto3d(v->noise_v.y); 
    v->valuechange = vec_length(v->p) * 0.5;
    v->isborder = 1 - rt_smoothstep( o->scale - \
	v->valuechange, o->scale + v->valuechange, \
	v->noise_v.z);
	v->fcolor =  rt_lerp(v->cellcolor, vec(1, 1, 1), 0.0);
	v->ffcol = rt_lerp(v->cellcolor, vec(0, 0, 0),\
	rt_step(v->noise_v.z, o->scale));
	v->fcol =  rt_lerp(v->cellcolor, vec(0, 0, 0), v->isborder);
}

t_vec   rt_voronoi(t_vec p, t_object *o)
{
   t_voronoi voronoi;

   voronoi.p = vec_div_k(p, o->scale);
   voronoi.noise_v = rt_start_voronoi(voronoi.p, o);
    rt_surf(&voronoi, o);
   if (o->noi.type == VORONOI1)
	  return (voronoi.fcolor);
  	else if (o->noi.type == VORONOI2)
	return (vec(voronoi.fcolor.y, voronoi.fcolor.y, \
			voronoi.fcolor.y));
	   	else if (o->noi.type == VORONOI3)
	 return (vec(voronoi.fcol.x + voronoi.fcol.z, voronoi.fcol.x + voronoi.fcol.z,\
	  voronoi.fcol.x + voronoi.fcol.z));
	 else
	 	return (vec_prod(o->col, vec(voronoi.fcolor.y, voronoi.fcolor.y, \
			voronoi.fcolor.y)));
}