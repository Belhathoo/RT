
#include <rt.h>

void	decode_header(t_bmp *bmp)
{
	unsigned char buffer[40];
	unsigned char buff[14];
	int i;

	i = read(bmp->fd, buff, 14);
	bmp->info_header->signature[0] = buff[0];
	bmp->info_header->signature[1] = buff[1];
	i = read(bmp->fd, buffer, 40);
	(void)i;
	bmp->info_header->bm_headersize = bytes_to_number(buffer, 4);//
	bmp->info_header->width = bytes_to_number(buffer + 4, 4);//
	bmp->info_header->height = bytes_to_number(buffer + 8, 4);//
	bmp->info_header->bpp = bytes_to_number(buffer + 14, 2);//
	bmp->padding = bmp->info_header->width % 4;//hna kat7sab l padding rasek katched star kaml kat9assmou 3la 4bytes lli shat lik ra howa l padding
}

int		check_header(t_bmp *bmp)
{
	if (bmp->info_header->signature[0] != 'B' &&
			bmp->info_header->signature[1] != 'M')
		return (0);
	if (bmp->info_header->bm_headersize != 40)
		return (0);
	if (bmp->info_header->bpp != 24)
		return (0);
	return (1);
}

static t_bmp	*decode(char *path)
{
	t_bmp *bmp;

	if (!(bmp = init_bmp()))
		return (NULL);
	if ((bmp->fd = open(path, O_RDONLY)) == -1)
	{
		destroy_bmp(bmp);
		return (NULL);
	}
	decode_header(bmp);
	if (check_header(bmp))
	{
		if (!(get_image(bmp)))
			return (NULL);
	}
	else
		return (NULL);
	close(bmp->fd);
	return (bmp);
}

unsigned char	*import_bmp(char *path,
				int *width, int *height)
{
	t_bmp			*bmp;
	unsigned char	*ret;

	if (!(bmp = decode(path)))
		return (NULL);
	*width = bmp->info_header->width;
	*height = bmp->info_header->height;
	ret = bmp->data_decode;
	destroy_bmp(bmp);
	return (ret);
}
