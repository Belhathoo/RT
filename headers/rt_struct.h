/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:29:15 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/11 14:29:18 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <rt_struct_annx.h>

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
	int			repet_txt;
	double		scale;
	double		mv1;
	double		mv2;
}				t_texture;

typedef struct	s_noise
{
	int			is_noise;
	int			type;
	t_vec		col1;
	t_vec		col2;
}				t_noise;

typedef struct	s_m
{
	t_vec		ka;
	t_vec		kd;
	t_vec		ks;
	float		shininess;
	float		kr;
	float		kt;
}				t_material;

typedef struct	s_button
{
	char		*name;
	void		*win;
	void		*mlx;
	void		*img;
	int			*img_data;
	int			bpp;
	int			size;
	int			endian;
	void		*deflt;
	int			*deflt_data;
	void		*select;
	int			state;
	int			h;
	int			w;
	int			x;
	int			y;
	t_vec		pos;
}				t_button;

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
	t_vec		rot;
	t_vec		col;
	t_vec		vec1;
	t_vec		vec2;

	t_vec		sl_vec;
	t_vec		sl_pnt;
	int			sl_ax;

	t_texture	txt;
	t_noise		noi;
	float		scale;
	int			(*hit)();
	int			is_sliced;

	struct s_m	mat;
	float		refl;
	float		refr;

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
	double		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_ry_light
{
	t_ray		r;
	t_light		*l;
	t_vec		l_vec;
}				t_sh_ray;

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
	double		neg[2];
	t_vec		neg_n;

	int			tx;
}				t_hit;

typedef struct	s_light_shading
{
	t_vec		l_vec;
	double		closest;
	t_object	*o;
	t_hit		rec;
}				t_li_sh;

typedef struct	s_slice
{
	t_object	plan;
	t_hit		recp;
	t_vec		p1;
	t_vec		p0;
	t_vec		ax;
	t_vec		my0;
	t_vec		my1;
	double		s0;
	double		s1;
	int			ret;
	double		t;
}				t_slice;

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

	int			dyn;
	int			aa;
	double		ambient;

	t_camera	camm[2];
	double		stereo;

	int			key_mvt;
	int			key_cam;
	int			key;

	int			max_anti_a;
	int			progress;
	int			select;
	t_vec		data1[9][IMG_WIDTH * IMG_HEIGHT];

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
	char		*name_sc;
	int			size;
	int			endian;
	int			filter;

	int			save_order;
	t_button	**bt;
	int			size_bt;
	t_vec		btns_up;
	t_vec		btns_noi;
	t_light		*s_light;
	int			is_perlin;
	t_vec		*ran;
	int			hash[255];
}				t_rt;

typedef struct	s_thread
{
	int			i;
	t_rt		*rt;
	t_hit		rec;
}				t_thread;

#endif
