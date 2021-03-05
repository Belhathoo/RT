
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
# include <rt_define.h>

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
	int			is_trans;
	t_vec		color;
	void		*img;
	int			*buf;
	int			width;
	int			height;
	float		scale;
}				t_texture;

typedef struct	s_noise
{
	int			is_noise;
	int			type;
	t_vec		col1;
	t_vec		col2;
}				t_noise;

typedef struct s_m
{
	t_vec		ka;
	t_vec		kd;
	t_vec		ks;
	float		shininess;
	float		kr;
	float		kt;
}				t_material;

typedef struct	s_o
{
	char		*name;
	char		*material;
	float		size;
	float		radius;
	float		angle;
	float		r;
	float		dist;
	float		width;
	float		height;
	t_vec		pos;
	t_vec		dir;
	t_vec		rot;//rotation
	t_vec		col;
	t_vec		vec1;
	t_vec		vec2;
	t_vec		sl_vec;
	t_vec		sl_pnt;

	t_texture	txt;
	t_noise		noi;
	float		scale;
	int			(*hit)();
	int			is_sliced;

	struct s_m	mat;
	float		refl;
	float		refr;
	
	//slice solution
	double		sl_sl;


	struct s_o	*compos;
	struct s_o	*next;
}				t_object;

typedef	struct	s_l
{
	int			type;
	t_vec		pos;
	t_vec		dir;
	t_vec		col;
	t_vec		l_vec;
	double		intensity;
	double		radius; // for soft shaddows !! not for sure
	double		angle;
	struct s_l	*next;
}				t_light;

typedef struct	s_hit
{
	t_object	*curr_obj;
	t_ray		*ray;
	t_vec		col;
	t_vec		p;
	t_vec		n;
	t_vec		or;
	t_vec		tmp;
	double		closest;
	double		t0;
	double		t1;
	double		t;
	double		u;
	double		v;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		coef[4];

	int			is_n;
	double		negative[2];
	t_vec		negative_normal;

	//slicing
	int			tx;
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
	t_object	*sl_obj;
	float		ambient;
	int			aa;

	int			max_anti_a;
	int			progress;
	int			select;
	int			key;
	int			key_cam;
	int			key2;
	t_vec		data1[9][IMG_WIDTH*IMG_HEIGHT];//IMG_WIDTH*IMG_HEIGHT

	//negative obj
	t_object	n_obj;
	int			is_neg;
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

typedef	struct	s_mobius
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		radius;
}				t_mobius;

typedef struct	s_voronoi
{
	float		valuechange;
	float		isborder;
	t_vec	    cellcolor;
	t_vec		p;
	t_vec		noise_v;
	t_vec		fcolor;
	t_vec		ffcolor;
	t_vec		fcol;
	t_vec		ffcol;
}				t_voronoi;

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


typedef struct  s_cell
{
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
#endif
