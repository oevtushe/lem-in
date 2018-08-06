/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:29:39 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 19:29:44 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*dup_node(t_node *room)
{
	t_node	*new;

	new = (t_node *)ft_memalloc(sizeof(t_node));
	ft_memcpy(new, room, sizeof(t_node));
	new->name = ft_strdup(room->name);
	return (new);
}
