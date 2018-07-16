/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdecode_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:04:01 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/14 10:04:43 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	pdecode_paths(t_lmdata *data, t_list *paths)
{
	t_list *p;

	while (paths)
	{
		p = (t_list *)paths->content;

		ft_printf("%s", ((t_node*)data->adj[*(int*)p->content]->content)->name);
		p = p->next;
		while (p)
		{
			ft_printf("->%s", ((t_node*)data->adj[*(int*)p->content]->content)->name);
			p = p->next;
		}
		paths = paths->next;
		ft_putchar('\n');
	}
}
