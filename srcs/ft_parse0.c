
/* ************************************************************************** */

#include <rt.h>

int				ft_fr(char **str)
{
	(*str) ? ft_strdel(str) : 0;
	return (1);
}

void			ft_set_coef(t_object *o)
{
	o->ka = 0.8;
	o->kd = 0.6;
	o->ks = 0.6;
	o->shininess = 90;
}

t_vec		ft_rot_x(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x;
	new.y = old.y * cos(theta) - old.z * sin(theta);
	new.z = old.y * sin(theta) + old.z * cos(theta);
	return (new);
}

t_vec		ft_rot_y(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x * cos(theta) + old.z * sin(theta);
	new.y = old.y;
	new.z = -old.x * sin(theta) + old.z * cos(theta);
	return (new);
}

t_vec		ft_rot_z(t_vec old, double theta)
{
	t_vec	new;

	new.x = old.x * cos(theta) - old.y * sin(theta);
	new.y = old.x * sin(theta) + old.y * cos(theta);
	new.z = old.z;
	return (new);
}


void		ft_do_rot(t_rt *p, t_vec *ret, char **each)
{
	double		theta;

	theta = ft_atod(each[3]);
	if (theta < -180.0 || theta > 180.0 || ft_strlen(each[4]) != 1
		|| ((each[4][0] != 'x') && (each[4][0] != 'y') && (each[4][0] != 'z')))
	{
		ft_free_twodim(&each);
		rt_exit(p, "Wrong rotation angle detected or axes type\n", EXIT_FAILURE);
	}
	ret->x = ft_atod(each[0]);
	ret->y = ft_atod(each[1]);
	ret->z = ft_atod(each[2]);
	*ret = vec_unit(*ret);
	if (theta != 0.0)
	{
		if (each[4][0] == 'x')
			*ret = ft_rot_x(*ret, (theta * M_PI / 180.0));
		else if (each[4][0] == 'y')
			*ret = ft_rot_y(*ret, (theta * M_PI / 180.0));
		else
			*ret = ft_rot_z(*ret, (theta * M_PI / 180.0));
	}
}

t_vec		ft_linetorot(t_rt *p, char **line, int free_it)
{
	t_vec		ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 5)
		rt_exit(p, "Must be five values for Rotation Data\n", EXIT_FAILURE);
	ft_do_rot(p, &ret, each);
	ft_free_twodim(&each);
	return (ret);
}

t_vec		ft_linetovec(t_rt *p, char **line, int free_it)
{
	t_vec		ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 3)
		rt_exit(p, "must be three values for Vectors data.\n", EXIT_FAILURE);
	ret.x = ft_atod(each[0]);
	ret.y = ft_atod(each[1]);
	ret.z = ft_atod(each[2]);
	ft_free_twodim(&each);
	return (ret);
}

double		ft_linetod(t_rt *p, char **line, int free_it)
{
	double		ret;
	char		**each;
	char		*str;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 1)
		rt_exit(p, "must be one value for such data\n", EXIT_FAILURE);
	ret = ft_atod(each[0]);
	ft_free_twodim(&each);
	return (ret);
}

t_texture		*ft_linetotxt(t_rt *p, char **line, int free_it)
{
	char		**each;
	char		*str;
	t_texture	*txt;
	int 		bpp, size, endian;

	str = *line;
	while (*str && *str != ':')
		str++;
	while (*str && *str != '"')
		str++;
	str++;
	str = ft_strsub(str, 0, ft_strlen(str) - 1);
	each = ft_strsplit(str, ' ');
	free(str);
	if (free_it)
		free(*line);
	if (ft_twodimlen(each) != 1)
		rt_exit(p, "must be One value for txt data\n", 1);
	txt = rt_init_txt(p);
	if (!ft_strncmp(each[0], "damier", 6))
		txt->is_txt = 1;
	else
	{
		txt->img = mlx_xpm_file_to_image(p->mlx, each[0], &txt->width, &txt->height);
		if (!txt->img)
			rt_exit(p, "Texture: file unsupported", EXIT_FAILURE);
    	txt->buf = (int *)mlx_get_data_addr(txt->img, &bpp,  &size, &endian);
	}
	ft_free_twodim(&each);
	return (txt);
}

void			ft_add_camera(t_rt *p, int fd, char **line, int t)
{
	t_camera		cam;

	(t > 0) ? rt_exit(p, "Wrong camera number\n", EXIT_FAILURE) : 0;
	if (ft_strcmp(*line, "\t\"Camera\":") && ft_fr(line))
		rt_exit(p, "Camera syntax\n", EXIT_FAILURE);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && ft_fr(line))
		rt_exit(p, "Camera syntax - near to {\n", EXIT_FAILURE);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookfrom\": \""
				, 15) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Camera syntax - lookfrom\n", EXIT_FAILURE);
	cam.origin = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"lookat\": \""
				, 13) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Camera syntax - lookat\n", EXIT_FAILURE);
	cam.lookat = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"fov\": \""
				, 10) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Camera syntax - fov\n", EXIT_FAILURE);
	cam.fov = ft_linetod(p, line, 1);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && ft_fr(line))
		rt_exit(p, "Camera syntax - near to }\n", EXIT_FAILURE);
	p->scene->cam = rt_init_camera(cam.origin, cam.lookat, cam.fov);
}

void			ft_get_object(t_rt *p, t_object *obj, int fd, char **line)
{
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && ft_fr(line))
		rt_exit(p, "Object syntax - near to {\n", EXIT_FAILURE);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
				, 15) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Object syntax - 1st param position\n", EXIT_FAILURE);
	obj->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"rotation\": \""
				, 15) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Object syntax - 2nd param rotation\n", EXIT_FAILURE);
	obj->rot = vec_unit(ft_linetorot(p, line, 1));
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"translation\": \"", 18)
		|| line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Object syntax - 3rd param translation\n", EXIT_FAILURE);
	obj->pos = vec_add(obj->pos, ft_linetovec(p, line, 1));
	if (!(get_next_line(fd, line) > 0 && line[0][ft_strlen(*line) - 1] == '"') && ft_fr(line))
		rt_exit(p, "Object syntax - 4th param color\n", EXIT_FAILURE);
	else 
	{
		obj->txt = NULL;
		if (!ft_strncmp(*line, "\t\t\"color\": \"", 12))
			obj->col = ft_linetovec(p, line, 1);
		else if (!ft_strncmp(*line, "\t\t\"texture\": \"", 14))
			obj->txt = ft_linetotxt(p, line, 1);
		else 
		{
			ft_fr(line);
			rt_exit(p, "Object syntax - 4th param color/txt\n", EXIT_FAILURE);
		}
	}
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"size\": \""
				, 11) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Object syntax - 5th param size\n", EXIT_FAILURE);
	obj->size = ft_linetod(p, line, 1);
	if (!(ft_strcmp(obj->name, "TORUS")))
	{
		if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"r\": \""
			, 8)|| line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
				rt_exit(p, "Object syntax - 6th param r\n", EXIT_FAILURE);
		obj->r = ft_linetod(p, line, 0);
	}
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && ft_fr(line))
		rt_exit(p, "Object syntax - near to }\n", EXIT_FAILURE);
}

# define C_S "\t\"Object\": \"Sphere\""
# define C_P "\t\"Object\": \"Plane\""
# define C_CO "\t\"Object\": \"Cone\""
# define C_TO "\t\"Object\": \"Torus\""
# define C_CY "\t\"Object\": \"Cylinder\""

void			ft_add_object(t_rt *p, int fd, char **line, int t)
{
	t_object		*obj;
	t_object		*tmp;

	if (!(obj = (struct s_o*)malloc(sizeof(struct s_o))) && t < 0)
		rt_exit(p, "Cannot allocate\n", EXIT_FAILURE);
	tmp = p->scene->object;
	if (ft_strcmp(*line, C_S) && ft_strcmp(*line, C_CO) && ft_strcmp(*line, C_P)
			&& ft_strcmp(*line, C_CY) && ft_strcmp(*line, C_TO) && ft_fr(line))
		rt_exit(p, "object syntax - undefined object\n", EXIT_FAILURE);
	if (!ft_strcmp(*line, C_S) && (obj->hit = rt_hit_sphere))
		obj->name = ft_strdup("SPHERE");
	else if (!ft_strcmp(*line, C_CY) && (obj->hit = rt_hit_cylinder))
		obj->name = ft_strdup("CYLINDER");
	else if (!ft_strcmp(*line, C_CO) && (obj->hit = rt_hit_cone))
		obj->name = ft_strdup("CONE");
	else if (!ft_strcmp(*line, C_TO) && (obj->hit = rt_hit_torus))
		obj->name = ft_strdup("TORUS");
	else if (!ft_strcmp(*line, C_P) && (obj->hit = rt_hit_plan))
		obj->name = ft_strdup("PLANE");
	ft_get_object(p, obj, fd, line);
	ft_set_coef(obj);
	p->scene->object = obj;
	obj->next = tmp;
}

void			ft_add_light(t_rt *p, int fd, char **line)
{
	t_light			*light[2];

	if (!(light[0] = (struct s_l*)malloc(sizeof(struct s_l))))
		rt_exit(p, "Cannot allocate\n", EXIT_FAILURE);
	light[1] = p->scene->light;
	if (ft_strcmp(*line, "\t\"Light\":") && ft_fr(line))
		rt_exit(p, "Light syntax\n", EXIT_FAILURE);
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t{") && ft_fr(line))
		rt_exit(p, "Light syntax - near to {\n", EXIT_FAILURE);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"position\": \""
			, 15) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Light syntax - 1st param position\n", EXIT_FAILURE);
	light[0]->pos = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line, "\t\t\"color\": \""
			, 12) || line[0][ft_strlen(*line) - 1] != '"') && ft_fr(line))
		rt_exit(p, "Light syntax - 2nd param color\n", EXIT_FAILURE);
	light[0]->col = ft_linetovec(p, line, 1);
	if (get_next_line(fd, line) > 0 && (ft_strncmp(*line,
		"\t\t\"intensity\": \"", 16) || line[0][ft_strlen(*line) - 1] != '"'))
		rt_exit(p, "Light syntax - 3d param intensity\n", EXIT_FAILURE);
	light[0]->intensity = ft_clamping(ft_linetod(p, line, 1));
	if (get_next_line(fd, line) > 0 && ft_strcmp(*line, "\t}") && ft_fr(line))
		rt_exit(p, "Light syntax - near to }\n", EXIT_FAILURE);
	p->scene->light = light[0];
	light[0]->next = light[1];
}

void			ft_get_data(t_rt *p, int fd)
{
	static int		cam_nbr = 0;
	static int		obj_nbr = 0;
	char			*line;

	get_next_line(fd, &line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "\t\"Camera\":", 10))
			ft_add_camera(p, fd, &line, cam_nbr++);
		else if (!ft_strncmp(line, "\t\"Object\": ", 11))
			ft_add_object(p, fd, &line, obj_nbr++);
		else if (!ft_strncmp(line, "\t\"Light\":", 9))
			ft_add_light(p, fd, &line);
		else if (!ft_strncmp(line, "]", 1) && ft_fr(&line))
			break ;
		else
			rt_exit(p, "unexpected data\n", 1);
	}
	ft_fr(&line);
	if (cam_nbr == 0 || obj_nbr == 0)
		rt_exit(p, "Missing Data - Minimum \"1-camera && 1-object\"\n", 1);
}