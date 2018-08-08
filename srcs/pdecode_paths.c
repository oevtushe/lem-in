/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdecode_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:04:01 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 15:31:09 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	pdecode_paths(t_list *paths, int *aop)
{
	int		i;
	t_list	*lst;
	t_path	*path;

	i = 0;
	while (paths)
	{
		path = (t_path *)paths->content;
		lst = path->list;
		ft_printf("%sAnts count%s: %d\n", YELLOW, RESET, aop[i++]);
		ft_printf("%sPath len%s: %d\n", YELLOW, RESET, ft_lstlen(lst));
		ft_printf("\033[38;5;%dm%s\033[m", path->color,
				((t_node *)lst->content)->name);
		lst = lst->next;
		while (lst)
		{
			ft_printf("->\033[38;5;%dm%s\033[m",
					path->color, ((t_node *)lst->content)->name);
			lst = lst->next;
		}
		paths = paths->next;
		ft_putchar('\n');
	}
}
