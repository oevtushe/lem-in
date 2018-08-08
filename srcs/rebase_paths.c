/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebase_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:43:50 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:41:49 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** function doesn't clone nodes, just catchs it by pointer
** don't need to free anything
*/

void	rebase_paths(t_list *paths)
{
	t_path	*p;
	t_list	*colors;
	int		def_one;

	def_one = 196;
	colors = ft_lstnew(&def_one, sizeof(int));
	while (paths)
	{
		p = (t_path *)ft_memalloc(sizeof(t_path));
		p->list = paths->content;
		p->color = gen_color(colors);
		ft_lstadd(&colors, ft_lstnew(&p->color, sizeof(int)));
		paths->content = p;
		paths = paths->next;
	}
	ft_lstdel(&colors, del_int);
}
