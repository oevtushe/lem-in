/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdecode_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:04:01 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/02 16:52:39 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	pdecode_paths(t_list *paths, int *aop)
{
	int		i;
	t_list *p;

	i = 0;
	while (paths)
	{
		p = (t_list *)paths->content;
		ft_printf("%sAnts count%s: %d\n", YELLOW, RESET, aop[i++]);
		ft_printf("%sPath len%s: %d\n", YELLOW, RESET, ft_lstlen(p));
		ft_printf("%s", ((t_node *)p->content)->name);
		p = p->next;
		while (p)
		{
			ft_printf("->%s", ((t_node *)p->content)->name);
			p = p->next;
		}
		paths = paths->next;
		ft_putchar('\n');
	}
}
