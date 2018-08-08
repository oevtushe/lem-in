/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:32:49 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:39:14 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ant(t_list *lst, t_pair *extra, t_po *po, t_path *path)
{
	if (po->p && ft_lstgetidx((t_list *)extra->fst,
				((t_node *)lst->content)->name, cmp_lst_str) != -1 &&
			!ft_strequ(((t_node *)lst->content)->name,
				((t_node *)((t_list *)extra->scd)->content)->name))
		ft_printf("%s%sL%d-%s%s", BOLD, GREEN,
				((t_node *)lst->content)->ant,
				((t_node *)lst->content)->name, RESET);
	else if (po->p && ft_strequ(((t_node *)lst->content)->name,
				((t_node *)((t_list *)extra->scd)->content)->name))
		ft_printf("%s\033[38;5;196mL%d-%s\033[m", BOLD,
				((t_node *)lst->content)->ant,
				((t_node *)lst->content)->name);
	else if (po->p)
		ft_printf("\033[38;5;%dmL%d-%s\033[m", path->color,
				((t_node *)lst->content)->ant,
				((t_node *)lst->content)->name);
	else
		ft_printf("L%d-%s", ((t_node *)lst->content)->ant,
				((t_node *)lst->content)->name);
}

void	check_path(t_pair *f, t_pair *extra, t_po *po, t_point *p)
{
	t_path *path;

	path = ((t_list *)f->scd)->content;
	while (f->fst)
	{
		if (((t_node *)((t_list *)f->fst)->content)->ant
				&& ((t_node *)((t_list *)f->fst)->content)->fresh)
		{
			if (p->y)
				ft_putchar(' ');
			print_ant(((t_list *)f->fst), extra, po, path);
			((t_node *)((t_list *)f->fst)->content)->fresh = 0;
			p->x = 1;
			p->y = 1;
			break ;
		}
		f->fst = ((t_list *)f->fst)->next;
	}
}
