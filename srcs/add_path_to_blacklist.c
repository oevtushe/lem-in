/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_blacklist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:41:17 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/17 11:26:41 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list *clone_path_node(t_list *elem)
{
	t_list *new;

	new = ft_lstnew(elem->content, elem->content_size);
	return (new);
}

void	add_path_to_blacklist(t_list **black_list, t_list *path)
{
	t_list *copy;

	if (path)
	{
		copy = ft_lstmap(path->next, clone_path_node);
		ft_lstpop(&copy);
		ft_lstappend(black_list, copy);
	}
}
