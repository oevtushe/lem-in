/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:44:07 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/04 16:49:01 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_node(void *content, size_t content_size)
{
	t_node	*node;

	++content_size;
	node = (t_node*)content;
	ft_strdel(&node->name);
	ft_memdel(&content);
}

void	free_node(t_node **node)
{
	ft_strdel(&(*node)->name);
	ft_memdel((void**)node);
}
