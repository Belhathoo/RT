/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp_extractor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:23:20 by msoulaim          #+#    #+#             */
/*   Updated: 2021/03/13 16:28:28 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
	image->file_size = (IMG_WIDTH * IMG_HEIGHT * 4) + 54;
	image->reserved = 0;
	image->data_offset = 54;
	image->size_header = 40;
	image->width = IMG_WIDTH;
	image->height = IMG_HEIGHT;
	image->planes = 1;
	image->bpp = 24;
	ft_bzero(image->rest_info, 24);
}

void	image_remap(int *img, t_image *image, int file)
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
			color = img[(IMG_HEIGHT - row) * IMG_WIDTH + col];
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

void	image_create(t_rt *rt)
{
	t_image	image;
	char	*name;
	char	*name_no_id;
	char	*name_dir;
	char	*id;

	name_no_id = ft_strsub(rt->name_sc, 8, ft_strlen(rt->name_sc) - 12);
	name_dir = ft_strjoin("saved_img/", name_no_id);
	free(name_no_id);
	name_no_id = ft_strjoin(name_dir, "_");
	id = ft_itoa(rt->save_order);
	free(name_dir);
	name_dir = ft_strjoin(name_no_id, id);
	name = ft_strjoin(name_dir, ".bmp");
	free(name_dir);
	free(name_no_id);
	free(id);
	image.file = open(name, O_RDWR | O_CREAT, 777);
	fill_data(&image);
	image_header(&image, image.file);
	image_remap(rt->data, &image, image.file);
	rt->save_order++;
}
