/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:42:41 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 18:39:39 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Creates new node with the same content,
** as in passed one.
*/

t_list	*clone_node(t_list *room)
{
	t_list *clone;
	t_node *cr;

	cr = (t_node*)room->content;
	clone = ft_lstnew(NULL, 0);
	clone->content = cr;
	clone->content_size = sizeof(t_node);
	return (clone);
}
