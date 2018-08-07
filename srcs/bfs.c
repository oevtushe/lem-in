/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:54:47 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 18:31:49 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_node(t_list *v, t_list **queue, int ud, int idx_u)
{
	((t_node*)v->content)->d = ud + 1;
	((t_node*)v->content)->p = idx_u;
	ft_lstappend(queue, clone_node(v));
	((t_node*)v->content)->visited = 1;
}

void		bfs(t_lmdata *data, t_list *start, t_list *black_list, int (*check)(void *, void *))
{
	t_list	*queue;
	t_node	*u;
	t_list	*v;
	int		idx_u;

	queue = ft_lstnew_cc(start->content, sizeof(t_node));
	((t_node *)queue->content)->d = 0;
	while (queue)
	{
		u = ft_lstdequeue(&queue);
		idx_u = get_node_idx(data, u->name);
		v = data->adj[idx_u]->next;
		while (v)
		{
			if (!((t_node*)v->content)->visited && ft_lstgetidx(black_list,\
						((t_node *)v->content)->name, check) == -1)
				set_node(v, &queue, u->d, idx_u);
			v = v->next;
		}
		u->visited = 1;
	}
}
