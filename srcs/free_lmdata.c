/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lmdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:14:02 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 19:29:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_adj(void *content)
{
	t_node	*node;
	t_list	*lst;

	lst = (t_list *)content;
	node = (t_node *)lst->content;
	ft_strdel(&node->name);
	ft_memdel((void **)&node);
	ft_lstdel(&lst, del_empty_node);
}

void	free_lmdata(t_lmdata **data)
{
	ft_freepa_sd((void ***)&(*data)->input, (*data)->inp_size);
	ft_freepa((void ***)&(*data)->adj, (*data)->adj_cs, free_adj);
	ft_memdel((void **)&(*data)->extra);
	ft_memdel((void **)data);
}
