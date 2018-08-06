/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:25:12 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 19:30:41 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*map_path_list(t_list *elem)
{
	t_list	*npath;
	t_node	*node;

	node = dup_node(elem->content);
	npath = ft_lstnew_cc(node, sizeof(t_node));
	return (npath);
}
