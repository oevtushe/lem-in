/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:39:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 15:40:21 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check(void *n, void *sn)
{
	t_node *n1;
	t_node *n2;

	n1 = (t_node*)n;
	n2 = (t_node*)((t_list*)sn)->content;
	return (ft_strequ(n1->name, n2->name));
}

t_err			*add_link(t_lmdata *data, char *fst, char *scd)
{
	int				i;
	int				j;
	t_err_code		ec;
	t_err			*err;
	t_list			*clone;

	err = NULL;
	ec = ERR_LINK_NOT_EXISTING_ROOM;
	if ((i = get_node_idx(data, fst)) >= 0 && (j = get_node_idx(data, scd)) >= 0)
	{
		if (ft_lstgetidx(data->adj[i], data->adj[j], check) == -1 &&
				ft_lstgetidx(data->adj[j], data->adj[i], check) == -1)
		{
			clone = clone_node(data->adj[j]);
			ft_lstappend(&data->adj[i], clone);
			clone = clone_node(data->adj[i]);
			ft_lstappend(&data->adj[j], clone);
			ec = ERR_NONE;
		}
		else
		{
			ec = ERR_NONE;
			if (i == j)
				err = raise_link_self(fst);
			else
				err = raise_link_double(fst, scd);
		}
	}
	if (ec == ERR_LINK_NOT_EXISTING_ROOM)
	{
		if (i == -1)
			err = raise_link_not_existing_room(fst);
		else
			err = raise_link_not_existing_room(scd);
	}
	return (err);
}
