/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:38:19 by oevtushe          #+#    #+#             */
/*   Updated: 2018/06/13 16:38:20 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_rooms(t_list *elem)
{
	t_node *node;

	node = (t_node*)elem->content;
	ft_printf("name = %s x=%d y=%d\n", node->name, node->x, node->y);
}
