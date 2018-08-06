/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:12:10 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 18:12:19 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_paths(t_list *paths)
{
	int		i;
	t_list	*lst;

	i = 0;
	while (paths)
	{
		lst = paths->content;
		ft_printf("%s", ((t_node *)lst->content)->name);
		lst = lst->next;
		while (lst)
		{
			ft_printf("->%s", ((t_node *)lst->content)->name);
			lst = lst->next;
		}
		paths = paths->next;
		ft_putchar('\n');
	}
}

