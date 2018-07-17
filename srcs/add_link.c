/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:39:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/16 18:20:11 by oevtushe         ###   ########.fr       */
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

	res = 0;
	if ((i = get_node_idx(data, fst)) >= 0 && (j = get_node_idx(data, scd)) >= 0)
	{
#ifdef DEBUG
		ft_printf("I know this nodes !!!\n");
#endif
		if (ft_lst_get_node_idx(data->adj[i], data->adj[j], check) == -1 &&
				ft_lst_get_node_idx(data->adj[j], data->adj[i], check) == -1)
		{
#ifdef DEBUG
			ft_printf("Add new node to %s\n", ((t_node*)data->adj[i]->content)->name);
#endif
			clone = clone_node(data->adj[j]);
			ft_lstappend(&data->adj[i], clone);
#ifdef DEBUG
			ft_printf("Add new node to %s\n", ((t_node*)data->adj[j]->content)->name);
#endif
			clone = clone_node(data->adj[i]);
			ft_lstappend(&data->adj[j], clone);
		}
#ifdef DEBUG
		else
		{
			ft_printf("This nodes are already linked OR This is a self-link!\n");
			return (0);
		}
#endif
		res = 1;
	}
	return (res);
}
