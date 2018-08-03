/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:51:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 19:47:51 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*clone_elem(t_list *elem)
{
	t_list *new_one;

	new_one = ft_lstnew(elem->content, elem->content_size);
	return (new_one);
}

static int	cmp_str_str(void *cn, void *sn)
{
	if (ft_strequ((char *)cn, sn))
		return (1);
	return (0);
}

/*
** Paths are saved as t_node *
*/

char	*backtracking(t_lmdata *data, t_pair *paths, char *root, int *bn)
{
	char		*o;
	char		*lo;
	t_list		*path;
	t_source	source;

	path = NULL;
	source.black_list = NULL;
	add_node_to_blacklist(&source.black_list, root);
	if (!(source.nodes = ((t_list*)data->extra->fst)->next))
		return (NULL);
	data->extra->fst = source.nodes;
	wash_up_map(data);
	bfs(data, source.nodes, source.black_list, cmp_str_str);
	save_path(data, &path);
	ft_lstcorder(&path);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		if ((o = check_overlapping(data, (t_list*)paths->scd, path)))
		{
			if (*bn >= BC_STOP)
			{
				*bn = -1;
				return (NULL);
			}
			++(*bn);
			add_node_to_blacklist(&source.black_list, o);
		}
		else
		{
			ft_lstadd((t_list**)&paths->scd, ft_lstnew(path, sizeof(t_list)));
			if (ft_lstlen((t_list*)paths->scd) > ft_lstlen((t_list*)paths->fst))
				paths->fst = ft_lstmap(paths->scd, clone_elem);
			if (!(lo = backtracking(data, paths, root, bn)))
				return (NULL);
			else
			{
				if (ft_lstgetidx(((t_list*)paths->scd)->content, lo, cmp_lst_str) == -1)
				{
					paths->scd = ((t_list*)paths->scd)->next;
					return (lo);
				}
				paths->scd = ((t_list*)paths->scd)->next;
				data->extra->fst = source.nodes;
				add_node_to_blacklist(&source.black_list, lo);
			}
		}
		path = NULL;
		wash_up_map(data);
		bfs(data, source.nodes, source.black_list, cmp_str_str);
		save_path(data, &path);
		ft_lstcorder(&path);
	}
	return ((char *)source.black_list->next->content);
}
