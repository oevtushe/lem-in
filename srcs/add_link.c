/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:39:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/05 11:33:46 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check(t_list *n, t_list *sn)
{
	t_node *n1;
	t_node *n2;

	n1 = (t_node*)n->content;
	n2 = (t_node*)sn->content;
	return (ft_strequ(n1->name, n2->name));
}

int		add_link(t_lmdata *data, char *fst, char *scd)
{
	int		i;
	int		j;
	int		res;
	t_list	*clone;

	res = 0;
	if ((i = get_node_idx(data, fst)) >= 0 && (j = get_node_idx(data, scd)) >= 0)
	{
		ft_printf("I know this nodes !!!\n");
		if (!ft_lstcontains(data->adj[i], data->adj[j], check))
		{
			ft_printf("Add new node to %s\n", ((t_node*)data->adj[i]->content)->name);
			clone = clone_node(data->adj[j]);
			ft_lstappend(&data->adj[i], clone);
		}
		if (!ft_lstcontains(data->adj[j], data->adj[i], check))
		{
			ft_printf("Add new node to %s\n", ((t_node*)data->adj[j]->content)->name);
			clone = clone_node(data->adj[i]);
			ft_lstappend(&data->adj[j], clone);
		}
		res = 1;
	}
	return (res);
}
