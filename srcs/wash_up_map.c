/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wash_up_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:56:37 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/10 15:56:58 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	wash_up(t_list *elem)
{
	t_node *node;

	node = (t_node*)elem->content;
	node->d = 0;
	node->p = 0;
	node->visited = 0;
}

void		wash_up_map(t_lmdata *data)
{
	int	i;

	i = 0;
	while (i < data->adj_cs)
		ft_lstiter(data->adj[i++], wash_up);
}
