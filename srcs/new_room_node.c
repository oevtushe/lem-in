/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:40:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/05 10:39:25 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*new_room_node(char *name, int x, int y)
{
	t_node	*node;
	t_list	*lnode;

	node = new_node(name, x, y);
	lnode = ft_lstnew(node, sizeof(t_node));
	ft_memdel((void**)&node);
	return (lnode);
}
