/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct_annx.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:46:42 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/13 17:46:49 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCT_ANNX_H
# define RT_STRUCT_ANNX_H

typedef	struct		s_mobius
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			radius;
}					t_mobius;

typedef struct		s_voronoi
{
	float			valuechange;
	float			isborder;
	t_vec			cellcolor;
	t_vec			p;
	t_vec			noise_v;
	t_vec			fcolor;
	t_vec			ffcolor;
	t_vec			fcol;
	t_vec			ffcol;
}					t_voronoi;

typedef struct		s_image
{
	char			signature[2];
	int				file_size;
	int				reserved;
	int				data_offset;
	int				size_header;
	int				width;
	int				height;
	short			planes;
	short			bpp;
	int				rest_info[6];
	int				file;
}					t_image;

typedef	struct		s_coef
{
	double			m;
	double			n;
	double			o;
	double			p;
	double			q;
}					t_coef;

typedef struct		s_quartic
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			z;
	double			u;
	double			v;
	double			sub;
	double			sq_a;
	double			p;
	double			q;
	double			r;
}					t_quartic;

typedef struct		s_cubic
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			sq_a;
	double			p;
	double			q;
	double			cb_p;
}					t_cubic;

typedef struct		s_cell
{
	t_vec			base;
	t_vec			cell;
	t_vec			cellcol;
	t_vec			tocell;
	t_vec			closest;
	t_vec			closetcell;
	t_vec			toclosest;
	t_vec			diff;
	t_vec			tocenter;
	t_vec			celldifference;
	double			mindistocell;
	double			minedgedistance;
	double			edgedistance;
}					t_cell;

typedef struct		s_header
{
	unsigned int	bm_headersize;
	unsigned int	width;
	unsigned int	height;
	unsigned short	bpp;
	unsigned char	signature[2];
}					t_header;

typedef struct		s_bmp
{
	int				fd;
	t_header		*info_header;
	unsigned char	*data_decode;
	int				padding;
	unsigned char	**readed;
	unsigned char	*buffer;
	unsigned char	pad[4];
}					t_bmp;

#endif
