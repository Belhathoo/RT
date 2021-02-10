/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:34:36 by belhatho          #+#    #+#             */
/*   Updated: 2021/01/31 16:58:21 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init(t_ptr *p)
{
	p->img = NULL;
	p->mlx = NULL;
	p->data = NULL;
	p->win = NULL;
	p->scene->anti_a = 3;
	p->scene->amb = 0.85;
}

void		ft_mlx_launch(t_ptr *p)
{
	ft_init(p);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, IMG_WIDTH, IMG_HEIGHT, "RTv1");
	p->img = mlx_new_image(p->mlx, IMG_WIDTH, IMG_HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->size, &p->endian);
}

typedef struct	s_image
{
	//header
	char		signature[2];
	int			file_size;
	int			reserved;
	int			data_offset;
	//info_header
	int			size_header;
	int			width;
	int			height;
	short		planes;
	short		bpp;
	int			rest_info[6];
}				t_image;

void	image_header(t_image *image, int file)
{
	char	str[54];
	ft_bzero(str, 54);
	ft_memcpy(str, image->signature, 2);
	ft_memcpy(str + 2, &image->file_size, 4);
	ft_memcpy(str + 6, &image->reserved, 4);
	ft_memcpy(str + 10, &image->data_offset, 4);
	ft_memcpy(str + 14, &image->size_header, 4);
	ft_memcpy(str + 18, &image->width, 4);
	ft_memcpy(str + 22, &image->height, 4);
	ft_memcpy(str + 26, &image->planes, 2);
	ft_memcpy(str + 28, &image->bpp, 2);
	ft_memcpy(str + 30, &image->rest_info, 24);
	write(file, &str, 54);
}
void	fill_data(t_image *image)
{
	image->signature[0] = 'B';
	image->signature[1] = 'M';
	image->file_size = (IMG_WIDTH * IMG_HEIGHT * 4) + 54; //54bytes header + every pixel is represented by 4 bytes
	image->reserved = 0;
	image->data_offset = 54;
	image->size_header = 40;
	image->width = IMG_WIDTH;
	image->height = IMG_HEIGHT;
	image->planes = 1;
	image->bpp = 24;
	ft_bzero(image->rest_info, 24);
}
void	image_put(int *img, t_image *image, int file)
{
	int				color;
	unsigned char	*buf;
	int				row;
	int				col;
	row = image->height;
	buf = malloc(image->file_size);
	ft_bzero(buf, sizeof(buf));
	while (row >= 0)
	{
		col = 0;
		while (col < (int)image->width)
		{
			color = img[(IMG_HEIGHT - row) *
				IMG_WIDTH + col];
			buf[row * image->width * 3 + col * 3 + 0] = color;
			buf[row * image->width * 3 + col * 3 + 1] = color >> 8;
			buf[row * image->width * 3 + col * 3 + 2] = color >> 16;
			col++;
		}
		row--;
	}
	write(file, buf, image->file_size);
	free(buf);
}
void	image_create(int *img)
{
	t_image	image;
	int		file;
	file = open("./save.bmp", O_RDWR | O_CREAT, 777);
	fill_data(&image);
	image_header(&image, file);
	image_put(img, &image, file);
}

int			main(int argc, char **argv)
{
	t_ptr	*p;

	if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
		return (0);
	if (argc == 2)
		ft_parser(argv[1], p);
	else
		ft_fexit("usage: ./rtv1: 1_scene_file\n", 0, &p);
	ft_mlx_launch(p);
	kick_off(p);
	mlx_hook(p->win, 17, 0, ft_close, p);
	mlx_hook(p->win, 2, 0, ft_deal_key, p);
	mlx_loop(p->mlx);
	return (0);
}
