/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:51:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/30 19:09:02 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		data_str(t_list *elem, void *data)
{
	if (ft_strequ(((t_node *)elem->content)->name, (char *)data))
		return (1);
	return (0);
}

static t_list	*clone_elem(t_list *elem)
{
	t_list *new_one;

	new_one = ft_lstnew(elem->content, elem->content_size);
	return (new_one);
}

static int	check(t_list *cn, void *sn)
{
	if (ft_strequ(cn->content, sn))
		return (1);
	return (0);
}

/*
static void print_p(t_list *elem)
{
	ft_printf("%s\n", ((t_node *)elem->content)->name);
}
*/

/*
** Paths are saved as t_node *
*/

char	*backtracking(t_lmdata *data, t_pair *paths, char *root)
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
	bfs(data, source.nodes, source.black_list, check);
	save_path(data, &path);
	ft_lstcorder(&path);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		if ((o = check_overlapping(data, (t_list*)paths->scd, path)))
			add_node_to_blacklist(&source.black_list, o);
		else
		{
			ft_lstadd((t_list**)&paths->scd, ft_lstnew(path, sizeof(t_list)));
			//pdecode_paths(data, (t_list*)paths->scd);
			/* In case when there are N start ways and
			   M ways to fininish, where N > M */
			if (ft_lstlen((t_list*)paths->scd) > ft_lstlen((t_list*)paths->fst))
				paths->fst = ft_lstmap(paths->scd, clone_elem);
			if (!(lo = backtracking(data, paths, root)))
				return (NULL);
			else
			{
				ft_printf("overlap: %s\n", lo);
				/* In case of collapsing with nodes not from current path */
				if (ft_lstgetidx(((t_list*)paths->scd)->content, lo, data_str) == -1)
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
		bfs(data, source.nodes, source.black_list, check);
		save_path(data, &path);
		ft_lstcorder(&path);
	}
	return ((char *)source.black_list->next->content);
}
