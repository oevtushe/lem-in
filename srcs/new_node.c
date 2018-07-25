/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:07:49 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/25 12:32:30 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*new_node(char *line, int x, int y)
{
	t_node	*node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	node->name = ft_strdup(line);
	node->x = x;
	node->y = y;
	node->d = -1;
	node->p	= -1;
	return (node);
}
