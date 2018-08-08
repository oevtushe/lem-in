/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_simple_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:58:55 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:26:17 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*dup_path(t_list *elem)
{
	t_list	*new;
	t_node	*node;

	node = dup_node((t_node *)elem->content);
	new = ft_lstnew_cc(node, sizeof(t_node));
	return (new);
}

t_list			*map_simple_paths(t_list *paths_node)
{
	t_list *copy;
	t_list *cpath;
	t_list *npath;

	cpath = (t_list *)paths_node->content;
	npath = ft_lstmap(cpath, dup_path);
	copy = ft_lstnew_cc(npath, sizeof(t_list));
	return (copy);
}
