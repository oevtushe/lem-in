/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 09:23:12 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:33:59 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	del_no_content(void *content, size_t content_size)
{
	content = NULL;
	content_size = 0;
}

static void	finalize(int dl, t_list *black_list, t_lmdata *data)
{
	if (dl)
		add_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
				((t_node*)((t_list*)data->extra->scd)->content)->name);
	if (black_list)
		ft_lstdel(&black_list, del_no_content);
}

static void	init(t_list **path, t_list **paths, t_list **black_list, int *dl)
{
	*dl = 0;
	*path = NULL;
	*paths = NULL;
	*black_list = NULL;
}

/*
** Function find's paths between start and end room
*/

t_list		*get_paths(t_lmdata *d)
{
	int		dl;
	t_list	*path;
	t_list	*paths;
	t_list	*black_list;

	init(&path, &paths, &black_list, &dl);
	bfs(d, d->extra->fst, black_list, cmp_str_node);
	while (((t_node*)((t_list*)d->extra->scd)->content)->p != -1)
	{
		save_path(d, &path);
		ft_lstappend(&paths, ft_lstnew_cc(path, sizeof(t_list)));
		add_path_to_blacklist(&black_list, path);
		if (((t_node*)((t_list*)d->extra->scd)->content)->p == \
		get_node_idx(d, ((t_node*)((t_list*)d->extra->fst)->content)->name))
		{
			dl = 1;
			del_link(d, ((t_node*)((t_list*)d->extra->fst)->content)->name,
					((t_node*)((t_list*)d->extra->scd)->content)->name);
		}
		wash_up_map(d);
		bfs(d, d->extra->fst, black_list, cmp_str_node);
		path = NULL;
	}
	finalize(dl, black_list, d);
	return (paths);
}
