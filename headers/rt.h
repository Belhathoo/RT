/* ************************************************************************** */

#ifndef RT_H
# define RT_H

//# include <SDL.h>

# include <rt_struct.h>
# include <rt_define.h>

#include<stdio.h> /// // 



/* Tmp Parse  */

t_vec			rt_ctovec(char *str, t_rt *rt);
double			rt_ctod(char *str, t_rt *rt);
t_texture   	*rt_ctotxt(char *str, t_rt *rt);

void			ft_parser(char *file, t_rt *p);
void			rt_parser(t_rt *p, char **av);
void			ft_get_data(t_rt *p, int fd);
int				ft_fr(char **str);

/*************/
/*
 * Raytracer
 */
t_ray			rt_ray(t_vec a, t_vec b);
t_vec 			rt_raytracer(t_thread *t, t_ray *r, int d);
t_vec 			rt_anti_aliasing(t_thread *t, int col, int row);
void			*rt_run(t_thread *t);
void			rt_start(t_rt *rt);
int				rt_draw(t_rt *rt);

/*
 * Lighting
 */

void			ft_ambient(t_light *l, t_thread *th, t_vec *col);
int				ft_shading(t_thread *th, t_vec lo);
int				rt_lighting(t_thread *th, t_light *t);
t_vec			ft_reflect(t_vec v, t_vec n);

/*
 * Hit
 */

int				rt_hit_sphere(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_cone(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_plan(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit(t_scene *scene, t_ray *r, t_hit *record);
int				rt_hit_torus(t_object *obj, t_ray *ray, t_hit *record);
int             rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record);
int     		rt_hit_cube(t_object *oo, t_ray *r, t_hit *record);

/*
 * Utils
 */

t_vec			vec_ray(t_ray *r, double t);
t_vec			rt_int_to_rgb(int x);
void			rt_adjustment(t_vec *c);
int				rt_rgb_to_int(t_vec c);
void			rt_mlx_putpixel(t_rt *rt, int x, int y, int color);
int				rt_check_distance(t_object *obj, double c[5], t_hit *rec, t_ray *ray);
int				rt_solve_quartic(double w[5], double s[4]);
static int		rt_case_two(double coeffs[4], double s[4], t_quartic *q);
static int		rt_case_norm(t_quartic *q);
static int		rt_case_one(double coeffs[4], double s[4], double *q,
				double *p);
int				rt_solve_cubic(double w[4], double s[3]);
static int		rt_case_3(double s[3], double *q, double *d);
static int		rt_case_2(double s[3], double *q, double *p,
				double *cb_p);
static int		rt_case_1(double s[2], double *q);
int				rt_solve_quadric(double w[3], double s[2]);
int				rt_is_zero(double delta);
void			add_compos(t_object *o, t_vec r, int x, t_object *head);
void			add_aux_o(t_object *o, t_vec r, int x, t_object *head);
void    		get_cube_compos(t_object *obj);
void			rt_check(t_object *compos, t_object *obj, int x);
void  			add_(t_object *o);
t_object		*x_zero(t_object *compos, t_object *obj);
t_object		*x_un(t_object *compos, t_object *obj);
t_object		*x_deux(t_object *compos, t_object *obj);
t_object		*x_trois(t_object *compos, t_object *obj);
t_object		*x_quatre(t_object *compos, t_object *obj);

void			rt_get_repere(t_scene *scene);

/*
* Textures
*/

t_texture		*rt_init_txt(t_rt *rt);
//t_vec   		rt_texture(double u, double v);
t_vec			rt_txt_damier(t_hit *rec);
int				rt_load_txt(t_rt *rt, t_object *o);
t_vec			rt_get_color_from_texture(t_object *o, double *u, double *v);
t_vec  			torus_txt(t_hit *rec);


/*
 * Events
 */

int				rt_mouse(int button, int x, int y, t_rt *rt);
int				rt_keys(int key, t_rt *rt);

/*
 * Init
 */
t_scene			*rt_init_scene(void);
t_object		*rt_init_object(void);
t_light			*rt_init_light(void);
t_camera		rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov);
void			rt_init(t_rt *rt);

/*
 * Close
 */

void			rt_perror(void);
void			rt_exit(t_rt *rt, char *msg, int err);
int				rt_close(t_rt *rt);

#endif
