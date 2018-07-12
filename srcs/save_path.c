/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:15:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/12 14:17:45 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		save_path_ro(t_lmdata *data, t_list **path)
{
	int		idx_cur;
	int		idx_end;
	int		idx_start;
	t_node	*end;
	t_list	*n;

	((t_node*)((t_list*)data->extra->fst)->content)->p = -1;
	end = (t_node*)((t_list*)data->extra->scd)->content;
	if (!end->d)
	{
		ft_printf("There is no path between start and end !\nERROR\n");
		return ;
	}
	idx_start = get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name);
	idx_end = get_node_idx(data, ((t_node*)((t_list*)data->extra->scd)->content)->name);
	idx_cur = idx_end;
	while (idx_cur != -1)
	{
		n = ft_lstnew(&idx_cur, sizeof(int));
		ft_lstappend(path, n);
		idx_cur = ((t_node*)data->adj[idx_cur]->content)->p;
	}
	((t_node*)((t_list*)data->extra->fst)->content)->p = 0;
}
