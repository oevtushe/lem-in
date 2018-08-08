/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 20:48:15 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:39:35 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_path_helper(t_lmdata *data, int idx)
{
	if (((t_node*)data->adj[idx]->content)->name ==
			((t_node*)((t_list*)data->extra->fst)->content)->name)
	{
		ft_printf("%s", ((t_node*)data->adj[idx]->content)->name);
		return ;
	}
	else
		print_path_helper(data, ((t_node*)data->adj[idx]->content)->p);
	ft_printf("->%s", ((t_node*)data->adj[idx]->content)->name);
}

void		print_path(t_lmdata *data)
{
	t_node	*end;

	end = (t_node*)((t_list*)data->extra->scd)->content;
	if (end->d == -1)
	{
		ft_printf("There is no path between start and end !\nERROR\n");
		return ;
	}
	print_path_helper(data, get_node_idx(data,
				((t_node*)((t_list*)data->extra->scd)->content)->name));
	ft_putchar('\n');
}
