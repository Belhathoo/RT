/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light_ref.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:54:33 by belhatho          #+#    #+#             */
/*   Updated: 2021/02/18 15:54:49 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>

t_vec		rt_reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_pro_k(vec_pro_k(n, 2), vec_dot(v, n))));
}

#define	N1 1.00029

float	rt_fresnel_ref(float ior, float n1, t_vec n, t_vec d)
{
	float	ret;
	float	x, y;
	float	cs;


	x = (ior - n1) / (n1 + ior);
	cs = -vec_dot(n, d);
	if (ior > n1)
	{
		y = ior / n1;
		y = y * y * (1.0 - cs*cs);

		if (y > 1.0)
			return (1.0);
		cs = sqrt(1 - y);
	}
	y = 1.0 - cs;
	ret = x + (1 - x) * y*y*y*y*y;

	ret = n1 + (1.0 - n1) * ret;
	return (ret);
}

t_vec       rt_refract(t_vec i, t_vec n, float n1, float n2)
{
    t_vec   ret;
    float   ior;

    ior = n1 / n2;
    // ior = rt_fresnel_ref(n1, n2, n, i);
    ret = vec_pro_k(n, ior * vec_dot(n, i) - sqrt(1 - ior*ior * (1-vec_dot(n, i))*(1-vec_dot(n, i))));
    ret = vec_add(vec_pro_k(i, ior), ret);
    return (ret);
}



void        rt_check_l_ref(t_thread *th, t_ray *r, t_object *o, int depth)
{
		t_ray       rf;
		t_ray       rt;
        t_vec       color;

        color = th->rec.col; 
		if (depth > 1  && o->mat.kr > 0)
		{
			rf.dir = rt_reflect(r->dir, th->rec.n);
			rf.origin = vec_add(th->rec.p, vec_pro_k(rf.dir, 0.001));

			color = vec_add(color, vec_pro_k(rt_raytracer(th, &rf, depth - 1), o->mat.kr));
			// color = vec_add(color, vec_pro_k(rt_raytracer(th, &rf, depth -1),\
			// 	rt_fresnel_ref(o, 1.125, th->rec.n, rf.dir)));
		}
        if (depth > 1  && o->mat.kt > 0)
		{
			rt.dir = rt_refract(r->dir, th->rec.n, N1, o->mat.kt);
			rt.origin = vec_add(th->rec.p, vec_pro_k(rf.dir, 0.001));

            color = rt_raytracer(th, &rt, depth - 1);
            if (th->rec.curr_obj != o)
			    color = vec_add(color, vec_pro_k(rt_raytracer(th, &rf, depth -1), o->mat.kt));
				    // ,rt_fresnel_ref(N1, o->mat.kt, th->rec.n, rf.dir)));
            else
            {
                /// print direction refacted ray !!! recheck -- close to work ^^
                
                rt_check_l_ref(th, &rt, th->rec.curr_obj, depth - 1);
                // depth--;
                // color = th->rec.curr_obj->col;
            }
		}
        th->rec.col = color;
}