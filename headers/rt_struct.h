
#ifndef RT_STRUCT_H
# define RT_STRUCT_H

# include <libft.h>
# include <libxml.h>
# include <libvec.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <pthread.h>

/*
 * Structures
 */

typedef struct	s_ray
{
	t_vec		origin;
	t_vec		dir;
}				t_ray;

typedef	struct	s_texture
{
	int			is_txt;
	// SDL_Surface	*surface;
	// Uint32		*data;
	void		*img;
	char		*filename;
	int			*buf;
	int			width;
	int			height;
	float		scale;
}				t_texture;

typedef struct	s_noise
{
	int			is_noise;
	int			type;
	float		scale1;
	float		scale2;
	t_vec		col1;
	t_vec		col2;
	//t_perlin	p;
}				t_noise;

typedef struct	s_o
{
	char		*name;
	char		*material;
	t_vec		pos;//position
	t_vec		dir;
	t_vec		rot;//rotation
	t_vec		col;//color
	t_texture	*txt;
	t_noise		noi;
	t_vec		vec1;
	t_vec		vec2;
	t_vec 		p; //
	float		size;//radius or angle
	double		r;
	float		ka;//coef ambient
	float		kd;//coef diffuse
	float		ks;//coef specular
	float		ke;//power of specular
	float		kr;//coef reflexion
	float		kf;//coef refraction
	float		shininess;
	int			(*hit)();
	struct s_o	*compos;
	struct s_o	*next;
}				t_object;

typedef	struct	s_l
{
	t_vec		pos;
	t_vec		dir;
	t_vec		col;
	double		intensity;
	double		flashlight;
	double		angle;
	int			type;
	struct s_l	*next;
}				t_light;

typedef struct	s_hit
{
	t_object	*curr_obj;
	t_ray		*ray;
	t_vec		col;
	t_vec		p; // p(t) = r_origin + t * r_direction
	t_vec		n;
	t_vec		or;
	t_vec		tmp;
	double		closest;
	double		t0;//sol1 2eme deg
	double		t1;//sol2 2eme deg
	double		t;//plus petit sol
	double		u;//texture
	double		v;//texture
	double		a;//eq 2eme deg
	double		b;//eq 2eme deg
	double		c;//eq 2eme deg
	double		coef[4];
	double		delta;//eq 2eme deg
}				t_hit;

typedef	struct	s_coef
{
	double		m;
	double		n;
	double		o;
	double		p;
	double		q;
}				t_coef;

typedef struct	s_quartic
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		z;
	double		u;
	double		v;
	double		sub;
	double		sq_a;
	double		p;
	double		q;
	double		r;
}				t_quartic;

typedef struct	s_cubic
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		sq_a;
	double		p;
	double		q;
	double		cb_p;
}				t_cubic;



typedef struct	s_camera
{
	t_vec		origin;
	t_vec		lower_left_corner;
	t_vec		horizontal;
	t_vec		vertical;
	t_vec		lookat;
	t_vec		lookfrom;
	t_vec		w;
	t_vec		u;
	t_vec		v;
	double		fov;
	double		half_h;
	double		half_w;
}				t_camera;

typedef struct	s_scene
{
	t_camera	cam;
	t_light		*light;
	t_object	*object;
	float		ambient;
	int			anti_aliasing;
}				t_scene;

typedef struct	s_rt
{
	t_scene		*scene;
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			bpp;
	int			size;
	int			endian;
	int 		filter;
}				t_rt;

typedef struct	s_thread
{
	int			i;
	t_rt		*rt;
	t_hit		rec;
    t_texture   *t;
}				t_thread;

#endif
