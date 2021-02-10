/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:26:05 by belhatho          #+#    #+#             */
/*   Updated: 2021/01/31 15:31:11 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <pthread.h>

# include <stdio.h>

# define IMG_WIDTH  1200
# define IMG_HEIGHT 600

# define NBTHREAD 4
# define TMIN 0.00001
# define MLX_KEY_ESC 53

# define C_S "\t\"Object\": \"Sphere\""
# define C_P "\t\"Object\": \"Plane\""
# define C_CO "\t\"Object\": \"Cone\""
# define C_CY "\t\"Object\": \"Cylinder\""

typedef struct		s_vec
{
	double			e1;
	double			e2;
	double			e3;
}					t_vec;

typedef struct		s_ray
{
	t_vec			origin;
	t_vec			dir;
}					t_ray;

typedef	struct		s_obj
{
	char			*name;
	t_vec			pos;
	t_vec			rot;
	t_vec			color;
	double			size;
	int				(*hit)();
	double			ka;
	double			kd;
	double			ks;
	double			shininess;
	struct s_obj	*next;
}					t_object;

typedef struct		s_camera
{
	t_vec			origin;
	t_vec			lower_left_corner;
	t_vec			horizontal;
	t_vec			vertical;
	t_vec			lookat;
	t_vec			u;
	t_vec			v;
	t_vec			w;
	double			fov;
	double			half_h;
	double			half_w;
}					t_cam;

typedef	struct		s_l
{
	t_vec			pos;
	t_vec			color;
	double			intensity;
	struct s_l		*next;
}					t_light;

typedef	struct		s_hit_record
{
	double			t;
	double			closest;
	t_vec			p;
	t_vec			normal;
	t_object		*curr_obj;
	t_ray			*ray;
	t_vec			oc;
	t_vec			tmp;
	double			coef[3];
	double			sol[2];
	double			delta;
}					t_record;

typedef struct		s_scene
{
	t_cam			camera;
	t_object		*obj;
	t_light			*light;
	double			anti_a;
	double			amb;
}					t_scene;

typedef struct		s_ptr
{
	void			*win;
	void			*mlx;
	void			*img;
	int				*data;
	int				bpp;
	int				size;
	int				endian;
	t_scene			*scene;
}					t_ptr;

typedef struct		s_thread
{
	int				i;
	t_ptr			*p;
	t_record		rec;
}					t_thread;

void				ft_init(t_ptr *p);
void				kick_off(t_ptr *p);
void				*ft_draw(t_thread *thread);

int					ft_anti_a(t_thread *th, double i, double j);
t_vec				ft_calcul(t_thread *t, t_ray ray);
int					ft_shading(t_thread *th, t_vec lo);
void				ft_lighting(t_thread *th, t_light *l, t_vec *col);
void				ft_ambient(t_light *l, t_thread *th, t_vec *col);
void				ft_set_coef(t_object *o);

int					ft_hit(t_object *o, t_ray r, t_record *rec, double m);
int					ft_hit_sphere(t_object *sphere, t_ray *r, t_record *rec);
int					ft_hit_plan(t_object *o, t_ray *r, t_record *rec);
int					ft_hit_cylinder(t_object *o, t_ray *r, t_record *rec);
int					ft_hit_cone(t_object *o, t_ray *r, t_record *rec);

t_vec				ft_vec(double x, double y, double z);
t_vec				ft_plus(t_vec a, t_vec b);
t_vec				ft_plus_k(t_vec a, double b);
t_vec				ft_minus(t_vec a, t_vec b);
t_vec				ft_div(t_vec a, t_vec b);
t_vec				ft_produit(t_vec a, t_vec b);
t_vec				ft_unit_vec(t_vec a);
t_vec				ft_pro_k(t_vec a, double k);
t_vec				ft_div_k(t_vec a, double k);
double				ft_dot(t_vec a, t_vec b);
t_vec				ft_cross(t_vec a, t_vec b);
double				ft_length(t_vec a);
double				ft_lengthsquared(t_vec a);
double				ffmax(double a, double b);
int					ft_twodimlen(char **twodim);
void				ft_free_twodim(char **to_free);
double				ft_atod(char *str);
double				ft_clamping(double value);
void				ft_clamp(t_vec *c);
int					ft_rgb_to_int(t_vec c);
void				ft_mlx_putpixel(t_ptr *p, int x, int y, int color);

void				ft_parser(char *file, t_ptr *p);
void				ft_add_object(t_ptr *p, int fd, char **line, int t);
void				ft_get_object(t_ptr *p, t_object *obj, int fd, char **line);
void				ft_add_camera(t_ptr *p, int fd, char **line, int t);
void				ft_add_light(t_ptr *p, int fd, char **line);
t_cam				ft_cam_set(t_vec lookfrom, t_vec lookat, double fov);

void				ft_do_rot(t_ptr *p, t_vec *ret, char **each);
t_vec				ft_linetorot(t_ptr *p, char **line, int free_it);
t_vec				ft_linetovec(t_ptr *p, char **line, int free_it);
t_vec				ft_linetocol(t_ptr *p, char **line, int free_it);
double				ft_linetod(t_ptr *p, char **line, int free_it);

t_vec				ft_rot_x(t_vec old, double theta);
t_vec				ft_rot_y(t_vec old, double theta);
t_vec				ft_rot_z(t_vec old, double theta);

t_ray				ft_ray(t_vec a, t_vec b);
t_vec				ray_fctn(t_ray *r, float t);
t_ray				ft_ray_tracer(t_ptr *p, double x, double y);

int					ft_close(t_ptr *p);
int					ft_deal_key(int key, t_ptr *p);
int					ft_fr(char **str);
void				ft_free_objects(t_object *o);
void				ft_fexit(char *msg, int er, t_ptr **p);

void				image_create(int *img);
#endif
