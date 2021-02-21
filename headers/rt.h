/* ************************************************************************** */

#ifndef RT_H
# define RT_H

//# include <SDL.h>

# include <rt_struct.h>
# include <rt_define.h>

#include<stdio.h> /// // 



/* Tmp Parse  */

void			rt_rot_dir(t_vec *d, t_vec r);
t_vec			rt_ctovec(char *str, t_rt *rt);
double			rt_ctod(char *str, t_rt *rt);
t_texture   	*rt_ctotxt(char *str, t_rt *rt);
t_noise			rt_add_noise(char *val, t_rt *rt);

void			rt_parser(t_rt *p, char **av);
void			rt_check_cam(t_camera c, t_rt *rt);
void			rt_check_obj(t_object *o, t_rt *rt);
void			rt_check_obj_name(t_object *obj, t_rt *rt);
void			rt_check_lights(t_light *l, t_rt *rt);

void			ft_parser(char *file, t_rt *p);
void			ft_get_data(t_rt *p, int fd);
int				ft_fr(char **str);

/*************/
/*
 * Raytracer
 */
t_ray			rt_ray(t_vec a, t_vec b);
t_ray			rt_get_ray(t_camera *p, double u, double v);
t_vec 			rt_raytracer(t_thread *t, t_ray *r, int d);
t_vec 			rt_anti_aliasing(t_thread *t, int col, int row);
void			*rt_run(t_thread *t);
void			rt_start(t_rt *rt);
int				rt_draw(t_rt *rt);

/*
 * Lighting
*/

void			rt_ambient(t_light *l, t_thread *th, t_vec *col);
int				rt_shading(t_thread *th, t_vec lo);
int				rt_lighting(t_thread *th, t_light *t);
t_vec			rt_reflect(t_vec v, t_vec n);

float           rt_fresnel_ref(float ior, float n1, t_vec n, t_vec d);
void            rt_check_l_ref(t_thread *th, t_ray *r, t_object *o, t_vec *c, int depth);

/*
 * Hit
*/

int				rt_hit_sphere(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_l_cylinder(t_object *o, t_ray *r, t_hit *rec);
int				rt_hit_cone(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_l_cone(t_object *o, t_ray *r, t_hit *rec);
int				rt_hit_plan(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_care(t_object *o, t_ray *ray, t_hit *rec);

int				rt_hit(t_scene *scene, t_ray *r, t_hit *record);
int				rt_hit_torus(t_object *obj, t_ray *ray, t_hit *record);
int             rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record);
int     		rt_hit_cube(t_object *oo, t_ray *r, t_hit *record);

int				rt_slicing(t_object *o, t_ray *r, t_hit *rec);

/*
 * Utils
*/

double          ffmax(double a, double b);
t_vec			vec_ray(t_ray *r, double t);
t_vec			rt_int_to_rgb(int x);
void			rt_adjustment(t_vec *c);
int				rt_rgb_to_int(t_vec c);
void			rt_mlx_putpixel(t_rt *rt, int x, int y, int color);
int				rt_check_distance(t_object *obj, double c[5], t_hit *rec, t_ray *ray);
int				rt_solve_quartic(double w[5], double s[4]);
int				rt_solve_cubic(double w[4], double s[3]);
int				rt_solve_quadric(double w[3], double s[2]);
int				rt_is_zero(double delta);
void			add_compos(t_object *o, t_vec r, int x, t_object *head);
void			add_aux_o(t_object *o, t_vec r, int x, t_object *head);
void    		get_cube_compos(t_object *obj);
void			rt_check(t_object *compos, t_object *obj, int x);
t_object		*x_zero(t_object *compos, t_object *obj);
t_object		*x_un(t_object *compos, t_object *obj);
t_object		*x_deux(t_object *compos, t_object *obj);
t_object		*x_trois(t_object *compos, t_object *obj);
t_object		*x_quatre(t_object *compos, t_object *obj);

void		ft_float_swap(double *a, double *b);

void			rt_get_repere(t_object *ob);

/*
* Textures && Noises
*/

t_texture		*rt_init_txt(t_rt *rt);
//t_vec   		rt_texture(double u, double v);
int				rt_load_txt(t_rt *rt, t_object *o);
t_vec			rt_get_color_from_texture(t_object *o, double *u, double *v);
t_vec  			torus_txt(t_hit *rec);

t_vec			rt_noise_damier(t_hit *rec);
t_vec			rt_noise(t_object *o, t_hit rec);

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
