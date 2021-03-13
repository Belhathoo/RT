
#include <rt.h>

static unsigned char	*img_cat(t_bmp *bmp, unsigned char **img_arr)
{
	unsigned char	*ret;
	int				len;
	unsigned int	i;
	int				j;
	int				k;

	k = 0;
	i = 0;
	len = bmp->info_header->width * 4;
	if (!(ret = malloc(bmp->info_header->width * bmp->info_header->height * 4)))
		return (NULL);
	while (i < bmp->info_header->height)
	{
		j = 0;
		while (j < len)
		{
			ret[k] = img_arr[i][j];
			k++;
			j++;
		}
		i++;
	}
	return (ret);
}

static unsigned char	*get_ligne(t_bmp *bmp, unsigned char *img)
{
	unsigned char	*ret;
	int				len;
	int				alloc;
	int				i;
	int				j;

	j = 0;
	i = 0;
	len = (bmp->info_header->width * 3);
	alloc = (bmp->info_header->width * 4);
	if (!(ret = malloc(alloc)))
		return (NULL);
	while (j < len)
	{
		ret[i] = img[j];
		ret[i + 1] = img[j + 1];
		ret[i + 2] = img[j + 2];
		ret[i + 3] = 0;
		j += 3;
		i += 4;
	}
	return (ret);
}

int		init_bmp2(t_bmp *bmp)
{
	if (!(bmp->readed = (unsigned char**)malloc(sizeof(unsigned char*) *
	(bmp->info_header->height + 1))))
		return (0);
	if (!(bmp->buffer = malloc((bmp->info_header->width * 3))))
		return (0);
	return(1);
}

int						get_image(t_bmp *bmp)
{
	int		i;
	int		k;

	init_bmp2(bmp);
	i = bmp->info_header->height - 1;
	bmp->readed[bmp->info_header->height] = 0;
	while (i != -1)
	{
		if (read(bmp->fd, bmp->buffer, (bmp->info_header->width * 3)))
			bmp->readed[i] = get_ligne(bmp, bmp->buffer);
		if (bmp->padding > 0)
			k = read(bmp->fd, bmp->pad, bmp->padding);
		i--;
	}
	free(bmp->buffer);
	if (!(bmp->data_decode = img_cat(bmp, bmp->readed)))
		return (0);
	(void)k;
	free2d(&bmp->readed);
	return (1);
}
