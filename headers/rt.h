/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:29:25 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 15:50:32 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <rt_struct.h>

#include<stdio.h> /// // 

/* Parse  */

t_vec			rt_rot_dir(t_vec *d, t_vec r);
t_vec			rt_ctovec(char *str, t_rt *rt);
double			rt_ctod(char *str, t_rt *rt);
t_texture   	rt_ctotxt(char *str, t_rt *rt);

void			rt_parser(t_rt *p, char **av);
void            rt_add_object(t_tag *t, t_rt *rt);
void            rt_add_neg_object(t_tag *t, t_rt *rt);
void            rt_add_option(t_tag *tag, t_rt *rt);
void	        rt_add_light(t_tag *tag, t_rt *rt);


void			rt_check_cam(t_camera c, t_rt *rt);
void			rt_check_obj(t_object *o, t_rt *rt);
void			rt_check_obj_name(t_object *obj, t_rt *rt);
void			rt_check_neg_obj(t_object *o, t_rt *rt);
void			rt_check_neg_obj_name(t_object *obj, t_rt *rt);
void			rt_check_lights(t_light *l, t_rt *rt);
void			rt_set_coef(t_object *o);
void			rt_comp_obj(t_object *o, t_rt *rt);
void			ft_get_data(t_rt *p, int fd); ///// ADD MAX !!
int				ft_fr(char **str);

/*
 * Raytracer
 */
t_ray			rt_ray(t_vec a, t_vec b);
t_ray			rt_get_ray(t_camera *p, double u, double v);
t_vec           rt_raytracer(t_thread *t, t_ray r, int d);
t_vec           rt_anti_aliasing(t_thread *t, int col, int row);

t_vec	    	anti_aa(t_thread *t, double col, double row, int select);
int				progress_bar(t_rt *rt);
t_vec			rt_stereoscopy(t_thread *t, double col, double row, int select);

void			rt_start(t_rt *rt, void *(*rt_runner)(t_thread *t));
void			*rt_run(t_thread *t);
void			*rt_run_50(t_thread *t);
void			*rt_run_25(t_thread *t);
void			*rt_run_12(t_thread *t);

t_vec			rt_stereoscopy(t_thread *t, double col, double row, int select);

/*
 * Lighting
 */

void			rt_ambient(double amb, t_light *l, t_hit rec, t_vec *col);
int				rt_shading(t_thread *th, t_ray sh_r, t_light *l, t_vec *c, int dpt);
t_vec			rt_lighting(t_thread *th, t_light *t);

t_vec			rt_reflect(t_vec v, t_vec n);
int				rt_refract(t_vec i, t_vec n, float ior, t_vec *rf);
t_ray			rt_reflection(t_hit rec, t_ray r, t_object *o);
t_ray			rt_refraction(t_hit rec, t_ray r, t_object *o);

/*
 * Hit
 */
int				rt_hit(t_scene *scene, t_ray *r, t_hit *record, double closest);

int				rt_hit_sphere(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_cylinder(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_lcylinder(t_object *o, t_ray *r, t_hit *rec);
int				rt_hit_cone(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_lcone(t_object *o, t_ray *r, t_hit *rec);
int				rt_hit_plan(t_object *obj, t_ray *ray, t_hit *record);
int				rt_hit_care(t_object *o, t_ray *ray, t_hit *rec);

int				rt_hit_torus(t_object *obj, t_ray *ray, t_hit *record);
int             rt_hit_parabol(t_object *obj, t_ray *ray, t_hit *record);
int     		rt_hit_cube(t_object *oo, t_ray *r, t_hit *record);

int				rt_hit_glasse(t_object *o, t_ray *r,  t_hit *rec);
int             rt_hit_cube_troue(t_object *obj, t_ray *ray, t_hit *record);
int             rt_hit_mobius( t_object *o, t_ray *ray, t_hit *rec);
void	        cylinder_uv(t_object *o, t_hit *rec);
void            cone_uv(t_object *o, t_hit *rec);
void	    	sphere_uv(t_object *o, t_hit *rec);
t_vec		    normale_cylinder(t_object *o, t_ray *r, t_hit *rec);
t_vec           normale_cone(t_object *o, t_ray *r, t_hit *rec);

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
int				is_zero(double delta);
void			add_compos(t_object *o, t_vec r, int x, t_object *head);
void    		get_cube_compos(t_object *obj, t_rt *rt);
t_vec			rotation(t_vec dir, t_vec rot);
void		ft_float_swap(double *a, double *b);

double	    	degtorad(double angle);
double  		degtorad(double angle);
void			rt_get_repere(t_object *ob);
t_vec           rt_rotZ(t_vec vec, double angle);
t_vec           rt_rotY(t_vec vec, double angle);
t_vec           rt_rotX(t_vec vec, double angle);
int		is_yequal(t_vec a, t_vec b);

void			my_mlx_putpixel(t_vec *data, int x, int y, t_vec color);
t_vec			my_mlx_getpixel(t_vec *data, int x, int y);

/*
 * Textures && Noises
 */

t_texture		rt_init_txt(void);
t_vec			rt_get_color_from_texture(t_object *o, double *u, double *v);
t_vec  			rt_torus_noise(t_hit *rec);

int     		rt_add_noise(char *val, t_rt *rt);
t_vec			rt_noise_damier(t_hit *rec);
t_vec			rt_noise(t_object *o, t_hit *rec);
t_vec		    rt_rand1dto3d(double value);
t_vec		    rt_rand3dto3d(t_vec value);
t_vec            vec_floor(t_vec v);
double		    rt_rand3dto1d(t_vec value, t_vec dot_dir);
double		    rt_rand1dto1d(double value, double mutator);
float	        rt_smoothstep(float a, float b, float x);
float	        rt_step(float a, float x);
double	        rt_frac(double value);
t_vec	        rt_lerp(t_vec a, t_vec b, float f);
t_vec           rt_voronoi(t_vec p,  t_object *o);
t_vec           rt_start_voronoi(t_vec p, t_object *o);
int             tranc_txt(t_ray *ray, t_object *obj, t_hit *rec);

/*
 * Events
 */

int				rt_mouse(int button, int x, int y, t_rt *rt);
int				rt_keys(int key, t_rt *rt);

int             rt_move(int key, t_vec *vec);
int             rt_rot_event(int key, t_object *o);

void      rt_reset(t_rt *rt);

void        save_btn(t_rt *rt);
void        mvt_btn(t_rt *rt);
void        cam_btn(t_rt *rt);
void        light_btn(t_rt *rt);
void        dame_btn(t_rt *rt);
void        circ_btn(t_rt *rt);
void        v1_btn(t_rt *rt);
void        v2_btn(t_rt *rt);
void        v3_btn(t_rt *rt);

void	        create_buttons(int	size, t_rt *rt);
void        	swap_button_by_id(int	id, t_rt *rt);
void	image_create(t_rt *rt);
int		get_selected_button(int x, int y, t_rt *rt);

t_button	*damier_button(t_rt *rt);
t_button	*circles_button(t_rt *rt);
t_button	*voronoi1_button(t_rt *rt);
t_button	*voronoi2_button(t_rt *rt);
t_button	*voronoi3_button(t_rt *rt);

/*
 * Init
 */
void			rt_init(t_rt *rt);
t_scene			*rt_init_scene(t_rt *rt);
t_object		*rt_init_object(t_rt *rt);
t_object		rt_init_neg_object(void);
t_light			*rt_init_light(t_rt *rt);
t_camera		rt_init_camera(t_vec lookfrom, t_vec lookat, double vfov);
void			init_tab(t_vec *tab);

/*
 * Close
 */

void			rt_exit(t_rt *rt, char *m1, char *msg, int err);
int				rt_close(t_rt *rt);

/*
 * Negatives
 */
int		    negative(t_hit *record);
int			rt_negative_sphere(t_object *sphere, t_ray *r, t_hit *rec);
int			rt_negative_cylinder(t_object *o, t_ray *r, t_hit *rec);
int			rt_negative_cone(t_object *o, t_ray *r, t_hit *rec);
void    	rt_init_negative(t_hit *rec);


/*
 * Slicing
 */
int			rt_slicing(t_object *o, t_ray *r, t_hit *rec);
int		    in_cylindr(t_object *o);
int		    in_sphere(t_object *o);

#endif
