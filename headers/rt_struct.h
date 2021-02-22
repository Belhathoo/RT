
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
	void		*img;
	int			*buf;
	int			width;
	int			height;
	float		scale;
}				t_texture;

typedef struct  s_cell
{ //// wherre is it !!
	t_vec	base;
	t_vec	cell;
	t_vec	cellcol;
	t_vec	tocell;
	t_vec   closest;
	t_vec	closetcell;
	t_vec	toclosest;
	t_vec	diff;
	t_vec	tocenter;
	t_vec	celldifference;
	double	mindistocell;
	double  minedgedistance;
	double	edgedistance;
	
}				t_cell;

typedef struct	s_voronoi
{
	float		valuechange;
	float		isborder;
	t_vec	    cellcolor;
	t_vec		p;
	t_vec		noise_v;
}				t_voronoi;


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


typedef struct s_m
{
	t_vec		ka;
	t_vec		kd;//coef diffuse
	t_vec		ks;//coef specular
	// float	ka;
	// float	kd;
	// float	ks;
	float		kr;//coef reflexion
	float		kt;//coef refraction
	float		shininess;
}				t_material;

typedef struct	s_o
{
	char		*name;
	char		*material;
	float		size;//radius or angle
	float		r;
	float		dist;
	float		width;
	float		height;
	float		angle;
	t_vec		pos;//position
	t_vec		dir;
	t_vec		rot;//rotation
	t_vec		col;//color
	t_texture	*txt;
	t_noise		noi;
	t_vec		vec1;
	t_vec		vec2;
	t_vec 		p; //
	int			(*hit)();
	int			is_sliced;
	t_vec		sl_vec;
	t_vec		sl_pnt;

	struct s_m	mat;
	
	struct s_o	*compos;
	struct s_o	*next;
}				t_object;

typedef	struct	s_l
{
	t_vec		pos;
	t_vec		dir;
	t_vec		col;
	t_vec		diff;
	t_vec		spec;

	double		intensity;
	double		flashlight;
	double		radius; // for soft shaddows !! not for sure
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
	double		delta;//eq 2eme deg
	double		coef[4];
	int			inside;
}				t_hit;



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

#endif
