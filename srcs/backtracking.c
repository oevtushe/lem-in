/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:51:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/14 12:34:25 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		data_int(t_list *elem, void *data)
{
	if (*(int*)elem->content == *(int*)data)
		return (1);
	return (0);
}

static t_list	*clone_elem(t_list *elem)
{
	t_list *new_one;

	new_one = ft_lstnew(elem->content, elem->content_size);
	return (new_one);
}

int		backtracking(t_lmdata *data, t_pair *paths, int root)
{
	int			o;
	int			lo;
	t_list		*path;
	t_source	source;

	path = NULL;
	source.black_list = NULL;
	add_to_blacklist(&source.black_list, root);
	if (!(source.nodes = ((t_list*)data->extra->fst)->next))
		return (-1);
	data->extra->fst = source.nodes;
	wash_up_map(data);
	bfs(data, source.nodes, source.black_list);
	save_path_ro(data, &path);
	print_path(data);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		if ((o = check_overlapping((t_list*)paths->scd, path)) != -1)
		{
			ft_printf("overlap: %s\n", ((t_node*)data->adj[o]->content)->name);
			pdecode_paths(data, (t_list*)paths->scd);
			add_to_blacklist(&source.black_list, o);
		}
		else
		{
			ft_lstadd((t_list**)&paths->scd, ft_lstnew(path, sizeof(t_list)));
			pdecode_paths(data, (t_list*)paths->scd);
			/* In case when there are N ways and M ways to fininish, where N > M */
			if (ft_lstlen((t_list*)paths->scd) > ft_lstlen((t_list*)paths->fst))
				paths->fst = ft_lstmap(paths->scd, clone_elem);
			if ((lo = backtracking(data, paths, root)) == -1)
				return (-1);
			else
			{
				ft_printf("overlap: %s\n", ((t_node*)data->adj[lo]->content)->name);
				/* In case of collapsing with nodes not from current path */
				if (!ft_lstcontains(((t_list*)paths->scd)->content, &lo, data_int))
				{
					paths->scd = ((t_list*)paths->scd)->next;
					return (lo);
				}
				paths->scd = ((t_list*)paths->scd)->next;
				data->extra->fst = source.nodes;
				add_to_blacklist(&source.black_list, lo);
			}
		}
		path = NULL;
		wash_up_map(data);
		bfs(data, source.nodes, source.black_list);
		print_path(data);
		save_path_ro(data, &path);
	}
	// return first overlap
	return (*(int*)source.black_list->next->content);
}
