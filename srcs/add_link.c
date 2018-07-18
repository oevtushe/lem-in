/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:39:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 11:13:55 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check(t_list *n, void *sn)
{
	t_node *n1;
	t_node *n2;

	n1 = (t_node*)n->content;
	n2 = (t_node*)((t_list*)sn)->content;
	return (ft_strequ(n1->name, n2->name));
}

int		add_link(t_lmdata *data, char *fst, char *scd)
{
	int		i;
	int		j;
	int		res;
	t_list	*clone;

	res = ER_LINK_UNEXISTED_ROOM;
	if ((i = get_node_idx(data, fst)) >= 0 && (j = get_node_idx(data, scd)) >= 0)
	{
		if (ft_lst_get_node_idx(data->adj[i], data->adj[j], check) == -1 &&
				ft_lst_get_node_idx(data->adj[j], data->adj[i], check) == -1)
		{
			clone = clone_node(data->adj[j]);
			ft_lstappend(&data->adj[i], clone);
			clone = clone_node(data->adj[i]);
			ft_lstappend(&data->adj[j], clone);
			res = 1;
		}
		else
		{
			if (i == j)
				res = ER_LINK_SELF;
			else
				res = ER_LINK_DOUBLE;
		}
	}
	return (res);
}
