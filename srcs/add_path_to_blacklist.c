/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_blacklist.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:41:17 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 18:39:14 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_path_to_blacklist(t_list **black_list, t_list *path)
{
	t_list *copy;

	if (path)
	{
		copy = ft_lstmap(path->next, clone_node);
		ft_lstpop(&copy);
		if (copy)
			ft_lstappend(black_list, copy);
	}
}
