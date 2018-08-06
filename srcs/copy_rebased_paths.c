/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_rebased_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:57:17 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 19:32:09 by oevtushe         ###   ########.fr       */
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

t_list	*copy_rebased_paths(t_list *path_lst)
{
	t_list	*copy;
	t_path	*cpath;
	t_path	*npath;

	npath = (t_path *)ft_memalloc(sizeof(t_path));
	cpath = (t_path *)path_lst->content;
	ft_memcpy(npath, cpath, sizeof(t_path));
	npath->list = ft_lstmap(cpath->list, dup_path);
	copy = ft_lstnew_cc(npath, sizeof(t_path));
	return (copy);
}
