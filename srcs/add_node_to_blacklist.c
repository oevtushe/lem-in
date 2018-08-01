/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_to_blacklist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:09:13 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/30 18:43:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_node_to_blacklist(t_list **black_list, char *o)
{
	t_list *node;

	node = ft_lstnew(o, sizeof(char) * (ft_strlen(o) + 1));
	ft_lstappend(black_list, node);
}
