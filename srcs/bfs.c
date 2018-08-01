/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:54:47 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/30 18:33:40 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
static int check(t_list *elem, void *data)
{
	if (ft_strequ((char *)data, ((t_node *)elem->content)->name))
		return (1);
	return (0);
}
*/

void		bfs(t_lmdata *data, t_list *start, t_list *black_list, int (*check)(t_list *, void *))
{
	t_list	*queue;
	t_node	*u;
	t_list	*v;
	int		idx_u;

	queue = NULL;
	queue = clone_node(start);
	((t_node *)queue->content)->d = 0;
	while (queue)
	{
		u = ft_lstdequeue(&queue);
		idx_u = get_node_idx(data, u->name);
		v = data->adj[idx_u]->next;
		while (v)
		{
			//idx_v = get_node_idx(data, ((t_node *)v->content)->name);
			if (!((t_node*)v->content)->visited && ft_lstgetidx(black_list,\
						((t_node *)v->content)->name, check) == -1)
			{
				((t_node*)v->content)->d = u->d + 1;
				((t_node*)v->content)->p = idx_u;
				ft_lstappend(&queue, clone_node(v));
				((t_node*)v->content)->visited = 1;
			}
			v = v->next;
		}
		u->visited = 1;
	}
}
