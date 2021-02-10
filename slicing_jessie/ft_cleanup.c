/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belhatho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:24:56 by belhatho          #+#    #+#             */
/*   Updated: 2020/11/16 12:24:57 by belhatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				ft_fr(char **str)
{
	(*str) ? ft_strdel(str) : 0;
	return (1);
}

void			ft_free_objects(t_object *object)
{
	t_object	*obj;
	t_object	*tmp;

	obj = object;
	while (obj != NULL)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
}

void			ft_free_lights(t_light *light)
{
	t_light		*l;
	t_light		*tmp;

	l = light;
	while (l != NULL)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

void			ft_fexit(char *msg, int err, t_ptr **p)
{
	ft_putstr(ft_strjoin(err ? "error: " : "", msg));
	if ((*p)->scene)
	{
		ft_free_objects((*p)->scene->obj);
		ft_free_lights((*p)->scene->light);
		free((*p)->scene);
	}
	free(*p);
	exit(0);
}
