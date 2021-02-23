#ifndef LIBVEC_H
#define LIBVEC_H

#include <libft.h>

typedef struct	s_vector
{
	double      x;
    double      y;
    double      z;
}				t_vec;

t_vec		vec(double x, double y, double z);
t_vec		vec3(double x);
t_vec		vec_unit(t_vec a);
t_vec		vec_sub(t_vec a, t_vec b);
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_prod(t_vec a, t_vec b);
t_vec		vec_pro_k(t_vec a, double k);
t_vec		vec_div(t_vec a, t_vec b);
t_vec		vec_div_k(t_vec a, double k);
t_vec       vec_cross(t_vec a, t_vec b);
double      vec_dot(t_vec a, t_vec b);
double      vec_length(t_vec a);
double      vec_lengthsquared(t_vec a);
t_vec       vec_fabs(t_vec v);

#endif