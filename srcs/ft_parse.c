/* ************************************************************************** */

#include <rt.h>

char			*ft_get_full_text(const int fd)
{
	char		*text;
	char		*tmp;
	int			ret;
	int			sum;

	sum = 0;
	if (!(text = (char*)malloc(BUFF_SIZE + 1)))
		return (NULL);
	while ((ret = read(fd, &text[sum], BUFF_SIZE)))
	{
		sum += ret;
		if (sum == 0 || text[0] != '[')
			return (NULL);
		text[sum] = '\0';
		tmp = ft_strdup(text);
		free(text);
		text = (char*)malloc(sum + BUFF_SIZE + 1);
		ft_strcpy(text, tmp);
		free(tmp);
	}
	text[sum] = '\0';
	return (text);
}

int				ft_check_brackets(char *s)
{
	int			b;
	int			i;

	i = 1;
	b = 0;
	while (s[i])
	{
		if (s[i] == '}')
			return (0);
		if (s[i] == '{')
		{
			b++;
			while (s[i])
			{
				i++;
				if (s[i] == '{')
					return (0);
				if (s[i] == '}')
					break ;
			}
		}
		i++;
	}
	return (s[0] && s[0] == '[' && s[i - 2] && s[i - 2] == ']' ? b : 0);
}


void			ft_check_data(t_rt *p)
{
	t_object	*tmp;
	double		c[3];

	tmp = p->scene->object;
	c[0] = tmp->col.x;
	c[1] = tmp->col.y;
	c[2] = tmp->col.z;
	if (p->scene->cam.fov < 0.0 || p->scene->cam.fov > 180.0)
		rt_exit(p, "Wrong Field Of View value\n", EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->size < 0.001 && tmp->hit != rt_hit_plan)
			rt_exit(p, "wrong size detected\n", EXIT_FAILURE);
		if (!tmp->txt && ((c[0] < 0.0 || c[0] > 1.0) || (c[1] < 0.0 || c[1] > 1.0)
				|| (c[2] < 0.0 || c[2] > 1.0)))
			rt_exit(p, "Wrong color format detected; [0-1]\n", EXIT_FAILURE);
		tmp = tmp->next;
	}
}

void			ft_parser(char *file, t_rt *p)
{
	int			fd;
	int			check;
	char		*txt;

	txt = NULL;
	fd = open(file, O_RDONLY, !O_DIRECTORY);
	if ((fd = open(file, O_RDONLY)) == -1)
		rt_exit(p, ft_strjoin(file, " : No Such File\n"), EXIT_FAILURE);
	if (open(file, O_DIRECTORY) != -1)
		rt_exit(p, ft_strjoin(file, " : Must Be a File\n"), EXIT_FAILURE);
	close(fd);
	fd = open(file, O_RDONLY);
	if (!(txt = ft_get_full_text(fd)) && ft_fr(&txt))
		rt_exit(p, "Syntax!\n", EXIT_FAILURE);
	check = ft_check_brackets(txt);
	ft_fr(&txt);
	if (check < 2)
		rt_exit(p, "Brackets!\n", EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	ft_get_data(p, fd);
	close(fd);
	ft_check_data(p);
}

