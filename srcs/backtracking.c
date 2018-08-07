/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:51:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 19:47:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		find_path(t_lmdata *data, t_source *source, t_list **path)
{
	*path = NULL;
	wash_up_map(data);
	bfs(data, source->nodes, source->black_list, cmp_str_str);
	save_path(data, path);
	ft_lstcorder(path);
}

int		bad_cur_path(t_source *source, char *lo, t_pair *paths, t_pair *roots)
{
	t_list	*bp;

	bp = NULL;
	if (ft_lstgetidx(((t_list*)paths->scd)->content, lo, cmp_lst_str) == -1)
	{
		paths->scd = ((t_list*)paths->scd)->next;
		return (0);
	}
	bp = paths->scd;
	paths->scd = ((t_list*)paths->scd)->next;
	ft_lstdelone((t_list **)&bp, del_simple_paths);
	roots->scd = (void *)source->nodes;
	add_node_to_blacklist(&source->black_list, lo);
	return (1);
}

int		bt_init(t_source *source, t_pair *roots)
{
	source->black_list = NULL;
	add_node_to_blacklist(&source->black_list, (char *)roots->fst);
	if (!(source->nodes = ((t_list*)roots->scd)->next))
		return (0);
	roots->scd = (void *)source->nodes;
	return (1);
}

void	operate_paths(t_pair *paths, t_list *path)
{
	t_list	*cpath;

	cpath = ft_lstmap(path, map_path_list);
	ft_lstdel(&path, del_node);
	ft_lstadd((t_list**)&paths->scd, ft_lstnew_cc(cpath, sizeof(t_list)));
	if (ft_lstlen((t_list*)paths->scd) > ft_lstlen((t_list*)paths->fst))
		paths->fst = ft_lstmap(paths->scd, map_simple_paths);
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
		return (2);
	}
	return (1);
}

void	init_pair_cc(t_pair *pair, void *fst, void *scd)
{
	pair->fst = fst;
	pair->scd = scd;
}

void	pp(t_list *elem)
{
	ft_printf("%s->", ((t_node *)elem->content)->name);
}

void	ppp(t_list *path)
{
	ft_lstiter(path, pp);
	ft_putchar('\n');
}

char	*backtracking(t_lmdata *data, t_pair *paths, t_pair *roots, int *bn)
{
	char		*lo;
	t_list		*path;
	t_source	source;
	t_pair		bb;
	int			egs;

	if (!bt_init(&source, roots))
		return (NULL);
	find_path(data, &source, &path);
	init_pair_cc(&bb, &source, bn);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		egs = overlap_case_n_limit(data, paths, path, &bb);
		if (!egs)
			return (NULL);
		else if (egs == 1)
		{
			operate_paths(paths, path);
			if (!(lo = backtracking(data, paths, roots, bn)))
				return (NULL);
			else if (!bad_cur_path(&source, lo, paths, roots))
				return (lo);
		}
		find_path(data, &source, &path);
	}
	return ((char *)source.black_list->next->content);
}
