/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:12:10 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/04 16:29:12 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_node_idx(t_lmdata *data, char *name)
{
	int		i;

	i = -1;
	while (++i < data->adj_cs)
		if (ft_strequ(((t_node*)(data->adj[i]->content))->name, name))
			return (i);
	return (-1);
}
