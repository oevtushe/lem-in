/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overlapping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 09:54:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/14 09:54:52 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_overlapping(t_list *paths, t_list *path)
{
	t_list *new_nodes;
	t_list *old_nodes;

	while (paths)
	{
		// ignore end
		old_nodes = ((t_list*)paths->content)->next;
		while (old_nodes)
		{
			// ignore end
			new_nodes = path->next;
			while (new_nodes)
			{
				if (*(int*)old_nodes->content == *(int*)new_nodes->content)
					return (*(int*)old_nodes->content);
				new_nodes = new_nodes->next;
			}
			old_nodes = old_nodes->next;
		}
		paths = paths->next;
	}
	return (-1);
}
