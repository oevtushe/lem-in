/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:34:42 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/10 17:31:23 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	cycle_through_path(t_list *path, int *new, int *sm)
{
	int old;

	old = 0;
	while (path)
	{
		old = ((t_node *)path->content)->ant;
		((t_node *)path->content)->ant = 0;
		if (*new)
		{
			*sm = 1;
			((t_node *)path->content)->ant = *new;
			((t_node *)path->content)->fresh = 1;
		}
		*new = old;
		path = path->next;
	}
}

int			move_ants(t_lmdata *data, t_list *paths, int *al, int *aop)
{
	int		i;
	int		new;
	t_list	*path;
	t_point	sm_sum;

	i = 0;
	ft_memset(&sm_sum, 0, sizeof(t_point));
	while (paths)
	{
		new = 0;
		path = ((t_path *)paths->content)->list;
		sm_sum.y += ft_lstlen(path);
		if (*al < data->ants &&
			(i + 1) * (int)ft_lstlen(path) - sm_sum.y <= (data->ants - *al))
		{
			++aop[i];
			sm_sum.x = 1;
			new = ++*al;
			path = path->next;
		}
		cycle_through_path(path, &new, &sm_sum.x);
		paths = paths->next;
		++i;
	}
	return (sm_sum.x);
}
