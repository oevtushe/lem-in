/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 11:48:42 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:28:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	cmp(void *cdata, void *data)
{
	return (ft_strequ(((t_node *)cdata)->name, (char *)data));
}

static void	del(void *content, size_t content_size)
{
	content = NULL;
	content_size = 0;
	return ;
}

/*
** Function deletes link between two nodes
*/

void		del_link(t_lmdata *data, char *n1, char *n2)
{
	int idx1;
	int idx2;

	idx1 = get_node_idx(data, n1);
	idx2 = get_node_idx(data, n2);
	if (idx1 >= 0 && idx2 >= 0)
	{
		ft_lstdelsafe(&data->adj[idx1],
				((t_node*)data->adj[idx2]->content)->name, cmp, del);
		ft_lstdelsafe(&data->adj[idx2],
				((t_node*)data->adj[idx1]->content)->name, cmp, del);
	}
}
