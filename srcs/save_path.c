/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:15:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 15:43:56 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Saves path as list of rooms
*/

void		save_path(t_lmdata *data, t_list **path)
{
	int		idx_cur;
	int		idx_end;
	int		idx_start;
	t_node	*end;
	t_list	*n;

	((t_node*)((t_list*)data->extra->fst)->content)->p = -1;
	end = (t_node*)((t_list*)data->extra->scd)->content;
	if (end->d == -1)
		return ;
	idx_start = get_node_idx(data,
			((t_node*)((t_list*)data->extra->fst)->content)->name);
	idx_end = get_node_idx(data,
			((t_node*)((t_list*)data->extra->scd)->content)->name);
	idx_cur = idx_end;
	while (idx_cur != -1)
	{
		n = ft_lstnew_cc(dup_node(data->adj[idx_cur]->content),
				sizeof(t_node));
		ft_lstadd(path, n);
		idx_cur = ((t_node*)data->adj[idx_cur]->content)->p;
	}
	((t_node*)((t_list*)data->extra->fst)->content)->p = 0;
}
