/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 09:33:03 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:38:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	i_cant_make_any_more_names(t_list **runner, t_list *paths, int *c)
{
	int res;

	res = 0;
	if (!*runner && *c)
	{
		*c = 0;
		*runner = paths;
	}
	else if (!*runner && !*c)
	{
		ft_putchar('\n');
		res = 1;
	}
	return (res);
}

static void	move_it(t_path **path, t_pair *f)
{
	ft_lstcorder(&((t_path *)((t_list *)f->scd)->content)->list);
	*path = (t_path *)((t_list *)f->scd)->content;
	f->fst = (*path)->list;
}

static void	init_pair(t_pair *f, void *fst, void *scd)
{
	f->fst = fst;
	f->scd = scd;
}

static void	init_point(t_point *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

/*
** Function cycles through the paths list and prints moved ants in the following
** order:
**			first ant moved on the first path
**			first ant moved on the second path
**			...
**			second ant moved on the first path
**			second ant moved on the second path
**			...
**
** ('first' && 'second') is about the last(the closest one
** to the end) ant on the current path.
** Continue until there is at least one moved ant in the paths list
*/

void		print_ants(t_list *paths, t_pair *extra, t_po *po)
{
	t_path	*path;
	t_pair	f;
	t_point	p;

	init_point(&p, 0, 0);
	init_pair(&f, NULL, paths);
	while (1)
	{
		move_it(&path, &f);
		check_path(&f, extra, po, &p);
		ft_lstcorder(&((t_path *)((t_list *)f.scd)->content)->list);
		f.scd = ((t_list *)f.scd)->next;
		if (i_cant_make_any_more_names((t_list **)&f.scd, paths, &p.x))
			break ;
	}
}
