
#include <rt.h>

unsigned int	bytes_to_number(unsigned char *str, unsigned int n)
{
	unsigned int ret;
	ft_memcpy((void *)&ret, (void *)str, n);
	return (ret);
}

void	free2d(unsigned char ***str)
{
	int i;

	i = 0;
	while ((*str)[i] != 0)
	{
		free((*str)[i]);
		i++;
	}
	free((*str)[i]);
	free(*str);
	*str = NULL;
}

t_bmp			*init_bmp()
{
	t_bmp	*bmp;

	if (!(bmp = malloc(sizeof(t_bmp))))
		return (NULL);
	if (!(bmp->info_header = malloc(sizeof(t_header))))
		return (NULL);
	bmp->data_decode = NULL;
	return (bmp);
}

void			destroy_bmp(t_bmp *bmp)
{
	free(bmp->info_header);
	bmp->info_header = NULL;
	free(bmp);
	bmp = NULL;
}