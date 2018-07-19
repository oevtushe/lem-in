/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:39:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/19 19:28:32 by oevtushe         ###   ########.fr       */
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

static t_err	*gen_dlink_err(char *fst, char *scd)
{
	t_err	*err;
	t_pair	*pair;

	pair = ft_newpair(fst, ft_strlen(fst) + 1, scd, ft_strlen(scd) + 1);
	err = new_err(ER_LINK_DOUBLE, pair, sizeof(t_pair));
	ft_memdel((void**)&pair);
	return (err);
}

t_err			*add_link(t_lmdata *data, char *fst, char *scd)
{
	int		i;
	int		j;
	int		ec;
	t_err	*err;
	t_list	*clone;

	err = NULL;
	ec = ER_LINK_NOT_EXISTING_ROOM;
	if ((i = get_node_idx(data, fst)) >= 0 && (j = get_node_idx(data, scd)) >= 0)
	{
		if (ft_lst_get_node_idx(data->adj[i], data->adj[j], check) == -1 &&
				ft_lst_get_node_idx(data->adj[j], data->adj[i], check) == -1)
		{
			clone = clone_node(data->adj[j]);
			ft_lstappend(&data->adj[i], clone);
			clone = clone_node(data->adj[i]);
			ft_lstappend(&data->adj[j], clone);
			ec = 1;
		}
		else
		{
			ec = 0;
			if (i == j)
				err = new_err(ER_LINK_SELF, fst, ft_strlen(fst) + 1);
			else
				err = gen_dlink_err(fst, scd);
		}
	}
	if (ec == ER_LINK_NOT_EXISTING_ROOM)
	{
		if (i == -1)
			err = new_err(ec, fst, ft_strlen(fst) + 1);
		else
			err = new_err(ec, scd, ft_strlen(scd) + 1);
	}
	return (err);
}
