/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:51:04 by belhatho          #+#    #+#             */
/*   Updated: 2021/03/10 17:51:05 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>



t_texture		rt_init_txt(void)
{
	t_texture	txt;

	txt.is_txt = 1;
	txt.buf = NULL;
	txt.img = NULL;
	return (txt);
}

t_object		rt_init_neg_object(void)
{
	t_object obj;

	obj.name = NULL;
	obj.pos = vec(0.0, 0.0, 0.0);
	obj.angle = 30.0;
	obj.radius = 2.0;
	obj.dir = vec(0.0, 1.0, 0.0);
	obj.rot = vec(0.0, 0.0, 0.0);
	obj.is_sliced = 0;
	obj.txt.is_txt = 0;
	obj.noi.is_noise = 0;
	obj.next = NULL;
	obj.compos = NULL;
	return (obj);
}

t_light			*rt_init_light(t_rt *rt)
{
	t_light	*light;

	if (!(light = (struct s_l*)malloc(sizeof(struct s_l))))
		rt_exit(rt, "Cannot allocate\n", "", EXIT_FAILURE);
	light->type = PT_LIGHT;
	light->pos = vec(0.0, 5.0, 15.0);
	light->col = vec(1.0, 1.0, 1.0);
	light->dir = vec(0.0, -1.0, 0.0);
	light->intensity = 0.6;
	light->next = NULL;
	return (light);
}

t_noise			rt_init_noise(void)
{
	t_noise n;

	n.is_noise = 0;
	n.type = 0;
	n.col1 = vec(1.0, 1.0, 1.0);
	n.col2 = vec(0.0, 0.0, 0.0);
	return (n);
}

void		init_perlin(t_rt *rt)
{
	int i;

	if (!(rt->ran = (t_vec *)malloc(256 * sizeof(t_vec))))
		rt_exit(rt, " perlin: ", "Cannot allacte", EXIT_FAILURE);
	i = 0;
	while (i < 256)
	{
		rt->ran[i].x = rand() % 255;
		rt->ran[i].y = rand() % 255;
		rt->ran[i].z = rand() % 255;
		rt->ran[i] = vec_unit(rt->ran[i]);
		rt->hash[i] = rand() % 255;
		i++;
	}
}

void			rt_init_obj_ann(t_object *obj)
{
	obj->refl = 0.0;
	obj->refr = 0.0;
	obj->txt.is_txt = 0;
	obj->txt.is_trans = 0;
	obj->txt.scale = 1.0;
	obj->txt.mv1 = 0.0;
	obj->txt.mv2 = 0.0;
	obj->noi = rt_init_noise();
	obj->scale = 1;
	obj->is_sliced = 0;
	obj->sl_pnt = vec(0.0, 0.0, 0.0);
	obj->sl_vec = vec(0.0, -1.0, 0.0);
	obj->sl_ax = 0.0;
}

t_object		*rt_init_object(t_rt *rt)
{
	t_object *obj;

	if (!(obj = (struct s_o*)malloc(sizeof(struct s_o))))
		rt_exit(rt, "", "Cannot allocate!", EXIT_FAILURE);
	obj->name = NULL;
	obj->material = NULL;
	obj->pos = vec(0.0, 0.0, 0.0);
	obj->size = 3.0;
	obj->radius = 3.0;
	obj->angle = 35;
	obj->r = 1.0;
	obj->dist = 4.0;
	obj->width = 5.0;
	obj->height = 2.50;
	obj->angle = 30.0;
	obj->dir = vec(0.0, 1.0, 0.0);
	obj->rot = vec(0.0, 0.0, 0.0);
	obj->col = vec(1.0, 0.7, 0.3);
	rt_init_obj_ann(obj);
	obj->next = NULL;
	obj->compos = NULL;
	return (obj);
}

t_scene		*rt_init_scene(t_rt *rt)
{
	t_scene *scene;

	if (!(scene = (struct s_scene*)malloc(sizeof(struct s_scene))))
		rt_exit(rt, "", "Cannot allocate!", EXIT_FAILURE);
	scene->progress = 1;
	scene->select = 0;
	scene->max_anti_a = 9;
	scene->aa = 1;
	scene->ambient = 0.15;
	scene->stereo = 0.0;
	scene->object = NULL;
	scene->light = NULL;
	scene->sl_obj = NULL;
	scene->is_neg = 0;
	scene->key_cam = 0;
	scene->key_mvt = 0;
	scene->key = 0;
	return (scene);
}

void		rt_init(t_rt *rt)
{
	rt->is_perlin = 0;
	rt->img = NULL;
	rt->mlx = NULL;
	rt->data = NULL;
	rt->win = NULL;
	rt->filter = NONE_FILTER;
}
