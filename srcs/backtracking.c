/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:51:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 10:45:02 by oevtushe         ###   ########.fr       */
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

void		find_path(t_lmdata *data, t_source *source, t_list **path)
{
	*path = NULL;
	wash_up_map(data);
	bfs(data, source->nodes, source->black_list, cmp_str_str);
	save_path(data, path);
	ft_lstcorder(path);
}

int		bad_cur_path(t_lmdata *data, t_source *source, char *lo, t_pair *paths)
{
	if (ft_lstgetidx(((t_list*)paths->scd)->content, lo, cmp_lst_str) == -1)
	{
		paths->scd = ((t_list*)paths->scd)->next;
		return (0);
	}
	paths->scd = ((t_list*)paths->scd)->next;
	data->extra->fst = source->nodes;
	add_node_to_blacklist(&source->black_list, lo);
	return (1);
}

int		bt_init(t_lmdata *data, t_source *source, char *root)
{
	source->black_list = NULL;
	add_node_to_blacklist(&source->black_list, root);
	if (!(source->nodes = ((t_list*)data->extra->fst)->next))
		return (0);
	data->extra->fst = source->nodes;
	return (1);
}

void	operate_paths(t_pair *paths, t_list *path)
{
	ft_lstadd((t_list**)&paths->scd, ft_lstnew(path, sizeof(t_list)));
	if (ft_lstlen((t_list*)paths->scd) > ft_lstlen((t_list*)paths->fst))
		paths->fst = ft_lstmap(paths->scd, clone_elem);
}

int		overlap_case_n_limit(t_lmdata *data, t_pair *paths, t_list *path, t_pair *extra)
{
	char	*o;

	o = NULL;
	if ((o = check_overlapping(data, (t_list*)paths->scd, path)))
	{
		if ((*(int *)extra->scd)++ >= BC_STOP)
		{
			(*(int *)extra->scd) = -1;
			return (0);
		}
		add_node_to_blacklist(&((t_source *)extra->fst)->black_list, o);
	}
	return (1);
}

/*
** Paths are saved as t_node *
*/

char	*backtracking(t_lmdata *data, t_pair *paths, char *root, int *bn)
{
	char		*lo;
	t_list		*path;
	t_source	source;
	t_pair		*bb;

	if (!bt_init(data, &source, root))
		return (NULL);
	find_path(data, &source, &path);
	bb = ft_newpair_cc(&source, bn);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		if (!overlap_case_n_limit(data, paths, path, bb))
			return (NULL);
		else
		{
			operate_paths(paths, path);
			if (!(lo = backtracking(data, paths, root, bn)))
				return (NULL);
			else if (!bad_cur_path(data, &source, lo, paths))
				return (lo);
		}
		find_path(data, &source, &path);
	}
	return ((char *)source.black_list->next->content);
}
