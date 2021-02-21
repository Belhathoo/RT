
#include <rt.h>


static void		rt_set_minedgedistance(t_cell *c, t_cell *tmp, float minedgedistance)
{
	tmp->tocenter = vec_pro_k(vec_add(c->toclosest, tmp->tocell), 0.5);
	tmp->celldifference = vec_unit(vec_sub(tmp->tocell, c->toclosest));
	tmp->edgedistance = vec_dot(tmp->tocenter, tmp->celldifference);
	minedgedistance = fmin(minedgedistance, tmp->edgedistance);
}
static void		rt_third_voronoi(t_cell *cell, t_vec p)
{
   	t_cell	tmp;
	int		i[3];
	t_vec  cellposition; 

	i[0] = -2;
	while (++i[0] <= 1)
	{
		i[1] = -2;
		while (++i[1] <= 1)
		{
			i[2] = -2;
			while (++i[2] <= 1)
			{
				tmp.cell = vec_add(cell->base, vec(i[0], i[1], i[2]));
				cellposition = vec_add(tmp.cell, rt_rand3dto3d(tmp.cell));
				tmp.tocell = vec_sub(cellposition, p);
				tmp.diff = vec_fabs(vec_sub(cell->closest, tmp.cell));
				if (tmp.diff.x + tmp.diff.y + tmp.diff.z >= 0.1)
				 {
				    tmp.tocenter = vec_pro_k(vec_add(cell->toclosest, tmp.tocell), 0.5);
				   	tmp.celldifference = vec_unit(vec_sub(tmp.tocell, cell->toclosest));
					tmp.edgedistance = vec_dot(tmp.tocenter, tmp.celldifference);
					tmp.minedgedistance = fmin(tmp.minedgedistance, tmp.edgedistance);
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
				tmp.closest = vec_add(c->base, vec(i[0], i[1], i[2]));
				cellposition = vec_add(tmp.closest, rt_rand3dto3d(tmp.closest));
				tmp.toclosest = vec_sub(cellposition, p);
				tmp.mindistocell = vec_length(tmp.toclosest);
				if (tmp.mindistocell < c->mindistocell)
					*c = tmp;
            }
        }
    }
} 

t_vec  rt_voronoi(t_vec p,  t_object *o)
{
    t_cell cell;
   double  random;

   cell.base = vec_floor(p);
   cell.mindistocell = 10.0;
   cell.minedgedistance = 10.0;
  if (o->noi.type == VORONOI1)  
      rt_first_voronoi(&cell, p);
  else if (o->noi.type == VORONOI2) 
  	 rt_third_voronoi(&cell, p);   
   random = rt_rand3dto1d(cell.closest, vec(12.9898, 78.233, 37.719));
	return (vec(cell.mindistocell, random, cell.minedgedistance));
}

t_vec   rt_start_voronoi(t_vec p, t_object *o)
{
   t_voronoi voronoi;

   voronoi.p = vec_div_k(p, o->noi.scale1);//o->noise->scale
   voronoi.noise_v = rt_voronoi(voronoi.p, o);
  if (o->noi.type == VORONOI1)
    return(vec(voronoi.noise_v.y + voronoi.noise_v.x, \
    voronoi.noise_v.y + voronoi.noise_v.x, \
	voronoi.noise_v.y + voronoi.noise_v.x));
 else //if (o->noi.type == VORONOI2)
    return (vec(voronoi.noise_v.y, voronoi.noise_v.y,\
	voronoi.noise_v.y));
//  else if (o->noi.type == VORONOI3)
//    return (vec());
}
