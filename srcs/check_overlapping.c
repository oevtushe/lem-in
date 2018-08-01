/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overlapping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:54:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/30 18:35:36 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Returns index of path with which overlapping has place.
** If no overlapping returns -1
*/

char	*check_overlapping(t_lmdata *data, t_list *paths, t_list *path)
{
	int		idx;
	t_list	*new_nodes;
	t_list	*old_nodes;

	idx = -1;
	while (paths)
	{
		// ignore end
		old_nodes = ((t_list*)paths->content)->next;
		while (old_nodes)
		{
			idx = get_node_idx(data, ((t_node *)old_nodes->content)->name);
			// ignore end
			new_nodes = path->next;
			while (new_nodes)
			{
				if (idx == get_node_idx(data, ((t_node *)new_nodes->content)->name))
					return (((t_node *)data->adj[idx]->content)->name);
				new_nodes = new_nodes->next;
			}
			old_nodes = old_nodes->next;
		}
		paths = paths->next;
	}
	return (NULL);
}
